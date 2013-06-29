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

#include "PolyVector3.h"

using namespace Polycode;

Vector3::Vector3() : x(0),y(0),z(0){


}

void Vector3::set(Number x, Number y, Number z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Number x,Number y,Number z) {
	set(x,y,z);
}

Vector3::Vector3(Number val) {
	set(val,val,val);
}

void Vector3::Normalize() {
	Number tL = sqrtf( x * x + y * y + z * z );
	if(tL > 1e-08 ) {
		Number invTl = 1.0 / tL;
		x *= invTl;
		y *= invTl;
		z *= invTl;
	}
}

Vector3::~Vector3() {

}
