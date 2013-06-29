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
#include "PolyMatrix4.h"
#include "PolyVector3.h"

namespace Polycode {

/**
* Rotation quaternion.
*/
class _PolyExport Quaternion : public PolyBase {
	public:

		/**
		* Construct from w,x,y,z values.
		* @param w W value.
		* @param x X value.
		* @param y Y value.
		* @param z Z value.
		*/ 
		Quaternion(Number w, Number x, Number y, Number z) {
			set(w,x,y,z);
		}

		/**
		* Default constructor.
		*/ 
		Quaternion();
		~Quaternion();

		// ----------------------------------------------------------------------------------------------------------------
		/** @name Public members
		*  Available public members
		*/
		//@{


		inline void setFromMatrix(const Matrix4 &_mat) {
			Number fTrace = _mat.m[0][0]+_mat.m[1][1]+_mat.m[2][2];
			Number fRoot;

			if ( fTrace > 0.0 ) {
				fRoot = sqrtf(fTrace + 1.0);  // 2w
				w = 0.5*fRoot;
				fRoot = 0.5/fRoot;
				x = (_mat.m[2][1]-_mat.m[1][2])*fRoot;
				y = (_mat.m[0][2]-_mat.m[2][0])*fRoot;
				z = (_mat.m[1][0]-_mat.m[0][1])*fRoot;
			} else {
				static size_t s_iNext[3] = { 1, 2, 0 };
				size_t i = 0;
				if ( _mat.m[1][1] > _mat.m[0][0] )
					i = 1;
				if ( _mat.m[2][2] > _mat.m[i][i] )
					i = 2;
				size_t j = s_iNext[i];
				size_t k = s_iNext[j];

				fRoot = sqrtf(_mat.m[i][i]-_mat.m[j][j]-_mat.m[k][k] + 1.0);
				Number* apkQuat[3] = { &x, &y, &z };
				*apkQuat[i] = 0.5*fRoot;
				fRoot = 0.5/fRoot;
				w = (_mat.m[k][j]-_mat.m[j][k])*fRoot;
				*apkQuat[j] = (_mat.m[j][i]+_mat.m[i][j])*fRoot;
				*apkQuat[k] = (_mat.m[k][i]+_mat.m[i][k])*fRoot;
			}
		}

		static Quaternion Slerp(Number fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath=false);
		Number Dot(const Quaternion& rkQ) const;
		Quaternion Log () const;
		Quaternion Exp () const;
		Number Norm () const;
		Number Normalize();
		Quaternion operator+ (const Quaternion& rkQ) const;
		Quaternion operator* (const Quaternion& rkQ) const;
		Quaternion operator* (Number fScalar) const;

		// TODO: implement
		inline void lookAt(const Vector3 &D, const Vector3 &upVector) {
			/*
			Vector3 D;
			Vector3 back = D * -1;
			back.Normalize();

			Vector3 right = back.crossProduct(upVector) ;
			right.Normalize();
			right = right * -1;

			Vector3 up = back.crossProduct(right);

			set( y.z - z.y , z.x - x.z, x.y - y.x, tr + 1.0f ); 
			 */
		}

		void createFromMatrix(const Matrix4& matrix) {
			Number  tr, s, q[4];
			int    i, j, k;

			static const int nxt[3] = {1, 2, 0};

			tr = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];


			// check the diagonal
			if (tr > 0.0f) {
				s = sqrtf(tr + 1.0f);
				w = s / 2.0f;
				s = 0.5f / s;
				x = (matrix.m[1][2] - matrix.m[2][1]) * s;
				y = (matrix.m[2][0] - matrix.m[0][2]) * s;
				z = (matrix.m[0][1] - matrix.m[1][0]) * s;
			} else {
				// diagonal is negative
				i = 0;
				if (matrix.m[1][1] > matrix.m[0][0])
					i = 1;
				if (matrix.m[2][2] > matrix.m[i][i]) 
					i = 2;
				j = nxt[i];
				k = nxt[j];

				s = sqrtf((matrix.m[i][i] - (matrix.m[j][j] + matrix.m[k][k])) + 1.0f);

				q[i] = s * 0.5f;

				if (s != 0.0f)
					s = 0.5f / s;

				q[3] = (matrix.m[j][k] - matrix.m[k][j]) * s;
				q[j] = (matrix.m[i][j] + matrix.m[j][i]) * s;
				q[k] = (matrix.m[i][k] + matrix.m[k][i]) * s;

				x = q[0];
				y = q[1];
				z = q[2];
				w = q[3];
			}

		}


		inline bool operator== (const Quaternion& rhs) const {
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}

		inline bool operator!= (const Quaternion& rhs) const {
			return (rhs.x != x) && (rhs.y != y) &&
				(rhs.z != z) && (rhs.w != w);
		}


		static Quaternion Squad(Number fT, const Quaternion& rkP, const Quaternion& rkA, const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath);
		Quaternion Inverse() const;

		Quaternion operator- () const {
			return Quaternion(-w,-x,-y,-z);
		}

		void set(Number w, Number x, Number y, Number z) {
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Quaternion Inverse() {
			Number fNorm = w*w+x*x+y*y+z*z;
			Number fInvNorm = 1.0/fNorm;
			return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);

		}

		Number InvSqrt(Number x) {
			Number xhalf = 0.5f * x;
			int i = *(int*)&x; // store Numbering-point bits in integer
			i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
			x = *(Number*)&i; // convert new bits into Number
			x = x*(1.5f - xhalf*x*x); // One round of Newton's method
			return x;
		}

		inline void fromAxes(Number az, Number ay, Number ax) {
			ax *= TORADIANS;
			ay *= TORADIANS;
			az *= TORADIANS;
			
			Number c1 = cos(ay / 2.0f);
			Number c2 = cos(ax / 2.0f);
			Number c3 = cos(az / 2.0f);
			
			Number s1 = sin(ay / 2.0f);
			Number s2 = sin(ax / 2.0f);
			Number s3 = sin(az / 2.0f);
			
			w = (c1*c2*c3) - (s1*s2*s3);
			x = (s1*s2*c3) + (c1*c2*s3);
			y = (s1*c2*c3) + (c1*s2*s3);
			z = (c1*s2*c3) - (s1*c2*s3);
		}


		void fromAngleAxis(const Number& rfAngle,
			const Vector3& rkAxis) {
			Number fHalfAngle ( 0.5*rfAngle );
			Number fSin = sin(fHalfAngle);
			w = cos(fHalfAngle);
			x = fSin*rkAxis.x;
			y = fSin*rkAxis.y;
			z = fSin*rkAxis.z;
		}

		void toEulerAngles (Vector3& eulerAngles) {
			// See http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			// q0 = w, q1 = x, q2 = y, q3 = z
			eulerAngles.x = atan2( 2 * ( w * x + y * z), 1 - 2 * (x * x + y * y) );
			eulerAngles.y = asin(2 * ( w * y - z * x));
			eulerAngles.z = atan2( 2 * ( w * z + x * y), 1 - 2 * (y * y + z * z) );
		}

		//-----------------------------------------------------------------------
		void toAngleAxis (Number& rfAngle, Vector3& rkAxis) {
			// The quaternion representing the rotation is
			//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

			Number fSqrLength = x*x+y*y+z*z;
			if ( fSqrLength > 0.0 ) {
				rfAngle = 2.0*acos(w);
				Number fInvLength = InvSqrt(fSqrLength);
				rkAxis.x = x*fInvLength;
				rkAxis.y = y*fInvLength;
				rkAxis.z = z*fInvLength;
			} else {
				// angle is 0 (mod 2*pi), so any axis will do
				rfAngle = Number(0.0);
				rkAxis.x = 1.0;
				rkAxis.y = 0.0;
				rkAxis.z = 0.0;
			}
		}

		void createFromAxisAngle(Number x, Number y, Number z, Number degrees);
		Matrix4 createMatrix() const;

		/**
		 * Rotate a Vector3 by this Quaternion.
		 * @param v Vector to operate on.
		 */
		Vector3 applyTo(Vector3 v) const {
			const Quaternion &q = *this;
			Quaternion result = q * Quaternion(0,v.x,v.y,v.z) * q.Inverse();
			return Vector3(result.x,result.y,result.z);
		}

		Quaternion operator *(Quaternion q);

		Number x;
		Number y;
		Number z;
		Number w;

		//@}			

	protected:

};
}
