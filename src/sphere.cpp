/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Romain Prévost

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

#include <nori/shape.h>
#include <nori/bsdf.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <cmath>

NORI_NAMESPACE_BEGIN

class Sphere : public Shape {
public:
    Sphere(const PropertyList & propList) {
        m_position = propList.getPoint3("center", Point3f());
        m_radius = propList.getFloat("radius", 1.f);

        m_bbox.expandBy(m_position - Vector3f(m_radius));
        m_bbox.expandBy(m_position + Vector3f(m_radius));
    }

    virtual BoundingBox3f getBoundingBox(uint32_t index) const override { return m_bbox; }

    virtual Point3f getCentroid(uint32_t index) const override { return m_position; }

    virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const override {
        auto o = ray.o;
        auto d = ray.d;
        auto A = d[0]*d[0] + d[1]*d[1] +d[2]*d[2];
        auto B = 2*(d[0]*(o[0]-m_position[0])+d[1]*(o[1]-m_position[1])+d[2]*(o[2]-m_position[2]));
        auto C = (o[0]-m_position[0])*(o[0]-m_position[0]) +(o[1]-m_position[1])*(o[1]-m_position[1]) +(o[2]-m_position[2])*(o[2]-m_position[2]) - m_radius*m_radius;
        auto delta = B*B-4*A*C;
        bool found = false;
        if(delta == 0){
            auto candidatet = (-B)/(2*A);
            if(candidatet >= 0 && candidatet >= ray.mint && candidatet <= ray.maxt){
                t = candidatet;
                return true;
            }
        }
        else if(delta > 0){
            auto candidatet1 = (-B+sqrt(delta))/(2*A);
            auto candidatet2 = (-B-sqrt(delta))/(2*A);
            if(candidatet1 >= Epsilon && candidatet1 >= ray.mint && candidatet1 <= ray.maxt){
                t = candidatet1;
                found = true;
            }
            if(candidatet2 >= Epsilon && candidatet2 >= ray.mint && candidatet2 <= ray.maxt){
                if(t>candidatet2)
                    t = candidatet2;
                return true;
            }
        }
        return found;

    }

    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const override {
        its.p = ray(its.t);
        its.geoFrame = Frame((its.p-m_position).normalized());
        its.shFrame = its.geoFrame;
        
        its.uv = sphericalCoordinates(its.geoFrame.n);
        
        its.uv[0] = its.uv[0]/(2*M_PI);
        its.uv[1] = its.uv[1]/(M_PI);
        
//        its.shFrame.n = sphericalDirection(its.uv[0],its.uv[0]);
    }

    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const override {
        Vector3f q = Warp::squareToUniformSphere(sample);
        sRec.p = m_position + m_radius * q;
        sRec.n = q;
        sRec.pdf = std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const override {
        return std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }


    virtual std::string toString() const override {
        return tfm::format(
                "Sphere[\n"
                "  center = %s,\n"
                "  radius = %f,\n"
                "  bsdf = %s,\n"
                "  emitter = %s\n"
                "]",
                m_position.toString(),
                m_radius,
                m_bsdf ? indent(m_bsdf->toString()) : std::string("null"),
                m_emitter ? indent(m_emitter->toString()) : std::string("null"));
    }

protected:
    Point3f m_position;
    float m_radius;
};

NORI_REGISTER_CLASS(Sphere, "sphere");
NORI_NAMESPACE_END
