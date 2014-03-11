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
	* 4D Vector class.
	*/
	class _PolyExport Vector4 : public PolyBase {
		public:
		
			/**
			* Create from x,y,z coordinates.
			* @param x X coordinate.
			* @param y Y coordinate.			
			* @param z Z coordinate.						
			* @param w W coordinate.
			*/					
			Vector4(Number x,Number y,Number z, Number w);

			/**
			* Create from single value for all coordinates
			* @param val Value for all coordinates
			*/					
			Vector4(Number val);
			
			/**
			* Default constructor.
			*/ 
			Vector4();
			virtual ~Vector4();

			/**
			* Sets the vector from x,y,z coordinates.
			* @param x X coordinate.
			* @param y Y coordinate.			
			* @param z Z coordinate.
            * @param w W coordinate
			*/
			void set(Number x, Number y, Number z, Number w);

			inline Vector4 operator - ( const Vector4& v2 ) const {
				return Vector4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
			}

			
			// ----------------------------------------------------------------------------------------------------------------
			/** @name Operators
			*  Available vector operators.
			*/
			//@{
			

			inline Vector4 operator * (const Number val) const {
				return Vector4(x * val, y * val, z * val, w * val);
			}

			inline Vector4 operator * (const Vector4 &v2) const {
				return Vector4(x * v2.x, y * v2.y, z * v2.z, w * v2.w);
			}


			inline Vector4 operator / (const Number val) const {
				assert( val != 0.0 );
				return operator*(1/val);
			}

			inline Vector4& operator = ( const Vector4& v2)  {
				x = v2.x;
				y = v2.y;
				z = v2.z;
				w = v2.w;
				return *this;
			}

			inline Vector4& operator += ( const Vector4& v2)  {
				x += v2.x;
				y += v2.y;
				z += v2.z;
				w += v2.w;
				return *this;
			}

			inline Vector4& operator -= ( const Vector4& v2)  {
				x -= v2.x;
				y -= v2.y;
				z -= v2.z;
				w -= v2.w;
				return *this;
			}
	
			inline Vector4 operator + ( const Vector4& v2 ) const {
				return Vector4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
			}
        
            inline Vector4 operator - () {
                return Vector4(-x, -y, -z, -w);
            }

			inline bool operator == ( const Vector4& v2)  {
				return (v2.x == x && v2.y == y && v2.z == z && v2.w == w);
			}		

			inline bool operator != ( const Vector4& v2)  {
				return (v2.x != x || v2.y != y || v2.z != z || v2.w != w);
			}				
		
			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
			
			/**
			* Returns the dot product with another vector.
			* @return Dor product with the vector.
			*/			
			inline Number dot(const Vector4 &u) const {
				return x * u.x + y * u.y + z * u.z + w * u.w;
			}

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

            /**
             * W coordinate.
             */
            Number w;

	};
}
