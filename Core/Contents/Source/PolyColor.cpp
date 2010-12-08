/*
 *  PolyColor.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyColor.h"

using namespace Polycode;

Color::Color() : r(0),g(0),b(0),a(1){

}

Color::Color(float r,float g, float b, float a) {
	setColor(r,g,b,a);
}

Color::Color(Color *color) {
	setColor(color->r, color->g, color->b, color->a);
}

Color::Color(int r,int g, int b, int a) {
	setColorRGBA(r,g,b,a);
}

Color::Color(unsigned int hex) {
	setColorHex(hex);
}

void Color::setColorHex(unsigned int hex) {
	int tr = (hex >> 24) & 0xFF;
	int tg = (hex >> 16) & 0xFF;
	int tb = (hex >> 8) & 0xFF;
	int ta = (hex ) & 0xFF;
	
	r = ((float)tr)/255.0f;
	g = ((float)tg)/255.0f;
	b = ((float)tb)/255.0f;
	a = ((float)ta)/255.0f;	
}

float Color::getBrightness() {
	return (r+g+b) / 3.0f;
}

void Color::setColorHSV(float H, float S, float V) {
	float r,g,b;
    
	if (S == 0) {
        r = g = b = V;
    } else {
        int i = (int)(H/60.0f);
        float f = (H/60.0f) - (float)i;
        float p = V*(1.0f-S);
        float q = V*(1.0f-S*f);
        float t = V*(1.0f-(1.0f-f)*S);
        switch (i) {
            case 0: r = V;   g = t;  b = p;  break;
            case 1: r = q;  g = V;   b = p;  break;
            case 2: r = p;  g = V;   b = t;  break;
            case 3: r = p;  g = q;  b = V;   break;
            case 4: r = t;  g = p;  b = V;   break;
            case 5: r = V;   g = p;  b = q;  break;
        }
    }

	setColor(r, g, b, a);
}

void Color::Random() {
	setColor((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 1.0f);
}

void Color::setColorRGB(int r, int g, int b) {
	this->r = ((float)r)/255.0f;
	this->g = ((float)g)/255.0f;
	this->b = ((float)b)/255.0f;
}
	
void Color::setColorRGBA(int r, int g, int b, int a) {
	this->r = ((float)r)/255.0f;
	this->g = ((float)g)/255.0f;
	this->b = ((float)b)/255.0f;
	this->a = ((float)a)/255.0f;
}

void Color::setColor(Color *color) {
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;
	this->a = color->a;
}


void Color::setColor(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

unsigned int Color::getUint() {
	
	unsigned int ir = 255.0f*r;
	unsigned int ig = 255.0f*g;
	unsigned int ib = 255.0f*b;
	unsigned int ia = 255.0f*a;
		
	unsigned int val = ((ia & 0xFF) << 24) | ((ib & 0xFF) << 16) | ((ig & 0xFF) << 8) | (ir & 0xFF);
	return val;
}

Color::~Color() {

}