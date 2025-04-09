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

#if !defined(__NORI_INTEGRATOR_H)
#define __NORI_INTEGRATOR_H

#include <nori/object.h>

NORI_NAMESPACE_BEGIN


/**
 * \brief Abstract integrator (i.e. a rendering technique)
 *
 * In Nori, the different rendering techniques are collectively referred to as 
 * integrators, since they perform integration over a high-dimensional
 * space. Each integrator represents a specific approach for solving
 * the light transport equation---usually favored in certain scenarios, but
 * at the same time affected by its own set of intrinsic limitations.
 */
struct HP{
    Point2f pixel;
    Point3f position;
    Vector3f normal;
    float rad;
    int N;
    Color3f flux;
};

class Integrator : public NoriObject {
public:
    /// Release all memory
    virtual ~Integrator() { }

    /// Perform an (optional) preprocess step
    virtual void preprocess(const Scene *scene) { }

    /**
     * \brief Sample the incident radiance along a ray
     *
     * \param scene
     *    A pointer to the underlying scene
     * \param sampler
     *    A pointer to a sample generator
     * \param ray
     *    The ray in question
     * \return
     *    A (usually) unbiased estimate of the radiance in this direction
     */
    virtual void preprocessPPM(const Scene *scene,int i) {}
    virtual Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const = 0;
    
    virtual Color3f trace_ray_forPPM(const Scene *scene, Sampler *sampler, const Ray3f &_ray, std::vector<nori::HP> &hitpoints, const Point2f &pixel) const {
        return Color3f(1.0f);
    }
    
    virtual Color3f Li_forPPM(const Scene *scene, Sampler *sampler, const Ray3f &ray, nori::HP &hitpoint) const {
        return Color3f(1.0f);
    }

    virtual bool isProgressivePhotonMapper() const {
        return false;
    }
    /**
     * \brief Return the type of object (i.e. Mesh/BSDF/etc.) 
     * provided by this instance
     * */
    virtual EClassType getClassType() const override { return EIntegrator; }
};

NORI_NAMESPACE_END

#endif /* __NORI_INTEGRATOR_H */
