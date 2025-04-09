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

#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/common.h>
#include <nori/warp.h>
#include <nori/texture.h>

NORI_NAMESPACE_BEGIN


class DisneyBSDF : public BSDF {
public:
    DisneyBSDF(const PropertyList &propList) {
        if(propList.has("albedo")) {
            PropertyList l;
            l.setColor("value", propList.getColor("albedo"));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
        }
        m_roughness = propList.getFloat("roughness", 0.0f);
        m_subsurface = propList.getFloat("subsurface", 0.0f);
        m_metallic = propList.getFloat("metallic",0.0f);
        m_anisotropic = propList.getFloat("anisotropic",0.0f);
        m_clearcoatGloss = propList.getFloat("clearcoatGloss",0.0f);
        m_clearcoat = propList.getFloat("clearcoat",0.0f);
    }
    
    /// Add texture for the albedo
    virtual void addChild(NoriObject *obj) override {
        switch (obj->getClassType()) {
            case ETexture:
                if(obj->getIdName() == "albedo") {
                    if (m_albedo)
                        throw NoriException("There is already an albedo defined!");
                    m_albedo = static_cast<Texture<Color3f> *>(obj);
                }
                else {
                    throw NoriException("The name of this texture does not match any field!");
                }
                break;

            default:
                throw NoriException("Diffuse::addChild(<%s>) is not supported!",
                                    classTypeName(obj->getClassType()));
        }
    }

    virtual void activate() override {
        if(!m_albedo) {
            PropertyList l;
            l.setColor("value", Color3f(0.5f));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
            m_albedo->activate();
        }
    }

    float GGX(const Vector3f w, float ax, float ay) const {
        if(m_anisotropic>0){
            float delta = 0.5*(sqrtf(1+((w.x()*ax)*(w.x()*ax)+(w.y()*ay)*(w.y()*ay))/(w.z()*w.z()))-1);
            return 1.0f/(1+delta);
        }
        auto cosTheta = Frame::cosTheta(w);
        float asquared = ax * ax;
        float cosThetasquared = cosTheta * cosTheta;
       
        return 1.f / (cosTheta + sqrt(cosThetasquared + asquared - asquared * cosThetasquared));
    }
    
    float Schlick(float x) const{
        x = clamp(1.f - x, 0.f, 1.f);
        return pow(x, 5);
    }
    
    float D(const BSDFQueryRecord &bRec, float ax, float ay) const {
        auto wh = (bRec.wi + bRec.wo).normalized();
        auto den = (wh.x()*wh.x())/(ax*ax)+(wh.y()*wh.y())/(ay*ay)+wh.z()*wh.z();
        return (INV_PI)/(ax*ay*den*den);
    }
    Color3f Fresnel(const BSDFQueryRecord &bRec,Color3f baseColor) const {
        auto wh = (bRec.wi + bRec.wo).normalized();
        auto nwi = Schlick(std::abs(bRec.wi.dot(wh)));
        return m_metallic*baseColor + (Color3f(1.0f)-m_metallic*baseColor)*nwi;
    }
    float GTR1(const BSDFQueryRecord &bRec) const {
        auto wh = (bRec.wi + bRec.wo).normalized();
        float ag = (1-m_clearcoatGloss)*0.1+m_clearcoatGloss*0.001;
        if(ag>=1){
            return INV_PI;
        }
        float num = (ag*ag-1)*INV_PI;
        float den = log(ag*ag)*(1+(ag*ag-1)*wh.z()*wh.z());
        return num/den;
    }
   
    virtual Color3f eval(const BSDFQueryRecord &bRec) const override {
        if (bRec.measure != ESolidAngle
            || Frame::cosTheta(bRec.wi) <= 0
            || Frame::cosTheta(bRec.wo) <= 0)
            return Color3f(0.0f);
        
        Vector3f wh = (bRec.wi + bRec.wo).normalized();
        auto baseColor = m_albedo->eval(bRec.uv);
        
        // Diffuse
        auto nwi =Schlick(Frame::cosTheta(bRec.wi));
        auto nwo =Schlick(Frame::cosTheta(bRec.wo));
        auto Fd90 = 0.5 + 2*m_roughness*pow(std::abs(wh.dot(bRec.wi.normalized())),2);
        auto Fdi = 1+(Fd90-1)*nwi;
        auto Fdo = 1+(Fd90-1)*nwo;
        Color3f baseDiffuse = baseColor * INV_PI * Fdi*Fdo;
                              
        auto Fss90 = m_roughness*pow(std::abs(wh.dot(bRec.wi.normalized())),2);
        auto Fssi = 1+(Fss90-1)*nwi;
        auto Fsso = 1+(Fss90-1)*nwo;
        Color3f subsurface = 1.25*INV_PI*baseColor*(Fssi*Fsso*(1.0f/(Frame::cosTheta(bRec.wo)+Frame::cosTheta(bRec.wi))-0.5)+0.5);
        Color3f diffuse = (1-m_subsurface)*baseDiffuse+m_subsurface*subsurface;
        
        // Metal
        auto aspect = sqrt(1-0.9*m_anisotropic);
        auto ax = fmax(0.0001,(m_roughness*m_roughness)/aspect);
        auto ay = fmax(0.0001,m_roughness*m_roughness*aspect);
        auto Gm = GGX(bRec.wi,ax,ay)*GGX(bRec.wo,ax,ay);
        auto Dm = Warp::squareToGTR2aPdf(wh,ax,ay);
        auto Fm = Fresnel(bRec,baseColor);
        Color3f metal = (Fm*Dm*Gm);
        
        
        //Clearcoat
        auto Gc = GGX(bRec.wi,0.25,0.25)*GGX(bRec.wo,0.25,0.25);
        auto Fc = 0.04+(1-0.04)*Schlick(std::abs(wh.dot(bRec.wi)));
        auto Dc = GTR1(bRec);
        Color3f clearcoat = Fc*Dc*Gc;
                    
        return (1-m_metallic)*diffuse+metal+0.25*m_clearcoat*clearcoat;
  
    }

    virtual float pdf(const BSDFQueryRecord &bRec) const override {
        /* Discrete BRDFs always evaluate to zero in Nori */
        
        float cosTheta = Frame::cosTheta(bRec.wo);
        if(cosTheta<=0)
            return 0.0f;
        Vector3f wh = (bRec.wi + bRec.wo).normalized();
        
        
        float diffuse = (1.f-m_metallic)*0.5f;
        float metal = 1.f / (1.f + m_clearcoat);;
        // Jacobian
        float J = 1.f/(4.f*abs(bRec.wo.dot(wh)));
        auto aspect = sqrt(1-0.9*m_anisotropic);
        auto ax = fmax(0.0001,(m_roughness*m_roughness)/aspect);
        auto ay = fmax(0.0001,m_roughness*m_roughness*aspect);
        auto alpha = (1-m_clearcoatGloss)*0.1 +m_clearcoatGloss*0.001;
        
        auto cosThetaWh = Frame::cosTheta(wh);
        auto pdfD = Warp::squareToCosineHemispherePdf(bRec.wo);
        auto pdfM = Warp::squareToGTR2aPdf(wh,ax,ay)*J*cosThetaWh;
        auto pdfC = Warp::squareToGTR1Pdf(wh,alpha)*J*cosThetaWh;
        
        return diffuse*pdfD + (1-diffuse)*(metal*pdfM+(1-metal)*pdfC);
        
        
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);
        bRec.measure = ESolidAngle;
        auto _sample = sample;
        
        //Diffuse
        float diffuse =(1.f-m_metallic)*0.5f;
        if(_sample.x() < diffuse){
            _sample.x() /= diffuse;
            bRec.wo = Warp::squareToCosineHemisphere(_sample);
        }
        else{
            //Specular
            _sample.x() = (_sample.x() - diffuse)/(1.f - diffuse);
            
            float metal = 1.f / (1.f + m_clearcoat);
            Vector3f wh;
            if(_sample.x() < metal){
                //Metal
                _sample.x() /= metal;
                auto aspect = sqrt(1-0.9*m_anisotropic);
                auto ax = fmax(0.0001,(m_roughness*m_roughness)/aspect);
                auto ay = fmax(0.0001,m_roughness*m_roughness*aspect);
                wh = Warp::squareToGTR2a(_sample,ax,ay);
            }
            else{
                //ClearCoat
                _sample.x() = (_sample.x() - metal)/(1.f - metal);
                auto alpha = (1-m_clearcoatGloss)*0.1 +m_clearcoatGloss*0.001;
                wh = Warp::squareToGTR1(_sample,alpha);
            }
            //Reflection
            bRec.wo = (-bRec.wi + 2 * bRec.wi.dot(wh) * wh).normalized();
            
        }
        
        float cosTheta = Frame::cosTheta(bRec.wo);
        if (cosTheta <= 0.f)
            return 0;

        return eval(bRec) * cosTheta / pdf(bRec);
        
    }

    virtual std::string toString() const override {
        return tfm::format(
            "DisneyBSDF[\n"
            "  m_metallic = %f,\n"
            "  m_roughness = %f,\n"
            "  m_subsurface = %f,\n"
            "  m_anisotropic = %f,\n"
            "  m_clearcoat = %f\n"
            "  m_clearcoatGloss = %f,\n"
            "]",
            m_metallic, m_roughness, m_subsurface, m_anisotropic,m_clearcoat,m_clearcoatGloss);
    }
private:
    Texture<Color3f> * m_albedo;
    float m_roughness, m_subsurface, m_metallic,m_anisotropic,m_clearcoat,m_clearcoatGloss;
};

NORI_REGISTER_CLASS(DisneyBSDF, "disney");
NORI_NAMESPACE_END

