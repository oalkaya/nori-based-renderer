/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob, Romain Prévost

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/camera.h>
#include <nori/rfilter.h>
#include <nori/warp.h>
#include <Eigen/Geometry>

NORI_NAMESPACE_BEGIN

/**
 * \brief Perspective camera with depth of field
 *
 * This class implements a simple perspective camera model. It uses an
 * infinitesimally small aperture, creating an infinite depth of field.
 */
class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(const PropertyList &propList) {
        /* Width and height in pixels. Default: 720p */
        m_outputSize.x() = propList.getInteger("width", 1280);
        m_outputSize.y() = propList.getInteger("height", 720);
        m_invOutputSize = m_outputSize.cast<float>().cwiseInverse();

        /* Specifies an optional camera-to-world transformation. Default: none */
        m_cameraToWorld = propList.getTransform("toWorld", Transform());

        /* Horizontal field of view in degrees */
        m_fov = propList.getFloat("fov", 30.0f);

        /* Near and far clipping planes in world-space units */
        m_nearClip = propList.getFloat("nearClip", 1e-4f);
        m_farClip = propList.getFloat("farClip", 1e4f);

        /* Additional features needed for DoF */
        m_lensRadius = propList.getFloat("lensRadius", 0);
        m_focalDistance = propList.getFloat("focalDistance", 1);

        /* Additional param for Radial Distortion */
        m_radialDistortionCoeff = propList.getFloat("radialDistortionCoeff", 0);

        /* Get Chromatic Aberration vector, set toggle to true if non-zero */
        m_chromaticAberrationWeight = propList.getVector3("chromaticAberrationWeight", Vector3f(0.0f));
        m_hasChromaticAberration =  m_chromaticAberrationWeight.norm() < Epsilon ? false : true;

        m_rfilter = NULL;
    }

    virtual void activate() override {
        float aspect = m_outputSize.x() / (float) m_outputSize.y();

        /* Project vectors in camera space onto a plane at z=1:
         *
         *  xProj = cot * x / z
         *  yProj = cot * y / z
         *  zProj = (far * (z - near)) / (z * (far-near))
         *  The cotangent factor ensures that the field of view is
         *  mapped to the interval [-1, 1].
         */
        float recip = 1.0f / (m_farClip - m_nearClip),
              cot = 1.0f / std::tan(degToRad(m_fov / 2.0f));

        Eigen::Matrix4f perspective;
        perspective <<
            cot, 0,   0,   0,
            0, cot,   0,   0,
            0,   0,   m_farClip * recip, -m_nearClip * m_farClip * recip,
            0,   0,   1,   0;

        /**
         * Translation and scaling to shift the clip coordinates into the
         * range from zero to one. Also takes the aspect ratio into account.
         */
        m_sampleToCamera = Transform(
            Eigen::DiagonalMatrix<float, 3>(Vector3f(0.5f, -0.5f * aspect, 1.0f)) *
            Eigen::Translation<float, 3>(1.0f, -1.0f/aspect, 0.0f) * perspective).inverse();

        /* If no reconstruction filter was assigned, instantiate a Gaussian filter */
        if (!m_rfilter) {
            m_rfilter = static_cast<ReconstructionFilter *>(
                    NoriObjectFactory::createInstance("gaussian", PropertyList()));
            m_rfilter->activate();
        }
    }

    Color3f sampleRay(Ray3f &ray,
            const Point2f &samplePosition,
            const Point2f &apertureSample,
            enum RGBChannel channel) const {
        /* Compute the corresponding position on the
           near plane (in local camera space) */
        Point3f nearP = m_sampleToCamera * Point3f(
            samplePosition.x() * m_invOutputSize.x(),
            samplePosition.y() * m_invOutputSize.y(), 0.0f);

        /* Implementation idea inspired from: https://prideout.net/barrel-distortion */
        /* Radial distortion function inspired from: https://github.com/tensorflow/graphics/blob/master/tensorflow_graphics/rendering/camera/quadratic_radial_distortion.py */
        if(m_radialDistortionCoeff != 0){
            nearP = quadraticRadialDistort(nearP);
        }

        /* Turn into a normalized ray direction, and
           adjust the ray interval accordingly */
        Vector3f d = nearP.normalized();
        float invZ = 1.0f / d.z();


        /* Chromatic Aberration */
        /* Channel_ALL also implies that there is no Chromatic Aberration*/
        float channelWeight;
        Color3f returnColor = Color3f(1.0f);

        switch(channel){
            case Camera::Channel_R: channelWeight = m_chromaticAberrationWeight.x(); returnColor = Color3f(1.0f, 0.0f, 0.0f);break;
            case Camera::Channel_G: channelWeight = m_chromaticAberrationWeight.y(); returnColor = Color3f(0.0f, 1.0f, 0.0f);break;
            case Camera::Channel_B: channelWeight = m_chromaticAberrationWeight.z(); returnColor = Color3f(0.0f, 0.0f, 1.0f);break;
        }

        /* If DoF, sampled position changes based on lensRadius and focalDistance, from PBR Book 6.2.3 */
        if(m_lensRadius > 0 || m_hasChromaticAberration){
            /* Sample point on lens */
            Point2f pLens = m_lensRadius * Warp::squareToUniformDisk(apertureSample);
            /* Compute point on plane of focus */
            float ft = m_focalDistance / d.z();
            Point3f pFocus = d * ft;
            if(m_hasChromaticAberration){
                /* Chromatic Aberrations effect on pFocus */
                Point2f chromaticAberrationShift = Point2f(samplePosition.x() - 0.5*m_outputSize.x(), samplePosition.y() - 0.5*m_outputSize.y()) / m_outputSize.maxCoeff();
                chromaticAberrationShift *= chromaticAberrationShift.squaredNorm() * channelWeight;
                // std::cout << chromaticAberrationShift.toString()<< std::endl;
                pFocus += Point3f(-chromaticAberrationShift.x(), chromaticAberrationShift.y(), 0.0f);
            }
            /* Update ray according to the effect of the lens, not one-to-one with PBR due to nori */
            Point3f o = Point3f(pLens.x(), pLens.y(), 0.0f);
            ray.o = m_cameraToWorld * o;
            d = (pFocus - o).normalized();
            ray.d = m_cameraToWorld * d;
        }
        else{
            //cout << "XD" << endl;
            ray.o = m_cameraToWorld * Point3f(0, 0, 0);
            ray.d = m_cameraToWorld * d;
        }

        ray.mint = m_nearClip * invZ;
        ray.maxt = m_farClip * invZ;
        ray.update();

        return returnColor;
    }

    Point3f quadraticRadialDistort(Point3f nearP) const{
        float rsq = powf((nearP.x()/nearP.z()), 2) + powf((nearP.x()/nearP.z()), 2);
        float fr = 1 + m_radialDistortionCoeff * rsq;
        nearP.x() *= fr;
        nearP.y() *= fr;
        return nearP;
    }

    bool hasChromaticAberration() const {
        return m_hasChromaticAberration;
    }

    virtual void addChild(NoriObject *obj) override {
        switch (obj->getClassType()) {
            case EReconstructionFilter:
                if (m_rfilter)
                    throw NoriException("Camera: tried to register multiple reconstruction filters!");
                m_rfilter = static_cast<ReconstructionFilter *>(obj);
                break;

            default:
                throw NoriException("Camera::addChild(<%s>) is not supported!",
                    classTypeName(obj->getClassType()));
        }
    }

    /// Return a human-readable summary
    virtual std::string toString() const override {
        return tfm::format(
            "PerspectiveCamera[\n"
            "  cameraToWorld = %s,\n"
            "  outputSize = %s,\n"
            "  fov = %f,\n"
            "  clip = [%f, %f],\n"
            "  rfilter = %s\n"
            "  lensRadius = %s\n"
            "  focalDistance = %s\n"
            "  radialDistortionCoeff = %s\n"
            "  chromaticAberrationWeight = %s\n"
            "]",
            indent(m_cameraToWorld.toString(), 18),
            m_outputSize.toString(),
            m_fov,
            m_nearClip,
            m_farClip,
            indent(m_rfilter->toString()),
            /* Additional prints for DoF */
            m_lensRadius,
            m_focalDistance,
            /* Additional print for Radial Distortion */
            m_radialDistortionCoeff,
            /* Additional print for Chromatic Aberration */
            m_chromaticAberrationWeight.toString()
        );
    }
private:
    Vector2f m_invOutputSize;
    Transform m_sampleToCamera;
    Transform m_cameraToWorld;
    float m_fov;
    float m_nearClip;
    float m_farClip;
    /* Additional params for DoF */
    float m_lensRadius;
    float m_focalDistance;
    /* Additional param for Radial Distortion */
    float m_radialDistortionCoeff;
    /* Additional params for Chromatic Aberration */
    Vector3f m_chromaticAberrationWeight;
    bool m_hasChromaticAberration;
};

NORI_REGISTER_CLASS(PerspectiveCamera, "perspective");
NORI_NAMESPACE_END
