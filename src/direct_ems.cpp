#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

#include <iostream>
NORI_NAMESPACE_BEGIN

class Direct_ems : public Integrator {
public:
    Direct_ems(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);
        
        auto lRec = EmitterQueryRecord(its.p);
        auto lRec_o = EmitterQueryRecord(ray.o,its.p,its.shFrame.n);
        auto lights = scene->getLights();
        float rnd = sampler->next1D();
        auto rand2d =Point2f(sampler->next2D());
        auto rndEm = scene->getRandomEmitter(rnd);
        Color3f L = 0.0f;
        
        if(its.mesh!=NULL && its.mesh->isEmitter()){
            auto startEmitter = its.mesh->getEmitter();
            L = startEmitter->eval(lRec_o);
        }
        
        auto c = rndEm->sample(lRec,rand2d);
        auto bRec = BSDFQueryRecord(its.toLocal(lRec.wi),its.toLocal(-ray.d.normalized()),ESolidAngle);
        bRec.uv = its.uv;
        bRec.p = its.p;
        auto bsdf =its.mesh->getBSDF()->eval(bRec);
        auto cos = its.shFrame.cosTheta(its.toLocal(lRec.wi));
        Intersection its2;
        if(!scene->rayIntersect(lRec.shadowRay,its2)){
            L+=(c*cos*bsdf)*lights.size();
        }
        return L;
    }

    std::string toString() const {
        return "Direct[]";
    }
};


NORI_REGISTER_CLASS(Direct_ems, "direct_ems");
NORI_NAMESPACE_END

