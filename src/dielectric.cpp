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

NORI_NAMESPACE_BEGIN

/// Ideal dielectric BSDF
class Dielectric : public BSDF {
public:
    Dielectric(const PropertyList &propList) {
        /* Interior IOR (default: BK7 borosilicate optical glass) */
        m_intIOR = propList.getFloat("intIOR", 1.5046f);

        /* Exterior IOR (default: air) */
        m_extIOR = propList.getFloat("extIOR", 1.000277f);
    }

    virtual Color3f eval(const BSDFQueryRecord &) const override {
        /* Discrete BRDFs always evaluate to zero in Nori */
        return Color3f(0.0f);
    }

    virtual float pdf(const BSDFQueryRecord &) const override {
        /* Discrete BRDFs always evaluate to zero in Nori */
        return 0.0f;
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const override {
        
        auto cosThetaI = Frame::cosTheta(bRec.wi);
        auto refCoeff = fresnel(cosThetaI,m_extIOR,m_intIOR);
        auto _sample = sample;
        bool entering = cosThetaI > 0.f;
        auto etaI = m_intIOR;
        auto etaT = m_extIOR;
        
        bRec.measure = EDiscrete;
        bRec.eta = etaI/etaT;
        
        if (entering) {
            etaI = m_extIOR;
            etaT = m_intIOR;
            cosThetaI = abs(cosThetaI);
        }
        
        if(_sample.x()<=refCoeff){
            bRec.wo = Vector3f(
                -bRec.wi.x(),
                -bRec.wi.y(),
                 bRec.wi.z()
            );
            return Color3f(1.0f);
        }
        else{
            // assuming bRec.wi is in local coordinates
            Vector3f n(0,0,-1);
            if(entering){
                n[2]=1;
            }
            float eta =etaI/etaT;
            auto cos = bRec.wi.dot(n);
            
            bRec.wo = -eta*(bRec.wi-cos*n)-n*sqrtf(1-eta*eta*(1-cos*cos));
//            return Color3f(eta*eta);
            return Color3f(1.0f);
        }
        
        
        
    }

    virtual std::string toString() const override {
        return tfm::format(
            "Dielectric[\n"
            "  intIOR = %f,\n"
            "  extIOR = %f\n"
            "]",
            m_intIOR, m_extIOR);
    }
private:
    float m_intIOR, m_extIOR;
};

NORI_REGISTER_CLASS(Dielectric, "dielectric");
NORI_NAMESPACE_END
