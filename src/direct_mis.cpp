#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>

#include <iostream>
NORI_NAMESPACE_BEGIN

class Direct_mis : public Integrator {
public:
    Direct_mis(const PropertyList &props) {
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        /* Find the surface that is visible in the requested direction */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);
        
        
        auto lRec_o = EmitterQueryRecord(ray.o,its.p,its.shFrame.n);
        auto lights = scene->getLights();
       
        Color3f L (0.0f);
        Color3f L_em(0.0f);
        Color3f L_mat(0.0f);
        float p_em_ie = 0.0f;
        float p_em_im = 0.0f;
        float p_mat_ie = 0.0f;
        float p_mat_im = 0.0f;
        
        if(its.mesh!=NULL && its.mesh->isEmitter()){
            auto startEmitter = its.mesh->getEmitter();
            L = startEmitter->eval(lRec_o);
        }
        //EM

        auto lRec = EmitterQueryRecord(its.p);
        float rnd = sampler->next1D();
        auto rand2d =Point2f(sampler->next2D());
        auto rndEm = scene->getRandomEmitter(rnd);
        auto c = rndEm->sample(lRec,rand2d);
        auto bRec = BSDFQueryRecord(its.toLocal(-ray.d),its.toLocal(lRec.wi),ESolidAngle);
        bRec.uv = its.uv;
        bRec.p = its.p;
        auto bsdf =its.mesh->getBSDF()->eval(bRec);
        auto cos = its.shFrame.cosTheta(its.toLocal(lRec.wi));
        Intersection its2;
        if(!scene->rayIntersect(lRec.shadowRay,its2)){
            L_em =(c*cos*bsdf)*lights.size();
            p_em_ie = rndEm->pdf(lRec)/lights.size();
            p_em_im = its.mesh->getBSDF()->pdf(bRec);
        }
        //MAT
        auto bRec2 = BSDFQueryRecord(its.toLocal(-ray.d));
        bRec2.uv = its.uv;
        bRec2.p = its.p;
        bsdf =its.mesh->getBSDF()->sample(bRec2,Point2f(sampler->next2D()));
        
        auto emRay = Ray3f(its.p,its.toWorld(bRec2.wo.normalized()));
        Intersection its3;
        if(scene->rayIntersect(emRay,its3) && its3.mesh!=NULL && its3.mesh->isEmitter()){
            auto em = its3.mesh->getEmitter();
            auto lRec2 = EmitterQueryRecord(its.p,its3.p,its3.shFrame.n);
            auto c = em->eval(lRec2);
            L_mat+=(c*bsdf);
            p_mat_ie = em->pdf(lRec2)/lights.size();
            p_mat_im = its.mesh->getBSDF()->pdf(bRec2);
            
        }
        (p_em_ie>Epsilon)?L+=(p_em_ie/(p_em_ie+p_em_im))*L_em:L+=Color3f(0.0f);
        (p_mat_im>Epsilon)?L+=(p_mat_im/(p_mat_im+p_mat_ie))*L_mat:L+=Color3f(0.0f);
        
    
        return L;
    }

    std::string toString() const {
        return "Direct[]";
    }
};


NORI_REGISTER_CLASS(Direct_mis, "direct_mis");
NORI_NAMESPACE_END

