/*
 Copyright (C) 2013 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolyRay.h"
#include <stdio.h>

using namespace Polycode;

Ray::Ray() {
	inv_direction = Vector3(1.0/direction.x, 1.0/direction.y, 1.0/direction.z);
	sign[0] = (inv_direction.x < 0);
	sign[1] = (inv_direction.y < 0);
	sign[2] = (inv_direction.z < 0);
	this->origin = origin;
	this->direction = direction;
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction) {
	inv_direction = Vector3(1.0/direction.x, 1.0/direction.y, 1.0/direction.z);
	sign[0] = (inv_direction.x < 0);
	sign[1] = (inv_direction.y < 0);
	sign[2] = (inv_direction.z < 0);
	this->origin = origin;
	this->direction = direction;
}

Ray Ray::tranformByMatrix(const Matrix4& matrix) const {
	Vector3 pos = matrix * origin;
	Vector3 dir = matrix.rotateVector(direction);
	dir.Normalize();	
	return Ray(pos, dir);
}

Vector3 Ray::planeIntersectPoint(const Vector3 &planeNormal, Number planeDistance) const {
	Number distanceToOrigin = origin.dot(planeNormal) - planeDistance;
	 return origin + direction * (-distanceToOrigin / direction.dot(planeNormal));
}

Vector3 Ray::planeIntersectPoint(const Vector3 &planeNormal, const Vector3 &planePosition) const {
	Number d = (planePosition - origin).dot(planeNormal) / direction.dot(planeNormal);
	return origin + direction * d;
}

bool Ray::polygonIntersect(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) const {

    Number t,u,v;
	t = 0; u = 0; v = 0;

	Vector3 edge1 = v2 - v3;
	Vector3 edge2 = v1 - v3;

	Vector3 tvec, pvec, qvec;
	Number det, inv_det;

	pvec = direction.crossProduct(edge2);
	det = edge1.dot(pvec);

	if (det > -0.00001f)
			return false;

	inv_det = 1.0f / det;

	tvec = origin - v3;

	u = tvec.dot(pvec) * inv_det;
	if (u < -0.001f || u > 1.001f)
			return false;

	qvec = tvec.crossProduct(edge1);

	v = direction.dot(qvec) * inv_det;
	if (v < -0.001f || u + v > 1.001f)
			return false;

	t = edge2.dot(qvec) * inv_det;

	if (t <= 0)
			return false;
			
	return true;
}

Vector3 Ray::closestPointOnRay(const Vector3 &point) const {
	Number b = (point - origin).dot(direction)/ direction.dot(direction);
	return origin + direction*b;
}

bool Ray::closestPointsBetween(const Ray &ray2, Vector3 *point1, Vector3 *point2) {
	Vector3 wOrigin = origin - ray2.origin;

	Number a = direction.dot(direction);
	Number b = direction.dot(ray2.direction);
	Number c = ray2.direction.dot(ray2.direction);
	Number d = direction.dot(wOrigin);
	Number e = ray2.direction.dot(wOrigin);
	Number denom = a*c - b*b;

	if(denom < 0.00001) {
		if(point1)
			*point1 = Vector3(0); 
		if(point2)
			*point2 = Vector3(0); 
		return false;
	}

	Number s = (b*e - c*d)/denom;
	Number t = (a*e - b*d)/denom;

	
	if(point1)
		*point1 = origin + direction*s; 
	if(point2)
		*point2 = ray2.origin + ray2.direction*t; 
	return true;
}

Number Ray::boxIntersect(const Vector3 &box, const Matrix4 &transformMatrix, float near, float far) const {

	if(box.x == 0 || box.y == 0 || box.z == 0)
		return -1.0;

	Ray r  = tranformByMatrix(transformMatrix.Inverse());

	Vector3 bounds[2];
	bounds[0] = Vector3(-box.x * 0.5, -box.y * 0.5, -box.z * 0.5);
	bounds[1] = Vector3(box.x * 0.5, box.y * 0.5, box.z * 0.5);	
	
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	tmin = (bounds[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
	tmax = (bounds[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
	tymin = (bounds[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
	tymax = (bounds[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;

	if ( (tmin > tymax) || (tymin > tmax) )
		return -1.0;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	tzmin = (bounds[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
	tzmax = (bounds[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;
	
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return -1.0;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;
		
	if( (tmin < far) && (tmax > near) ) {
        Vector3 hitpoint = r.origin + (r.direction * fabs(tmin));
        hitpoint = transformMatrix * hitpoint;
        return origin.distance(hitpoint);
    } else {
        return -1.0;
    }
}
