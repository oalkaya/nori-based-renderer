/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

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

#if !defined(__NORI_CAMERA_H)
#define __NORI_CAMERA_H

#include <nori/object.h>

NORI_NAMESPACE_BEGIN

/**
 * \brief Generic camera interface
 *
 * This class provides an abstract interface to cameras in Nori and
 * exposes the ability to sample their response function. By default, only
 * a perspective camera implementation exists, but you may choose to
 * implement other types (e.g. an environment camera, or a physically-based
 * camera model that simulates the behavior actual lenses)
 */
class Camera : public NoriObject {
public:
    /**
     * \brief Importance sample a ray according to the camera's response function
     *
     * \param ray
     *    A ray data structure to be filled with a position
     *    and direction value
     *
     * \param samplePosition
     *    Denotes the desired sample position on the film
     *    expressed in fractional pixel coordinates
     *
     * \param apertureSample
     *    A uniformly distributed 2D vector that is used to sample
     *    a position on the aperture of the sensor if necessary.
     *
     * \param RGB
     *    An integer value passed from the render.cpp file in order to index
     *    the color channels. Query done with integers 0 1 2 corresponding to R, G, B
     *    channels respectively.
     *
     * \return
     *    An importance weight associated with the sampled ray.
     *    This accounts for the difference in the camera response
     *    function and the sampling density.
     */
    enum RGBChannel {
        Channel_R = 0,
        Channel_G,
        Channel_B,
        Channel_ALL
    };

    /* Using Channel_ALL as a dummy / default parameter for legacy code compatibility */
    virtual Color3f sampleRay(Ray3f &ray,
        const Point2f &samplePosition,
        const Point2f &apertureSample,
        enum RGBChannel channel = Channel_ALL) const = 0;

    virtual bool hasChromaticAberration() const = 0;

    /// Return the size of the output image in pixels
    const Vector2i &getOutputSize() const { return m_outputSize; }

    /// Return the camera's reconstruction filter in image space
    const ReconstructionFilter *getReconstructionFilter() const { return m_rfilter; }

    /**
     * \brief Return the type of object (i.e. Mesh/Camera/etc.)
     * provided by this instance
     * */
    virtual EClassType getClassType() const override { return ECamera; }
protected:
    Vector2i m_outputSize;
    ReconstructionFilter *m_rfilter;
};

NORI_NAMESPACE_END

#endif /* __NORI_CAMERA_H */
