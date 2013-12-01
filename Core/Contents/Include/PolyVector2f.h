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
#include <assert.h>
	
namespace Polycode {

  namespace Math {
	
		/**
		* Optimized Vector2 class
		* Uses float instead of Number ( which is a double ).
		* Number is twice the size of float and you do not need that much memory for Vectors.
		* I also add the namepace Math so then this can be organized better but it doesnt have to be there.
		*/
		class _PolyExport Vector2f : public PolyBase {

			public:
				
				/**
				* Create from x,y,z coordinates.
				* @param x X coordinate.
				* @param y Y coordinate.									
				*/					
				//Vector2(Number x,Number y);		
				Vector2( float x , float y );

				/**
				* Default constructor.
				*/ 
				Vector2();
				~Vector2();

				/**
				* Sets the vector from x,y,z coordinates.
				* @param x X coordinate.
				* @param y Y coordinate.												
				*/
				void set(float x, float y);

				inline Vector2 operator - ( const Vector2& v2 ) const {
					return Vector2(x - v2.x, y - v2.y);
				}

				/**
				* Returns the distance from this vector to another one.
				* @param vec2 Second vector.
				* @return Distance to the other vector.
				*/
				inline float distance(const Vector2& vec2) const {
					return (*this - vec2).length();
				}
			
				// ----------------------------------------------------------------------------------------------------------------
				/** @name Operators
				*  Available vector operators.
				*/
				//@{
			

				inline Vector2 operator * (const float val) const {
					return Vector2(x * val, y * val);
				}

				inline Vector2 operator / (const float val) const {
					assert( val != 0.0 );
					return operator*(1/val);
				}

				inline Vector2& operator = ( const Vector2& v2)  {
					x = v2.x;
					y = v2.y;
					return *this;
				}

				inline Vector2& operator += ( const Vector2& v2)  {
					x += v2.x;
					y += v2.y;
					return *this;
				}

				inline Vector2& operator -= ( const Vector2& v2)  {
					x -= v2.x;
					y -= v2.y;
					return *this;
				}
	
				inline Vector2 operator + ( const Vector2& v2 ) const {
					return Vector2(x + v2.x, y + v2.y);
				}		


				inline bool operator == ( const Vector2& v2)  {
					return (v2.x == x && v2.y == y);
				}		

				inline bool operator != ( const Vector2& v2)  {
					return (v2.x != x || v2.y != y);
				}				
		
				//@}
				// ----------------------------------------------------------------------------------------------------------------
	

				/**
				* Returns the vector length.
				* @return Length of the vector.
				*/
				inline float length () const {
					return sqrtf( x * x + y * y);
				}
			
				/**
				* Returns the dot product with another vector.
				* @return Dot product with the vector.
				*/			
				inline float dot(const Vector2 &u) const {
					return x * u.x + y * u.y;
				}

				/**
				* Returns the cross product with another vector.
				* @param vec2 Second vector.
				* @return Cross product with the vector.
				*/
				inline float crossProduct( const Vector2& vec2 ) const {
					return x * vec2.y - y * vec2.x;
				}
			
				inline float angle(const Vector2& vec2 ) const {
					Number dtheta,theta1,theta2;
					theta1 = atan2(y,x);
					theta2 = atan2(vec2.y,vec2.x);
					dtheta = theta2 - theta1;
					while (dtheta > PI)
						dtheta -= PI*2.0;
					while (dtheta < -PI)
						dtheta += PI*2.0;
					return(dtheta);
				}									

				/**
				* Normalizes the vector.
				*/
				void Normalize();
		
				/**
				* X coordinate.
				*/
				//Number x;
				float x;
			
				/**
				* Y coordinate.
				*/			
				//Number y;
				float y;
			
					
			protected:

		};

	}
}
