/*
 *  PolyMatrix4.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/26/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyMatrix4.h"

using namespace Polycode;

Matrix4::Matrix4() {
	init();
}

void Matrix4::init() {
	memset(ml, 0, sizeof(Number)*16);
	ml[0] = 1;
	ml[5] = 1;
	ml[10] = 1;
	ml[15] = 1;		
}

Matrix4::~Matrix4() {

}

Matrix4::Matrix4(Number *m) {
	memcpy(ml, m, sizeof(Number)*16);
}

    Matrix4 Matrix4::inverse() 
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
    //-----------------------------------------------------------------------
    Matrix4 Matrix4::inverseAffine(void) 
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