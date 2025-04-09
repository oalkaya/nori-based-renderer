#include <nori/medium.h>
#include <nori/phasefunction.h>

NORI_NAMESPACE_BEGIN

/* GridDensityMedium from PBR Book 11.3.3 3D Grids */
class HomogeneousMedium : public Medium {
public:
    HomogeneousMedium(const PropertyList &props){
        m_sigma_a = props.getColor("sigma_a", Color3f(0.1f));
        m_sigma_s = props.getColor("sigma_s", Color3f(0.1f));
        m_g = props.getFloat("hg_g", 0.0f);
        /* Delta tracking assumption for spectrally uniform attenuation from PBR book 15.2.2 */
        m_sigma_t = m_sigma_a + m_sigma_s;
        m_albedo = m_sigma_s / m_sigma_t;
    }

    float Tr(Point3f &x0, Point3f &xi, Sampler *sampler) const override{
        /* Compute distance from given 2 points */
        float t = (xi - x0).norm();
        /* Sample channel to compute Tr with */
        int channel = std::min((int) (sampler->next1D() * 3), 2);
        /* Tr(t) = exp(-sigma_t * t) */
        return expf(-1 *  m_sigma_t[channel] * t);
    }

    /* Sample freeFlightDistance */
    float sample(const Ray3f &ray, Sampler *sampler, MediumQueryRecord &mi) const override{
        /* <<Sample a channel and distance along the ray>> from the PBR Book 15.2.1 */
        int channel = std::min((int) (sampler->next1D() * 3), 2);
        float dist = -std::log(1 - sampler->next1D()) / m_sigma_t[channel];
        float t = std::min(dist * ray.d.norm(), mi.tMax);

        /* Set p to the medium scattering point */
        mi.p = (ray.o + ray.d * t);

        /* Sample wo, if m_g not given use Isotropic, else HG */
        if(m_g < Epsilon){
            mi.wo = PhaseFunction::samplePIsotropic(sampler->next2D()); 
        }
        else{
            mi.wo = PhaseFunction::samplePHenyeyGreenstein(-ray.d.normalized(), sampler->next2D(), m_g); 
        }

        return t;
    }

    std::string toString() const override {
        return tfm::format(
            "Sphere[\n"
            "  sigma_a = %s,\n"
            "  sigma_s = %s,\n"
            "  sigma_t = %s,\n"
            "  albedo = %s,\n"
            "  g = %f,\n"
            "]",
            m_sigma_a.toString(),
            m_sigma_s.toString(),
            m_sigma_t.toString(),
            m_albedo.toString(),
            m_g
            );
    }


};

NORI_REGISTER_CLASS(HomogeneousMedium, "homogeneous_medium")
NORI_NAMESPACE_END