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

#include "PolyQuaternion.h"

using namespace Polycode;

Quaternion::Quaternion() : x(0), y(0), z(0), w(1.0f) {

}

Quaternion::~Quaternion() {

}

void Quaternion::createFromAxisAngle(Number ax, Number ay, Number az, Number degrees)
{
	Number angle = Number((degrees / 180.0f) * PI);
	Number result = (Number)sin( angle / 2.0f );
	w = (Number)cos( angle / 2.0f );
	x = Number(ax * result);
	y = Number(ay * result);
	z = Number(az * result);
}

Matrix4 Quaternion::createMatrix() const
{
	Matrix4 m;
	Number fTx  = 2.0*x;
	Number fTy  = 2.0*y;
	Number fTz  = 2.0*z;
	Number fTwx = fTx*w;
	Number fTwy = fTy*w;
	Number fTwz = fTz*w;
	Number fTxx = fTx*x;
	Number fTxy = fTy*x;
	Number fTxz = fTz*x;
	Number fTyy = fTy*y;
	Number fTyz = fTz*y;
	Number fTzz = fTz*z;

	m[0][0] = 1.0-(fTyy+fTzz);
	m[1][0] = fTxy-fTwz;
	m[2][0] = fTxz+fTwy;
	m[0][1] = fTxy+fTwz;
	m[1][1] = 1.0-(fTxx+fTzz);
	m[2][1] = fTyz-fTwx;
	m[0][2] = fTxz-fTwy;
	m[1][2] = fTyz+fTwx;
	m[2][2] = 1.0-(fTxx+fTyy);
	return m;
}

Number Quaternion::Dot (const Quaternion& rkQ) const
{
	return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}

Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
	return Quaternion
	(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
	);
}

Quaternion Quaternion::operator* (Number fScalar) const
{
	return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
}

Quaternion operator* (Number fScalar, const Quaternion& rkQ)
{
	return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y, fScalar*rkQ.z);
}

Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
	return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}

Quaternion Quaternion::Exp () const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	Number fAngle ( sqrtf(x*x+y*y+z*z) );
	Number fSin = sinf(fAngle);

	Quaternion kResult;
	kResult.w = cosf(fAngle);

	if ( fabs(fSin) >= 1e-03 ) {
		Number fCoeff = fSin/fAngle;
		kResult.x = fCoeff*x;
		kResult.y = fCoeff*y;
		kResult.z = fCoeff*z;
	} else {
		kResult.x = x;
		kResult.y = y;
		kResult.z = z;
	}

	return kResult;
}

Quaternion Quaternion::Inverse () const
{
	Number fNorm = w*w+x*x+y*y+z*z;
	if ( fNorm > 0.0 ) {
		Number fInvNorm = 1.0/fNorm;
		return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
	} else {
		// return an invalid result to flag the error
		return Quaternion(0,0,0,0);
	}
}


Quaternion Quaternion::Log () const
{
	Quaternion kResult;
	kResult.w = 0.0;

	if ( fabs(w) < 1.0 ) {
		Number fAngle ( acosf(w) );
		Number fSin = sinf(fAngle);
		if ( fabs(fSin) >= 1e-03 ) {
			Number fCoeff = fAngle/fSin;
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}

Number Quaternion::Norm () const
{
	return w*w+x*x+y*y+z*z;
}

Number Quaternion::Normalize()
{
	Number len = Norm();
	Number factor = 1.0f / sqrtf(len);
	*this = *this * factor;
	return len;
}

Quaternion Quaternion::Slerp(Number fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath)
{
	Number fCos = rkP.Dot(rkQ);
	Quaternion rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath) {
		fCos = -fCos;
		rkT = -rkQ;
	} else {
		rkT = rkQ;
	}

	if (fabs(fCos) < 1 - 1e-03) {
		// Standard case (slerp)
		Number fSin = sqrtf(1 - (fCos*fCos));
		Number fAngle = atan2f(fSin, fCos);
		Number fInvSin = 1.0f / fSin;
		Number fCoeff0 = sinf((1.0f - fT) * fAngle) * fInvSin;
		Number fCoeff1 = sinf(fT * fAngle) * fInvSin;
		return fCoeff0 * rkP + fCoeff1 * rkT;
	} else {
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		Quaternion t = (1.0f - fT) * rkP + fT * rkT;
		// taking the complement requires renormalisation
		t.Normalize();
		return t;
	}
}

Quaternion Quaternion::Squad (Number fT, const Quaternion& rkP, const Quaternion& rkA, const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
{
	Number fSlerpT = 2.0*fT*(1.0-fT);
	Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	Quaternion kSlerpQ = Slerp(fT, rkA, rkB, shortestPath);
	return Slerp(fSlerpT, kSlerpP ,kSlerpQ, shortestPath);
}

Quaternion Quaternion::operator *(Quaternion q)
{
	Quaternion r;

	r.w = w*q.w - x*q.x - y*q.y - z*q.z;
	r.x = w*q.x + x*q.w + y*q.z - z*q.y;
	r.y = w*q.y + y*q.w + z*q.x - x*q.z;
	r.z = w*q.z + z*q.w + x*q.y - y*q.x;

	return r;
}
