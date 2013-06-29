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

#include "PolyMatrix4.h"

using namespace Polycode;

Matrix4::Matrix4() {
	identity();
}

Matrix4::~Matrix4() {

}

Matrix4::Matrix4(const Number *m) {
	memcpy(ml, m, sizeof(Number)*16);
}

Matrix4 Matrix4::Inverse() const
{
	Number m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	Number m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	Number m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	Number m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	Number v0 = m20 * m31 - m21 * m30;
	Number v1 = m20 * m32 - m22 * m30;
	Number v2 = m20 * m33 - m23 * m30;
	Number v3 = m21 * m32 - m22 * m31;
	Number v4 = m21 * m33 - m23 * m31;
	Number v5 = m22 * m33 - m23 * m32;

	Number t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	Number t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	Number t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	Number t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	Number invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	Number d00 = t00 * invDet;
	Number d10 = t10 * invDet;
	Number d20 = t20 * invDet;
	Number d30 = t30 * invDet;

	Number d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Number d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Number d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Number d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	Number d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Number d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Number d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Number d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	Number d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Number d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Number d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Number d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return Matrix4(
		d00, d01, d02, d03,
		d10, d11, d12, d13,
		d20, d21, d22, d23,
		d30, d31, d32, d33);
}

Matrix4 Matrix4::inverseAffine(void) const
{

	Number m10 = m[1][0], m11 = m[1][1], m12 = m[1][2];
	Number m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	Number t00 = m22 * m11 - m21 * m12;
	Number t10 = m20 * m12 - m22 * m10;
	Number t20 = m21 * m10 - m20 * m11;

	Number m00 = m[0][0], m01 = m[0][1], m02 = m[0][2];

	Number invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

	t00 *= invDet; t10 *= invDet; t20 *= invDet;

	m00 *= invDet; m01 *= invDet; m02 *= invDet;

	Number r00 = t00;
	Number r01 = m02 * m21 - m01 * m22;
	Number r02 = m01 * m12 - m02 * m11;

	Number r10 = t10;
	Number r11 = m00 * m22 - m02 * m20;
	Number r12 = m02 * m10 - m00 * m12;

	Number r20 = t20;
	Number r21 = m01 * m20 - m00 * m21;
	Number r22 = m00 * m11 - m01 * m10;

	Number m03 = m[0][3], m13 = m[1][3], m23 = m[2][3];

	Number r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
	Number r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
	Number r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

	return Matrix4(
		r00, r01, r02, r03,
		r10, r11, r12, r13,
		r20, r21, r22, r23,
		  0,   0,   0,   1);
}

Number Matrix4::determinant() const {
	const Number *cols[4] = {m[0],m[1],m[2],m[3]};
	return generalDeterminant(cols, 4);
}

// Determinant function by Edward Popko
// Source: http://paulbourke.net/miscellaneous/determinant/
//==============================================================================
// Recursive definition of determinate using expansion by minors.
//
// Notes: 1) arguments:
//             a (double **) pointer to a pointer of an arbitrary square matrix
//             n (int) dimension of the square matrix
//
//        2) Determinant is a recursive function, calling itself repeatedly
//           each time with a sub-matrix of the original till a terminal
//           2X2 matrix is achieved and a simple determinat can be computed.
//           As the recursion works backwards, cumulative determinants are
//           found till untimately, the final determinate is returned to the
//           initial function caller.
//
//        3) m is a matrix (4X4 in example)  and m13 is a minor of it.
//           A minor of m is a 3X3 in which a row and column of values
//           had been excluded.   Another minor of the submartix is also
//           possible etc.
//             m  a b c d   m13 . . . .
//                e f g h       e f . h     row 1 column 3 is elminated
//                i j k l       i j . l     creating a 3 X 3 sub martix
//                m n o p       m n . p
//
//        4) the following function finds the determinant of a matrix
//           by recursively minor-ing a row and column, each time reducing
//           the sub-matrix by one row/column.  When a 2X2 matrix is
//           obtained, the determinat is a simple calculation and the
//           process of unstacking previous recursive calls begins.
//
//                m n
//                o p  determinant = m*p - n*o
//
//        5) this function uses dynamic memory allocation on each call to
//           build a m X m matrix  this requires **  and * pointer variables
//           First memory allocation is ** and gets space for a list of other
//           pointers filled in by the second call to malloc.
//
//        6) C++ implements two dimensional arrays as an array of arrays
//           thus two dynamic malloc's are needed and have corresponsing
//           free() calles.
//
//        7) the final determinant value is the sum of sub determinants
//
//==============================================================================
Number Matrix4::generalDeterminant(Number const* const*a,int n)
{
	int i,j,j1,j2;                    // general loop and matrix subscripts
	Number det = 0;                   // init determinant
	Number **m = NULL;                // pointer to pointers to implement 2d
	// square array

	if (n < 1) {   }                // error condition, should never get here

	else if (n == 1) {                 // should not get here
		det = a[0][0];
	}

	else if (n == 2)  {                // basic 2X2 sub-matrix determinate
		// definition. When n==2, this ends the
		det = a[0][0] * a[1][1] - a[1][0] * a[0][1];// the recursion series
	}


	// recursion continues, solve next sub-matrix
	else {                             // solve the next minor by building a
		// sub matrix
		det = 0;                      // initialize determinant of sub-matrix

		// for each column in sub-matrix
		for (j1 = 0; j1 < n; j1++) {
			// get space for the pointer list
			m = new Number*[n-1];
			
			for (i = 0; i < n-1; i++)
				m[i] = new Number[n-1];
			//     i[0][1][2][3]  first malloc
			//  m -> +  +  +  +   space for 4 pointers
			//       |  |  |  |          j  second malloc
			//       |  |  |  +-> _ _ _ [0] pointers to
			//       |  |  +----> _ _ _ [1] and memory for
			//       |  +-------> _ a _ [2] 4 doubles
			//       +----------> _ _ _ [3]
			//
			//                   a[1][2]
			// build sub-matrix with minor elements excluded
			for (i = 1; i < n; i++) {
				j2 = 0;               // start at first sum-matrix column position
				// loop to copy source matrix less one column
				for (j = 0; j < n; j++) {
					if (j == j1) continue; // don't copy the minor column element

					m[i-1][j2] = a[i][j];   // copy source element into new sub-matrix
					// i-1 because new sub-matrix is one row
					// (and column) smaller with excluded minors
					j2++;                  // move to next sub-matrix column position
				}
			}

			det += pow(-1.0,1.0 + j1 + 1.0) * a[0][j1] * generalDeterminant(m,n-1);
			// sum x raised to y power
			// recursively get determinant of next
			// sub-matrix which is now one
			// row & column smaller

			for (i = 0 ; i < n-1 ; i++) 
				delete[] m[i];// free the storage allocated to
			// to this minor's set of pointers
			delete[] m;                       // free the storage for the original
			// pointer to pointer
		}
	}
	return(det) ;
}
