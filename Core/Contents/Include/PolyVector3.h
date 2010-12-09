/*
 *  PolyVector3.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 
// @package Math

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include <math.h>

//#ifdef _WINDOWS
	#include <assert.h>
//#endif 

namespace Polycode {

	class _PolyExport Vector3 {
		public:
		
			Vector3();
			Vector3(float x,float y,float z);
			~Vector3();

			void set(float x, float y, float z);

			inline Vector3 operator - ( const Vector3& v2 ) const {
				return Vector3(x - v2.x, y - v2.y, z - v2.z);
			}

			inline float distance(const Vector3& rhs) const {
				return (*this - rhs).length();
			}

			inline Vector3& operator * (const float val) {
				x *= val;
				y *= val;
				z *= val;
				return *this;				
			}

			inline Vector3& operator / (const float val) {
				assert( val != 0.0 );
				x /= val;
				y /= val;
				z /= val;
				return *this;				
			}

			inline Vector3& operator = ( const Vector3& v2)  {
				x = v2.x;
				y = v2.y;
				z = v2.z;
				return *this;
			}

			inline Vector3& operator += ( const Vector3& v2)  {
				x += v2.x;
				y += v2.y;
				z += v2.z;
				return *this;
			}

			inline Vector3& operator -= ( const Vector3& v2)  {
				x -= v2.x;
				y -= v2.y;
				z -= v2.z;
				return *this;
			}
	
			inline Vector3 operator + ( const Vector3& v2 ) const {
				return Vector3(x + v2.x, y + v2.y, z + v2.z);
			}

			inline float length () const {
				return sqrtf( x * x + y * y + z * z );
			}
			
			inline float dot(Vector3 &u) {
				return x * u.x + y * u.y + z * u.z;
			}

			inline Vector3 crossProduct( const Vector3& rkVector ) const {
				return Vector3(
					y * rkVector.z - z * rkVector.y,
					z * rkVector.x - x * rkVector.z,
					x * rkVector.y - y * rkVector.x);
			}			

			void Normalize();
		
			float x;
			float y;
			float z;			
			
		private:

	};
}