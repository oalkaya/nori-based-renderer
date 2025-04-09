#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

class SpotLight : public Emitter{
public:
    SpotLight(const PropertyList &props){
        power = props.getColor("power");
        worldSpacePosition = props.getPoint3("position");
        worldSpaceDirection = props.getVector3("direction");
        cosTotalWidth = (std::cos(degToRad(props.getFloat("cosTotalWidth"))));
        cosFalloffStart = (std::cos(degToRad(props.getFloat("cosFalloffStart"))));
    }
    
    virtual std::string toString() const override {
        return tfm::format(
                "SpotLight[\n"
                "  power = %s,\n"
                "  position = %s,"
                "  direction = %s,"
                "  cosTotalWidth = %f,"
                "  cosFalloffStart = %f"
                "]",
                           power.toString(),worldSpacePosition.toString(),worldSpaceDirection.toString(),cosTotalWidth,cosFalloffStart);
    }
    
    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        auto I =  power/(2.f*M_PI*(1-.5f*(cosFalloffStart+cosTotalWidth)));
        return I*Falloff(-lRec.wi)/((lRec.ref-lRec.p).squaredNorm());
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        
        lRec.wi = (worldSpacePosition-lRec.ref).normalized();
        lRec.p = worldSpacePosition;
        lRec.n = worldSpaceDirection.normalized();
        lRec.shadowRay = Ray3f(lRec.ref,lRec.wi,Epsilon,(worldSpacePosition-lRec.ref).norm()-Epsilon);
        lRec.pdf = 1.0f;
        auto I = power/(2.f*M_PI*(1-.5f*(cosFalloffStart+cosTotalWidth)));
        return I*Falloff(-lRec.wi)/((lRec.ref-lRec.p).squaredNorm());
    }
    
    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        return 1.f;
    }


    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {
        return 0.f;
    }
    
private:
    float Falloff(const Vector3f& w) const {
        float costheta = worldSpaceDirection.normalized().dot(w.normalized());
        if(costheta < cosTotalWidth) return 0.0f;
        if(costheta > cosFalloffStart) return 1.0f;
        float delta = (std::acos(costheta)-std::acos(cosTotalWidth))/(std::acos(cosFalloffStart)-std::acos(cosTotalWidth));
        return delta;
    }
protected:
    Color3f power;
    Point3f worldSpacePosition;
    Vector3f worldSpaceDirection;
    float cosTotalWidth;
    float cosFalloffStart;
    
};

NORI_REGISTER_CLASS(SpotLight, "spot")
NORI_NAMESPACE_END
