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

#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>
#include <iostream>
#include <nori/bitmap.h>

NORI_NAMESPACE_BEGIN

class EnvMap : public Emitter {
public:
    EnvMap(const PropertyList &props) {
        
        data = Bitmap(props.getString("OpenEXR"));
        m_w = data.cols();
        m_h = data.rows();
        MatrixXf lum = MatrixXf::Zero(m_h,m_w);
        for (int i = 0; i < m_h; i++) {
            for (int j = 0; j < m_w; j++) {
                lum(i,j) = (1/(1000000))*data(i,j).getLuminance();
            }
        }
        
        marginal_p = MatrixXf::Zero(1,m_h);
        marginal_c = MatrixXf::Zero(1,m_h+1);
        pdf_e = MatrixXf::Zero(m_h,m_w);
        cdf = MatrixXf::Zero(m_h,m_w+1);
        
        precompute2D(lum, marginal_p, marginal_c, pdf_e, cdf);
        
    }
    float precompute1D(int u, const MatrixXf &f, MatrixXf &pf, MatrixXf &Pf) const{
        float I = 0;
        Pf(u,0) = 0;
        for(int i = 0; i < f.cols(); i++){
            I += f(u,i);
            pf(u,i) = f(u,i);
            if(i>0){
                Pf(u,i) = Pf(i,i-1);
            }
            Pf(u,f.cols()) = 1;
        }
        if(I==0)
            return 0;
        pf(u) /= I;
        return I;
    }
    void precompute2D(const MatrixXf &lum, MatrixXf &pu, MatrixXf &Pu, MatrixXf &pv, MatrixXf &Pv) const {
        MatrixXf colsum = MatrixXf::Zero(1,m_h);
        for(int i = 0; i < m_h; i++){
            colsum(0,i) = precompute1D(i,lum,pv,Pv);
        }
        precompute1D(0,colsum,pu,Pu);
    }
    int binarySearch(int u, const MatrixXf &Pf,const float &sample) const{
        for(int i = 0; i < Pf.cols(); i++){
            if(sample >= Pf(u,i) && sample < Pf(u,i+1))
                return i;
        }
    }
    void sample1D(int u, const MatrixXf &Pf, const float &sample, float &x) const {
        int i = binarySearch(u,Pf,sample);
        float t = (Pf(u,i+1)-sample)/(Pf(u,i+1)-Pf(u,i));
        x = (1-t)*i+t*(i+1);
    }
    void sample2D(const MatrixXf &Pu,const MatrixXf &Pv, const Point2f & sample, Point2f &uv) const {
        sample1D(0, Pu, sample.x(), uv.x());
        sample1D(uv.x(), Pv, sample.y(), uv.y());
    }

    Vector3f xy_to_dir(const Point2f &xy) const {
        float phi = xy.y() * 2.f * M_PI / (m_w-1);
        float theta = xy.x() * M_PI / (m_h-1);
        return Vector3f(cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta)).normalized();
    }
    Point2f dir_to_xy(const Vector3f &dir) const {
        float theta = sphericalCoordinates(dir).x();
        float phi = sphericalCoordinates(dir).y();
        float x = theta * 0.5 * (m_w-1) /M_PI ;
        float y = phi * (m_h-1) / M_PI ;
        return Point2f(x,y);
    }
    
    Color3f bilint(const Point2f &xy) const{
        int left = floor(xy.y());
        int right = left+1;
        int bottom = floor(xy.x());
        int top = bottom+1;
        
        float w11 = ((right-xy.y())*(top-xy.x()));
        float w12 = ((right-xy.y())*(xy.x()-bottom));
        float w21 = ((xy.y()-left)*(top-xy.x()));
        float w22 = ((xy.y()-left)*(xy.x()-bottom));
        Color3f Q11=0.f,Q12=0.f,Q21 = 0.f,Q22=0.f;
        if(left>=0 && left < m_w && bottom >=0 && bottom < m_h)
            Q11 = data(bottom,left);
        if(left>=0 && left < m_w && top >=0 && top < m_h)
            Q12 = data(top,left);
        if(right>=0 && right < m_w && bottom >=0 && bottom < m_h)
            Q21 = data(bottom,right);
        if(right>=0 && right < m_w && top >=0 && top < m_h)
            Q22 = data(top,right);
        return w11*Q11 + w12*Q12 +w21*Q21+w22*Q22;
    }
    
    virtual std::string toString() const override {
        return "";
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        Point2f xy = dir_to_xy(lRec.wi);
        return bilint(xy);
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        Point2f uv;
        sample2D(marginal_c,cdf,sample,uv);
        lRec.wi =xy_to_dir(uv);
        lRec.shadowRay = Ray3f(lRec.ref,lRec.wi);
        lRec.pdf = pdf(lRec);
        if(lRec.pdf < Epsilon) return Color3f(0.0f);
        return eval(lRec)/lRec.pdf;
        
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        auto jacobian = ((m_w-1)*(m_h-1)*INV_TWOPI*0.5)/Frame::sinTheta(lRec.wi.normalized());
        Point2f xy = dir_to_xy(lRec.wi.normalized());
        if(xy.x()>m_w-1)
            xy.x()=m_w-1;
        if(xy.y()>m_h-1)
            xy.y()=m_h-1;
        return marginal_p(0,xy.x())*pdf_e(xy.x(),xy.y())*jacobian;
    }
    
    virtual bool isEnv() const override{
        return true;
    }

    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {
        return Color3f(0.0f);
    }


protected:
    Bitmap data;
    float m_w;
    float m_h;
    MatrixXf cdf,pdf_e,marginal_c,marginal_p;
};

NORI_REGISTER_CLASS(EnvMap, "env")
NORI_NAMESPACE_END
