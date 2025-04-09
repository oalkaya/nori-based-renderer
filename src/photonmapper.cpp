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

#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/scene.h>
#include <nori/photon.h>

NORI_NAMESPACE_BEGIN

class PhotonMapper : public Integrator {
public:
    /// Photon map data structure
    typedef PointKDTree<Photon> PhotonMap;

    PhotonMapper(const PropertyList &props) {
        /* Lookup parameters */
        m_photonCount  = props.getInteger("photonCount", 1000000);
        m_photonRadius = props.getFloat("photonRadius", 0.0f /* Default: automatic */);
        m_emissionCount = 0;
    }

    virtual void preprocess(const Scene *scene) override {
        cout << "Gathering " << m_photonCount << " photons .. ";
        cout.flush();

        /* Create a sample generator for the preprocess step */
        Sampler *sampler = static_cast<Sampler *>(
            NoriObjectFactory::createInstance("independent", PropertyList()));

        /* Allocate memory for the photon map */
        m_photonMap = std::unique_ptr<PhotonMap>(new PhotonMap());
        m_photonMap->reserve(m_photonCount);

		/* Estimate a default photon radius */
		if (m_photonRadius == 0)
			m_photonRadius = scene->getBoundingBox().getExtents().norm() / 500.0f;

	

		/* How to add a photon?
		 * m_photonMap->push_back(Photon(
		 *	Point3f(0, 0, 0),  // Position
		 *	Vector3f(0, 0, 1), // Direction
		 *	Color3f(1, 2, 3)   // Power
		 * ));
		 */

		// put your code to trace photons here
        auto nlights = scene->getLights().size();
        size_t count = 0;
        while(true){
            if(m_photonCount<=count)
                break;
            Ray3f ray;
            auto rndEm = scene->getRandomEmitter(sampler->next1D());
            auto W = rndEm->samplePhoton(ray,sampler->next2D(),sampler->next2D());
            W*=nlights;
            m_emissionCount++;
            
            while(true){
                
                Intersection its;
                if(!scene->rayIntersect(ray,its) || m_photonCount<=count)
                    break;
                
                
                if(its.mesh->getBSDF()->isDiffuse()){
                    m_photonMap->push_back(Photon(its.p,-ray.d,W));
                    count++;
                }
                
               
                
                auto bRec = BSDFQueryRecord(its.toLocal(-ray.d));
                bRec.uv = its.uv;
                bRec.p = its.p;
                auto bsdf =its.mesh->getBSDF()->sample(bRec,Point2f(sampler->next2D()));
                auto newW = W * bsdf;
                
                auto successProbability = 1-std::fmin(newW.maxCoeff()/W.maxCoeff(), 0.99f);
                //std::cout<<successProbability<<std::endl;
                if(sampler->next1D() < successProbability) break;
                else {
                    W=newW/(1-successProbability);
                }
                
                ray.o = its.p;
                ray.d = its.toWorld(bRec.wo);
                
                ray.update();
            }
            
        }
		/* Build the photon map */
        m_photonMap->build();
    }

    virtual Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &_ray) const override {
    	
		/* How to find photons?
		 * std::vector<uint32_t> results;
		 * m_photonMap->search(Point3f(0, 0, 0), // lookup position
		 *                     m_photonRadius,   // search radius
		 *                     results);
		 *
		 * for (uint32_t i : results) {
		 *    const Photon &photon = (*m_photonMap)[i];
		 *    cout << "Found photon!" << endl;
		 *    cout << " Position  : " << photon.getPosition().toString() << endl;
		 *    cout << " Power     : " << photon.getPower().toString() << endl;
		 *    cout << " Direction : " << photon.getDirection().toString() << endl;
		 * }
		 */

		// put your code for path tracing with photon gathering here
        
        Color3f L = 0.0f;
        Color3f t = 1.0f;
        Ray3f traceRay = _ray;
        
        
        while(true){
            Intersection its;
            if (!scene->rayIntersect(traceRay, its))
                break;
            auto x0 = its.p;
            
            // Contrib from material sampling
            if(its.mesh!=NULL && its.mesh->isEmitter()){
                auto lRec = EmitterQueryRecord(traceRay.o,its.p,its.shFrame.n);
                L+= t*its.mesh->getEmitter()->eval(lRec);
            }
            
            if(its.mesh->getBSDF()->isDiffuse()){

                Color3f Lr = 0.0f;
                std::vector<uint32_t> results;
                m_photonMap->search(x0,m_photonRadius, results);
                for(auto i:results){
                    const Photon &p = (*m_photonMap)[i];
                    auto bRecP = BSDFQueryRecord(its.toLocal(-traceRay.d),its.toLocal(p.getDirection()),ESolidAngle);
                    bRecP.p = p.getPosition();
                    Lr+= (p.getPower()*its.mesh->getBSDF()->eval(bRecP)*INV_PI)/(m_photonRadius*m_photonRadius);
                }

                L+=t*(Lr/m_emissionCount);
                break;
            }

            auto successProbability = fmin(t.maxCoeff(), 0.99);
            if(sampler->next1D() > successProbability) break;
            else t/=successProbability;
            
            auto bRec = BSDFQueryRecord(its.toLocal(-traceRay.d));
            bRec.uv = its.uv;
            bRec.p = x0;
            auto bsdf = its.mesh->getBSDF()->sample(bRec,Point2f(sampler->next2D()));
            t *= bsdf;
            traceRay = Ray3f(x0,its.toWorld(bRec.wo));
            
            
        }

		return L;
    }

    virtual std::string toString() const override {
        return tfm::format(
            "PhotonMapper[\n"
            "  photonCount = %i,\n"
            "  photonRadius = %f\n"
            "]",
            m_photonCount,
            m_photonRadius
        );
    }
private:
    /* 
     * Important: m_photonCount is the total number of photons deposited in the photon map,
     * NOT the number of emitted photons. You will need to keep track of those yourself.
     */ 
    int m_photonCount;
    float m_photonRadius;
    int m_emissionCount;
    std::unique_ptr<PhotonMap> m_photonMap;
};

NORI_REGISTER_CLASS(PhotonMapper, "photonmapper");
NORI_NAMESPACE_END
