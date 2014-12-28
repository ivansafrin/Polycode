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

#pragma once
#include "PolyGlobals.h"
#include "PolyVector3.h"
#include "PolyMatrix4.h"

namespace Polycode {

	/**
	* Ray class. 
	*/
	class _PolyExport Ray : public PolyBase {
		public:
			Ray();
			Ray(const Vector3 &origin, const Vector3 &direction);
	
			Number boxIntersect(const Vector3 &box, const Matrix4 &transformMatrix, float near = 0.0, float far = 9999.0) const;
			
			Vector3 planeIntersectPoint(const Vector3 &planeNormal, Number planeDistance) const;
			Vector3 planeIntersectPoint(const Vector3 &planeNormal, const Vector3 &planePosition) const;
			Ray tranformByMatrix(const Matrix4& matrix) const;

			/**
			* finds the two closest point on the ray to an arbitrary point space.
			*/
			Vector3 closestPointOnRay(const Vector3 &point) const;

			/**
			* finds the two closest points between two rays, returns false if they're parallel.
			*/
			bool closestPointsBetween(const Ray &ray2, Vector3 *point1, Vector3 *point2);
			
			bool polygonIntersect(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3) const;
		
			Vector3 origin;
			Vector3 direction;
			
			Vector3 inv_direction;
			int sign[3];
	};
	
}