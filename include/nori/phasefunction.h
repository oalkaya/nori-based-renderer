#if !defined(__NORI_PHASEFUNCTION_H)
#define __NORI_PHASEFUNCTION_H

#include <nori/object.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

/* PBR Book 11.2 Phase Functions */
class PhaseFunction : public NoriObject{
public:
    static Vector3f samplePIsotropic(const Point2f &u);

    static float pdfPIsotropic();

    static Vector3f samplePHenyeyGreenstein(const Vector3f &wo, const Point2f &u, float g);

    static float pdfPHenyeyGreenstein(float cosTheta, float g);

    virtual EClassType getClassType() const override{
        return EPhaseFunction;
    }
};

NORI_NAMESPACE_END
#endif /* __NORI_PHASEFUNCTION_H */