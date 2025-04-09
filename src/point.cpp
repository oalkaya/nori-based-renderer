#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

class PointLight : public Emitter{
public:
    PointLight(const PropertyList &props){
        power = props.getColor("power");
        worldSpacePosition = props.getPoint3("position");
    }
    
    virtual std::string toString() const override {
        return tfm::format(
                "PointLight[\n"
                "  power = %s,\n"
                "]",
                power.toString());
    }
    
    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        auto I = power/(4*M_PI);
        return (I/((worldSpacePosition-lRec.ref).norm()*(worldSpacePosition-lRec.ref).norm()));
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        
        lRec.wi = (worldSpacePosition-lRec.ref).normalized();
        lRec.shadowRay = TRay<Point3f,Vector3f>(lRec.ref,lRec.wi,Epsilon,(worldSpacePosition-lRec.ref).norm());
        lRec.pdf = pdf(lRec);
        
        return eval(lRec)/lRec.pdf;
    }
    
    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        return 1.f;
    }


    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {
        throw NoriException("To implement...");
    }
    
protected:
    Color3f power;
    Point3f worldSpacePosition;
};

NORI_REGISTER_CLASS(PointLight, "point")
NORI_NAMESPACE_END


