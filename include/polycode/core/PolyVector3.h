/*
 Copyright (C) 2011 by Ivan Safrin
 
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
#include <math.h>

//#ifdef _WINDOWS
	#include <assert.h>
//#endif 

namespace Polycode {

	/**
	* 3D Vector class. 
	*/
	class _PolyExport Vector3 : public PolyBase {
		public:
		
			/**
			* Create from x,y,z coordinates.
			* @param x X coordinate.
			* @param y Y coordinate.			
			* @param z Z coordinate.						
			*/					
			Vector3(Number x,Number y,Number z);		

			/**
			* Create from single value for all coordinates
			* @param val Value for all coordinates
			*/					
			Vector3(Number val);
			
			/**
			* Default constructor.
			*/ 
			Vector3();
			virtual ~Vector3();

			/**
			* Sets the vector from x,y,z coordinates.
			* @param x X coordinate.
			* @param y Y coordinate.			
			* @param z Z coordinate.									
			*/
			void set(Number x, Number y, Number z);

			inline Vector3 operator - ( const Vector3& v2 ) const {
				return Vector3(x - v2.x, y - v2.y, z - v2.z);
			}

			/**
			* Returns the distance from this vector to another one.
			* @param vec2 Second vector.
			* @return Distance to the other vector.
			*/
			inline Number distance(const Vector3& vec2) const {
				return (*this - vec2).length();
			}
			
			// ----------------------------------------------------------------------------------------------------------------
			/** @name Operators
			*  Available vector operators.
			*/
			//@{
			

			inline Vector3 operator * (const Number val) const {
				return Vector3(x * val, y * val, z * val);
			}

			inline Vector3 operator * (const Vector3 &v2) const {
				return Vector3(x * v2.x, y * v2.y, z * v2.z);
			}


			inline Vector3 operator / (const Number val) const {
				assert( val != 0.0 );
				return operator*(1/val);
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
        
            inline Vector3 operator - () {
                return Vector3(-x, -y, -z);
            }

			inline bool operator == ( const Vector3& v2)  {
				return (v2.x == x && v2.y == y && v2.z == z);
			}		

			inline bool operator != ( const Vector3& v2)  {
				return (v2.x != x || v2.y != y || v2.z != z);
			}				
		
			//@}
			// ----------------------------------------------------------------------------------------------------------------
	
			/**
			* Returns the angle between this and the specified vectors.
			* @return Angle between the vectors
			*/
			inline Number angleBetween(const Vector3& dest) {
				Number lenProduct = length() * dest.length();
				if(lenProduct < 1e-6f)
					lenProduct = 1e-6f;
				
				Number f = dot(dest) / lenProduct;
				f = clampf(f, -1.0, 1.0);
				return acosf(f);
			}

			/**
			* Returns the vector length.
			* @return Length of the vector.
			*/
			inline Number length () const {
				return sqrtf( x * x + y * y + z * z );
			}

			/**
			* Returns square of the length of the vector.
			* Cheaper to execute than length(), for use when you're just e.g. comparing vector lengths.
			* @return Square length of the vector.
			*/
			inline Number lengthSquared() const {
				return dot(*this);
			}
			
			inline Vector3 setLength(const Number newLength) {
				Number oldLength = length();
				if(oldLength != 0 && newLength != oldLength) {
					(*this) = (*this) * (newLength / oldLength);
				}
				return (*this);
				
			}
			
			/**
			* Returns the dot product with another vector.
			* @return Dor product with the vector.
			*/			
			inline Number dot(const Vector3 &u) const {
				return x * u.x + y * u.y + z * u.z;
			}

			/**
			* Returns the cross product with another vector.
			* @param vec2 Second vector.
			* @return Cross product with the vector.
			*/
			inline Vector3 crossProduct( const Vector3& vec2 ) const {
				return Vector3(
					y * vec2.z - z * vec2.y,
					z * vec2.x - x * vec2.z,
					x * vec2.y - y * vec2.x);
			}			

			/**
			* Normalizes the vector.
			*/
			void Normalize();
		
			/**
			* X coordinate.
			*/
			Number x;
			
			/**
			* Y coordinate.
			*/			
			Number y;
			
			/**
			* Z coordinate.
			*/			
			Number z;			
			
		protected:

	};
}
