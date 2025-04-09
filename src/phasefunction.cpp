#include <nori/warp.h>
#include <nori/vector.h>
#include <nori/frame.h>
#include <nori/phasefunction.h>

NORI_NAMESPACE_BEGIN
/* Check for wo, wi nomenclature (currently using PBR Book nomenclature) and returns (should it be wi or the float value) */

/* Isotropic sampling */
Vector3f PhaseFunction::samplePIsotropic(const Point2f &u){
    Vector3f wi = Warp::squareToUniformSphere(u);
    //return INV_FOURPI;
    return wi;
}

/* Isotropic sampling pdf */
float PhaseFunction::pdfPIsotropic(){
    return INV_FOURPI;
}

/* HenyeyGreenstein sampling from PBR Book 15.2.3 */
Vector3f PhaseFunction::samplePHenyeyGreenstein(const Vector3f &wo, const Point2f &u, float g){
    /* Compute cosTheta */
    float cosTheta;
    if(std::abs(g) < Epsilon){
        cosTheta = 1 - (2 * u.x());
    }
    else{
        float sqrtterm = (1 - g * g) / (1 - g + 2 * g * u.x());
        cosTheta = (1 + g * g - sqrtterm * sqrtterm) / (2 * g);
    }
    /* Compute wi direction */
    float sinTheta = std::sqrt(std::max(0.0f, 1 - cosTheta * cosTheta));
    float phi = 2 * M_PI * u.y();

    /* Use Frame constructor instead of CoordinateSystem used in PBR Book */
    /* WARNING MIGHT NOT BE WORKING */
    /* woFrame.n = wo */
    Frame woFrame = Frame(wo);

    /* PBR Book SphericalDirection */
    Vector3f wi = sinTheta * std::cos(phi) * woFrame.s + sinTheta * std::sin(phi) * woFrame.t + cosTheta * wo;

    // /* inline PhaseHG */
    // float denom = 1 + g * g + 2 * g * cosTheta;
    // return INV_FOURPI * (1 - g * g ) / (denom * std::sqrt(denom));
    return wi;
}



/* HenyeyGreenstein pdf from PBR Book 15.2.3 */
float PhaseFunction::pdfPHenyeyGreenstein(float cosTheta, float g){

    /* inline PhaseHG */
    float denom = 1 + g * g + 2 * g * cosTheta;
    return INV_FOURPI * (1 - g * g ) / (denom * std::sqrt(denom));
}

NORI_NAMESPACE_END