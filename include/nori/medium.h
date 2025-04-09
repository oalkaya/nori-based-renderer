#if !defined(__NORI_MEDIUM_H)
#define __NORI_MEDIUM_H

#include <nori/object.h>

NORI_NAMESPACE_BEGIN

/* MediumIntersection from PBR Book 11.3.1, also incorporating tMax from Lecture slides to fit the structures of similarly named QueryRecords in Nori */
struct MediumQueryRecord {
    /// Point at which the medium intersection occurs
    Point3f p;

    /// Distance to scene intersection
    float tMax;

    /// Outgoing direction (in the local frame), sampled from some phase function after sample() call
    Vector3f wo;

    /* Constructor */
    MediumQueryRecord(const float tMax) : tMax(tMax) {}
};

/* GridDensityMedium from PBR Book 11.3.3 3D Grids */
class Medium : public NoriObject {
public:
    virtual float Tr(Point3f &x0, Point3f &xi, Sampler *sampler) const = 0;

    virtual float sample(const Ray3f &ray, Sampler *sampler, MediumQueryRecord &mi) const = 0;

    virtual std::string toString() const = 0;

    virtual EClassType getClassType() const override {
        return EMedium;
    }
    virtual Color3f get_sigma_a() {return m_sigma_a;}
    virtual Color3f get_sigma_s() {return m_sigma_s;}
    virtual Color3f get_sigma_t() {return m_sigma_t;}
    virtual Color3f get_albedo()  {return m_albedo;}
    virtual float get_g()  {return m_g;}

    virtual void addChild(NoriObject *child) override{}

    Color3f m_sigma_a;
    Color3f m_sigma_s;
    Color3f m_sigma_t;
    Color3f m_albedo;
    float m_g;   
    PhaseFunction *m_phasefunction = nullptr; 
};

NORI_NAMESPACE_END

#endif