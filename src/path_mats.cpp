#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

#include <iostream>
NORI_NAMESPACE_BEGIN

class Path_mats : public Integrator {
public:
    Path_mats(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        
        Ray3f traceRay = ray;
        Color3f L = 0.0f;
        Color3f t = 1.0f;
        
        while(true){
            Intersection its;
            if (!scene->rayIntersect(traceRay, its)){
                auto lRec = EmitterQueryRecord();
                lRec.wi = traceRay.d;
                
                auto env = scene->getEnvEmitter();
                if(env!= NULL){
                    L+= t*env->eval(lRec);
                }
                break;
            }
            auto x0 = its.p;
            
            // Contrib from material sampling
            if(its.mesh!=NULL && its.mesh->isEmitter()){
                auto lRec = EmitterQueryRecord(traceRay.o,its.p,its.shFrame.n);
                L+= t*its.mesh->getEmitter()->eval(lRec);
            }
            
            auto successProbability = fmin(t.maxCoeff(), 0.99);
            if(sampler->next1D() > successProbability) break;
            else t/=successProbability;
            
            auto bRec = BSDFQueryRecord(its.toLocal(-traceRay.d));
            bRec.uv = its.uv;
            bRec.p = x0;
            auto bsdf =its.mesh->getBSDF()->sample(bRec,Point2f(sampler->next2D()));
            t*= bsdf;
            traceRay = Ray3f(x0,its.toWorld(bRec.wo));
            
        }
        
        
        return L;
    }

    std::string toString() const {
        return "Path[]";
    }
};


NORI_REGISTER_CLASS(Path_mats, "path_mats");
NORI_NAMESPACE_END

