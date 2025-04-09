#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

#include <iostream>
NORI_NAMESPACE_BEGIN

class Direct_mats : public Integrator {
public:
    Direct_mats(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);
        
        
        auto lRec_o = EmitterQueryRecord(ray.o,its.p,its.shFrame.n);
        auto lights = scene->getLights();
      
       
        Color3f L = 0.0f;
        
        if(its.mesh!=NULL && its.mesh->isEmitter()){
            auto startEmitter = its.mesh->getEmitter();
            L = startEmitter->eval(lRec_o);
        }
        
        auto bRec = BSDFQueryRecord(its.toLocal(-ray.d));
       
        bRec.uv = its.uv;
        bRec.p = its.p;
        auto bsdf =its.mesh->getBSDF()->sample(bRec,Point2f(sampler->next2D()));
        
        Intersection its2;
        auto emRay = TRay<Point3f,Vector3f>(its.p,its.toWorld(bRec.wo));
        if(scene->rayIntersect(emRay,its2) && its2.mesh!=NULL && its2.mesh->isEmitter()){
            
            auto em = its2.mesh->getEmitter();
            auto lRec = EmitterQueryRecord(its.p,its2.p,its2.shFrame.n);
            auto c = em->eval(lRec);
            L+=(c*bsdf);
        }
        return L;
    }

    std::string toString() const {
        return "Direct[]";
    }
};


NORI_REGISTER_CLASS(Direct_mats, "direct_mats");
NORI_NAMESPACE_END

