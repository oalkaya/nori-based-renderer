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

#include <nori/warp.h>
#include <nori/vector.h>
#include <nori/frame.h>

NORI_NAMESPACE_BEGIN

Vector3f Warp::sampleUniformHemisphere(Sampler *sampler, const Normal3f &pole) {
    // Naive implementation using rejection sampling
    Vector3f v;
    do {
        v.x() = 1.f - 2.f * sampler->next1D();
        v.y() = 1.f - 2.f * sampler->next1D();
        v.z() = 1.f - 2.f * sampler->next1D();
    } while (v.squaredNorm() > 1.f);

    if (v.dot(pole) < 0.f)
        v = -v;
    v /= v.norm();

    return v;
}

Point2f Warp::squareToUniformSquare(const Point2f &sample) {
    return sample;
}

float Warp::squareToUniformSquarePdf(const Point2f &sample) {
    return ((sample.array() >= 0).all() && (sample.array() <= 1).all()) ? 1.0f : 0.0f;
}

Point2f Warp::squareToUniformDisk(const Point2f &sample) {
    auto r = sqrtf(sample[0]);
    auto omega = 2*M_PI*sample[1];
    return Point2f(r*cos(omega),r*sin(omega));
}

float Warp::squareToUniformDiskPdf(const Point2f &p) {
    return (p[0]*p[0] + p[1]*p[1] - 1 <= Epsilon) ? (INV_PI) : 0.0f;
}

Vector3f Warp::squareToUniformCylinder(const Point2f &sample){
    auto z = 2*sample[0]-1;
    auto phi = 2*M_PI*sample[1];
    return Vector3f(cos(phi),sin(phi),z);
}

Vector3f Warp::squareToUniformSphereCap(const Point2f &sample, float cosThetaMax) {
    auto cylinder = squareToUniformCylinder(sample);
    auto z = abs(cylinder[2])*(1-cosThetaMax)+(cosThetaMax);
    auto r = sqrtf(1-z*z);
    return Vector3f(r*cylinder[0],r*cylinder[1],z);
}

float Warp::squareToUniformSphereCapPdf(const Vector3f &v, float cosThetaMax) {
    return ((v[0]*v[0] + v[1]*v[1] + v[2]*v[2] - 1 <= Epsilon) && (v[2] >=(cosThetaMax))) ? (INV_PI/(2*(1-cosThetaMax))) : 0.0f;
}

Vector3f Warp::squareToUniformSphere(const Point2f &sample) {
    auto cylinder = squareToUniformCylinder(sample);
    auto r = sqrtf(1-cylinder[2]*cylinder[2]);
    return Vector3f(r*cylinder[0],r*cylinder[1],cylinder[2]);
}

float Warp::squareToUniformSpherePdf(const Vector3f &v) {
    return (v[0]*v[0] + v[1]*v[1] + v[2]*v[2] - 1 <= Epsilon) ? (INV_PI/4) : 0.0f;
}

Vector3f Warp::squareToUniformHemisphere(const Point2f &sample) {
    auto cylinder = squareToUniformCylinder(sample);
    auto z = sample[0];
    auto r = sqrtf(1-z*z);
    return Vector3f(r*cylinder[0],r*cylinder[1],z);
}

float Warp::squareToUniformHemispherePdf(const Vector3f &v) {
    return ((v[0]*v[0] + v[1]*v[1] + v[2]*v[2] - 1 <= Epsilon) && (v[2]>= Epsilon)) ? (INV_PI/2) : 0.0f;
}

Vector3f Warp::squareToCosineHemisphere(const Point2f &sample) {
    auto d = squareToUniformDisk(sample);
    auto z = sqrtf(1-d[0]*d[0]-d[1]*d[1]);
    return Vector3f(d[0],d[1],z);
}

float Warp::squareToCosineHemispherePdf(const Vector3f &v) {
    auto cosTheta = v[2];
    return  ((v[0]*v[0] + v[1]*v[1] + v[2]*v[2] - 1 <= Epsilon) && (v[2]>= Epsilon)) ? cosTheta*INV_PI : 0.0f;
}

Vector3f Warp::squareToBeckmann(const Point2f &sample, float alpha) {
    auto theta = atanf(sqrtf(alpha*alpha*log(1/sample[0])));
    auto z = cos(theta);
    auto phi = 2*M_PI*sample[1];
    return Vector3f(sin(theta)*cos(phi),sin(theta)*sin(phi),z);
}

float Warp::squareToBeckmannPdf(const Vector3f &m, float alpha) {
    auto cosThetasquared = m[2]*m[2];
    auto pdf = expf((cosThetasquared-1)/(cosThetasquared*alpha*alpha))*INV_PI*(1/(alpha*alpha*cosThetasquared*cosThetasquared))*m[2];
    return ((m[0]*m[0] + m[1]*m[1] + m[2]*m[2] - 1 <= Epsilon) && (m[2]>=0)) ? pdf : 0.0f;
}

Vector3f Warp::squareToUniformTriangle(const Point2f &sample) {
    float su1 = sqrtf(sample.x());
    float u = 1.f - su1, v = sample.y() * su1;
    return Vector3f(u,v,1.f-u-v);
}

Vector3f Warp::squareToGTR1(const Point2f &sample, float alpha){
    auto theta = 2.f*M_PI*sample.y();
    auto phi = 0.0f;
    if(alpha<1)
        phi = acos(sqrtf((1-pow(alpha*alpha,1-sample.x()))/(1-alpha*alpha)));
    return Vector3f(sin(phi)*cos(theta),sin(phi)*sin(theta),cos(phi));
}
float Warp::squareToGTR1Pdf(const Vector3f &m, float alpha){
    if(alpha>=1.f)
        return INV_PI;
    auto cosThetasquared = m[2]*m[2];
    float pdf = m[2]*(alpha*alpha-1.f)*INV_PI/(2.f*std::log(alpha)*(1.f+cosThetasquared*(alpha*alpha-1.f)));
    return ((m[0]*m[0] + m[1]*m[1] + m[2]*m[2] - 1 <= Epsilon) && (m[2]>=0)) ? pdf : 0.0f;
}

Vector3f Warp::squareToGTR2a(const Point2f &sample, float ax, float ay){
    auto x = sqrtf(sample.y()/(1-sample.y()))*ax*cos(2*M_PI*sample.x());
    auto y = sqrtf(sample.y()/(1-sample.y()))*ay*sin(2*M_PI*sample.x());
    auto z = 1;
    return Vector3f(x,y,z).normalized();
}
float Warp::squareToGTR2aPdf(const Vector3f &m, float ax, float ay){
    auto cosThetasquared = m[2]*m[2];
    float tmp =((m[0]*m[0])/(ax*ax))+((m[1]*m[1])/(ay*ay))+(m[2]*m[2]);
    float pdf = m[2]*INV_PI/(ax*ay*tmp*tmp);
    return (m[2]>=0) ? pdf : 0.0f;
}

NORI_NAMESPACE_END
