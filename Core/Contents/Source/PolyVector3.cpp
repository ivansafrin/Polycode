/*
 *  PolyVector3.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
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
