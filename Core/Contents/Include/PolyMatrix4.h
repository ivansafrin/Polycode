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
#include <string.h>
#include "PolyGlobals.h"
#include "PolyVector3.h"

namespace Polycode {

class Vector3;

/**
* 4x4 Matrix.
*/
class _PolyExport Matrix4 : public PolyBase {

	public:
		Matrix4();

		/**
		* Construct with 16 matrix values.
		*/ 
		inline Matrix4(
			Number m00, Number m01, Number m02, Number m03,
			Number m10, Number m11, Number m12, Number m13,
			Number m20, Number m21, Number m22, Number m23,
			Number m30, Number m31, Number m32, Number m33 ) {
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		/**
		 * Construct with pointer to 16 Number values.
		 */ 
		Matrix4(const Number *m);
		~Matrix4();

		union {
			Number m[4][4];
			Number ml[16];
		};

		/**
		 * Resets the matrix to identity.
		 */
		inline void identity() {
			memset(ml, 0, sizeof(Number)*16);
			ml[0] = 1;
			ml[5] = 1;
			ml[10] = 1;
			ml[15] = 1;
		}

		/**
		 * Rotates a vector by the matrix values.
		 * @param v2 Vector to rotate.
		 */
		inline Vector3 rotateVector(const Vector3 &v2) const {
			return Vector3(v2.x*m[0][0] + v2.y*m[1][0] + v2.z*m[2][0],
					v2.x*m[0][1] + v2.y*m[1][1] + v2.z*m[2][1],
					v2.x*m[0][2] + v2.y*m[1][2] + v2.z*m[2][2]);
		}

		/**
		 * Returns the position from the matrix.
		 * @return Position.
		 */
		inline Vector3 getPosition() const {
			Vector3 pos;
			pos.x = m[3][0];
			pos.y = m[3][1];
			pos.z = m[3][2];
			return pos;
		}

		// ----------------------------------------------------------------------------------------------------------------
		/** @name Operators
		 *  Available vector operators.
		 */
		//@{


		inline Vector3 operator * ( const Vector3 &v2 ) const {
			return Vector3(v2.x*m[0][0] + v2.y*m[1][0] + v2.z*m[2][0] + m[3][0],
					v2.x*m[0][1] + v2.y*m[1][1] + v2.z*m[2][1] + m[3][1],
					v2.x*m[0][2] + v2.y*m[1][2] + v2.z*m[2][2] + m[3][2]);
		}

		inline Number* operator [] ( int row ) { return m[row];}
		inline const Number* operator [] ( int row ) const { return m[row];}

		inline Matrix4 operator + ( const Matrix4 &m2 ) const {
			Matrix4 r;

			r.m[0][0] = m[0][0] + m2.m[0][0];
			r.m[0][1] = m[0][1] + m2.m[0][1];
			r.m[0][2] = m[0][2] + m2.m[0][2];
			r.m[0][3] = m[0][3] + m2.m[0][3];

			r.m[1][0] = m[1][0] + m2.m[1][0];
			r.m[1][1] = m[1][1] + m2.m[1][1];
			r.m[1][2] = m[1][2] + m2.m[1][2];
			r.m[1][3] = m[1][3] + m2.m[1][3];

			r.m[2][0] = m[2][0] + m2.m[2][0];
			r.m[2][1] = m[2][1] + m2.m[2][1];
			r.m[2][2] = m[2][2] + m2.m[2][2];
			r.m[2][3] = m[2][3] + m2.m[2][3];

			r.m[3][0] = m[3][0] + m2.m[3][0];
			r.m[3][1] = m[3][1] + m2.m[3][1];
			r.m[3][2] = m[3][2] + m2.m[3][2];
			r.m[3][3] = m[3][3] + m2.m[3][3];

			return r;
		}

		inline Matrix4 operator - ( const Matrix4 &m2 ) const {
			Matrix4 r;

			r.m[0][0] = m[0][0] - m2.m[0][0];
			r.m[0][1] = m[0][1] - m2.m[0][1];
			r.m[0][2] = m[0][2] - m2.m[0][2];
			r.m[0][3] = m[0][3] - m2.m[0][3];

			r.m[1][0] = m[1][0] - m2.m[1][0];
			r.m[1][1] = m[1][1] - m2.m[1][1];
			r.m[1][2] = m[1][2] - m2.m[1][2];
			r.m[1][3] = m[1][3] - m2.m[1][3];

			r.m[2][0] = m[2][0] - m2.m[2][0];
			r.m[2][1] = m[2][1] - m2.m[2][1];
			r.m[2][2] = m[2][2] - m2.m[2][2];
			r.m[2][3] = m[2][3] - m2.m[2][3];

			r.m[3][0] = m[3][0] - m2.m[3][0];
			r.m[3][1] = m[3][1] - m2.m[3][1];
			r.m[3][2] = m[3][2] - m2.m[3][2];
			r.m[3][3] = m[3][3] - m2.m[3][3];

			return r;
		}

		inline Matrix4 operator * (const Matrix4 &m2) const {
			Matrix4 r;
			r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
			r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
			r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
			r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

			r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
			r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
			r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
			r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

			r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
			r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
			r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
			r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

			r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
			r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
			r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
			r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

			return r;

		}


		//@}
		// ----------------------------------------------------------------------------------------------------------------

		/**
		 * Sets the position in the matrix.
		 * @param x X coordinate.
		 * @param y Y coordinate.
		 * @param z Z coordinate.
		 */
		inline void setPosition(Number x, Number y, Number z) {
			m[3][0] = x;
			m[3][1] = y;
			m[3][2] = z;
		}

		/**
		 * Sets the scale in the matrix.
		 * @param x X scale.
		 * @param y Y scale.
		 * @param z Z scale.
		 */
		inline void setScale(Vector3 scale) {
			m[0][0] = scale.x;
			m[1][1] = scale.y;
			m[2][2] = scale.z;
		}

		/**
		 * Returns the matrix rotation as euler angles. (This might be kind of buggy).
		 * @param ax Pointer to roll angle to set.
		 * @param ay Pointer to pitch angle to set.
		 * @param az Pointer to yaw angle to set.
		 */
		inline void getEulerAngles(Number *ax, Number *ay, Number *az) const {
			Number angle_x, angle_y, angle_z,tr_x,tr_y,C;

			angle_y = asin(m[0][2]);

			C = cosf(angle_y);
			angle_y *= TODEGREES;

			if(fabsf(C) > 0.005) {
				tr_x      =  m[2][2] / C; // 10 
				tr_y      = -m[1][2]  / C; // 6
				angle_x  = atan2f( tr_y, tr_x ) * TODEGREES;
				tr_x      =  m[0][0] / C; // 0
				tr_y      = -m[0][1] / C; // 1
				angle_z  = atan2f( tr_y, tr_x ) * TODEGREES;
			} else {
				angle_x  = 0;
				tr_x      =  m[1][1];
				tr_y      =  m[1][0];
				angle_z  = atan2f( tr_y, tr_x ) * TODEGREES;
			}

			if (angle_x < 0) 
				angle_x += 360;
			if (angle_y < 0) 
				angle_y += 360;
			if (angle_z < 0) 
				angle_z += 360;

			*ax = -fabs(angle_x);
			*ay = fabs(angle_y);
			*az = -fabs(angle_z);

		}

		/**
		 * Returns the transpose of the matrix.
		 */
		inline Matrix4 transpose() const {
			return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
					m[0][1], m[1][1], m[2][1], m[3][1],
					m[0][2], m[1][2], m[2][2], m[3][2],
					m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		/**
		 * Returns the inverse of the matrix.
		 */
		Matrix4 Inverse() const;

		/**
		 * Returns the affine inverse of the matrix.
		 */			
		Matrix4 inverseAffine() const;

		/**
		 * Returns the determinant of the matrix.
		 */
		Number determinant() const;

		/**
		 * Returns the determinant of any general (square) matrix.
		 * @param a A square matrix as an array of pointers to rows (or columns).
		 * @param n The number of dimensions in matrix A.
		 */
		static Number generalDeterminant(Number const* const*a, int n);

	protected:

};

}
