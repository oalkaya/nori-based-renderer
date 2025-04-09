#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

#include <iostream>
NORI_NAMESPACE_BEGIN

class Path_mis : public Integrator {
public:
    Path_mis(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        
        Ray3f traceRay = ray;
        Color3f L = 0.0f;
        Color3f t = 1.0f;
        
        float w_em =  0.0f;
        float w_mats = 1.0f;
        
        while(true){
            
            Intersection its;
            float p_em_ie = 0.0f;
            float p_em_im = 0.0f;
            float p_mat_ie = 0.0f;
            float p_mat_im = 0.0f;
            
            Color3f L_em(0.0f);
            
            auto lights = scene->getLights();
            
            if (!scene->rayIntersect(traceRay, its)){
                auto lRec = EmitterQueryRecord();
                lRec.wi = traceRay.d;
                auto env = scene->getEnvEmitter();
                if(env!= NULL)
                    L+= t*w_mats*env->eval(lRec);
                break;
            }
                 
            auto x0 = its.p;
            
            // Contrib from material sampling
            if(its.mesh!=NULL && its.mesh->isEmitter()){
                auto lRec = EmitterQueryRecord(traceRay.o,x0,its.shFrame.n);
                L+= t*w_mats*its.mesh->getEmitter()->eval(lRec);
            }
            
            auto successProbability = fmin(t.maxCoeff(), 0.99f);
            if(sampler->next1D() >= successProbability) break;
            else t/=successProbability;
            
            auto bRec = BSDFQueryRecord(its.toLocal(-traceRay.d));
            bRec.uv = its.uv;
            bRec.p = x0;
            auto bsdf =its.mesh->getBSDF()->sample(bRec,Point2f(sampler->next2D()));
            
            if(bRec.measure==EDiscrete){
                w_em = 0.0f;
                w_mats = 1.0f;
            }
            
            else{
                
                Intersection its3;
                auto emRay = Ray3f(x0,its.toWorld(bRec.wo));
                if(scene->rayIntersect(emRay,its3) && its3.mesh!=NULL && its3.mesh->isEmitter()){
                    auto em = its3.mesh->getEmitter();
                    auto lRec2 = EmitterQueryRecord(x0,its3.p,its3.shFrame.n);
                    p_mat_ie = em->pdf(lRec2)/lights.size();
                    p_mat_im = its.mesh->getBSDF()->pdf(bRec);
                    if(p_mat_im>Epsilon) w_mats = (p_mat_im/(p_mat_im+p_mat_ie));
                }
                
                // Contrib from emitter sampling
                
                auto rndEm = scene->getRandomEmitter(sampler->next1D());
                auto lRecEm = EmitterQueryRecord(x0);
                auto cEm = rndEm->sample(lRecEm,sampler->next2D());
                auto bRecEm = BSDFQueryRecord(its.toLocal(-traceRay.d),its.toLocal(lRecEm.wi),ESolidAngle);
                bRecEm.uv = its.uv;
                bRecEm.p = x0;
                auto bsdfEm =its.mesh->getBSDF()->eval(bRecEm);
                auto cosEm = its.shFrame.cosTheta(its.toLocal(lRecEm.wi));
                Intersection its2;
                if(!scene->rayIntersect(lRecEm.shadowRay,its2)){
                    L_em = (cEm*cosEm*bsdfEm)*lights.size();
                    
                    p_em_ie = rndEm->pdf(lRecEm)/lights.size();
                    p_em_im = its.mesh->getBSDF()->pdf(bRecEm);
                    if(p_em_ie>Epsilon) {
                        w_em = p_em_ie/(p_em_ie+p_em_im);
                        L+= t*w_em*L_em;
                    }
                    
                }
                
            }
            
            
            t*= bsdf;
            traceRay.o = x0;
            traceRay.d = its.toWorld(bRec.wo);
            traceRay.update();
            
        }
        
        
        return L;
    }

    std::string toString() const {
        return "Path[]";
    }
};


NORI_REGISTER_CLASS(Path_mis, "path_mis");
NORI_NAMESPACE_END

