#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <string>

NORI_NAMESPACE_BEGIN

class AverageVisibilityIntegrator : public Integrator {
public:
    AverageVisibilityIntegrator(const PropertyList &props) {
        len = props.getFloat("length");
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(1.0f);

        Normal3f n = its.shFrame.n;
        Vector3f d = Warp::sampleUniformHemisphere(sampler,n);
        Ray3f r = TRay<Point3f,Vector3f>(its.p,d,Epsilon,len);
        Intersection its2;
        if (!scene->rayIntersect(r, its2))
            return Color3f(1.0f);
        else
            return Color3f(0.0f);
    }

    std::string toString() const {
        return "AverageVisibilityIntegrator[]";
    }
protected:
    float len;
};


NORI_REGISTER_CLASS(AverageVisibilityIntegrator, "av");
NORI_NAMESPACE_END
