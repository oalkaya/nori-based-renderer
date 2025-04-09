#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
NORI_NAMESPACE_BEGIN

class Direct : public Integrator {
public:
    Direct(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);
        auto lRec = EmitterQueryRecord(its.p);
        Normal3f n = its.shFrame.n;
        auto lights = scene->getLights();
        Color3f sum = Color3f(0.0f,0.0f,0.0f);
        for(auto em : lights){
            auto c = em->sample(lRec,Point2f(.0,.0));
            auto bRec = BSDFQueryRecord(its.toLocal(lRec.wi),its.toLocal(-ray.d.normalized()),ESolidAngle);
            bRec.uv = its.uv;
            auto cos = its.shFrame.cosTheta(its.toLocal(lRec.wi));
            auto bsdf =its.mesh->getBSDF()->eval(bRec);
            Intersection its2;
            if(scene->rayIntersect(lRec.shadowRay,its2))
                continue;
            else
                sum+= c*bsdf*cos;
        }
        
        return sum;
    }

    std::string toString() const {
        return "Direct[]";
    }
};


NORI_REGISTER_CLASS(Direct, "direct");
NORI_NAMESPACE_END

