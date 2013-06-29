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

#include "PolyColor.h"
#include <stdlib.h>

using namespace Polycode;

Color::Color() : r(1),g(1),b(1),a(1){

}

Color::Color(Number r,Number g, Number b, Number a) {
	setColor(r,g,b,a);
}

Color::Color(const Color *color) {
	setColor(color->r, color->g, color->b, color->a);
}

Color::Color(int r,int g, int b, int a) {
	setColorRGBA(r,g,b,a);
}

Color::Color(unsigned int hex) {
	setColorHex(hex);
}

Color Color::ColorWithInts(int r,int g, int b, int a) {
	return Color(r,g,b,a);
}

Color Color::ColorWithHex(unsigned int hex) {
	return Color(hex);
}


void Color::setColorHexRGB(unsigned int hex) {

//	int tr = (hex >> 24) & 0xFF;
	int tr = (hex >> 16) & 0xFF;
	int tg = (hex >> 8) & 0xFF;
	int tb = (hex ) & 0xFF;

	r = ((Number)tr)/255.0f;
	g = ((Number)tg)/255.0f;
	b = ((Number)tb)/255.0f;
//	a = ((Number)ta)/255.0f;

}

void Color::setColorHexFromString(String hex) {
	setColorHex(strtoul(hex.c_str(), 0, 16));
}

void Color::setColorHexRGBFromString(String hex) {
	setColorHexRGB(strtoul(hex.c_str(), 0, 16));
}

Color Color::blendColor(Color c2, int mode, Number amount, Color c3) {
	Color ret;
	Number premul = c2.a * amount;
	switch(mode) {
		case Color::BLEND_NORMAL:
			ret.r = (r * (1.0-premul)) + (c2.r * premul);
			ret.g = (g * (1.0-premul)) + (c2.g * premul);
			ret.b = (b * (1.0-premul)) + (c2.b * premul);
			ret.a = a + premul;
		break;
		case Color::BLEND_REPLACE_COLOR:
			ret.r = (r * (1.0-premul)) + (c3.r * premul);
			ret.g = (g * (1.0-premul)) + (c3.g * premul);
			ret.b = (b * (1.0-premul)) + (c3.b * premul);
			ret.a = a + premul;
		break;
		case Color::BLEND_ADDITIVE:
			ret.r = r + (c2.r);
			ret.g = g + (c2.g);
			ret.b = b + (c2.b);
			ret.a = a + premul;
			if(ret.r > 1.0)
				ret.r = 1.0;
			if(ret.g > 1.0)
				ret.g = 1.0;
			if(ret.b > 1.0)
				ret.b = 1.0;

		break;
	}

	if(ret.a > 1.0)
		ret.a = 1.0;
	return ret;
}

void Color::setColorHex(unsigned int hex) {
	int tr = (hex >> 24) & 0xFF;
	int tg = (hex >> 16) & 0xFF;
	int tb = (hex >> 8) & 0xFF;
	int ta = (hex ) & 0xFF;

	r = ((Number)tr)/255.0f;
	g = ((Number)tg)/255.0f;
	b = ((Number)tb)/255.0f;
	a = ((Number)ta)/255.0f;
}

Number Color::getBrightness() const {
	return (r+g+b) / 3.0f;
}

void Color::RGBtoHSV(const Number &r, const Number &g, const Number &b, Number &h, Number &s, Number &v) {

	double min, max;
	double delta;

	min = MIN(r, g);
	min = MIN(min, b);
	max = MAX(r, g);
	max = MAX(max, b);

	v = max;

	s = (max != 0) ? (max - min) / max : 0;

	if (s == 0) {
		h = 0;
	} else {
		delta = max - min;
		if (r == max) {
			h = (g - b) / delta;
		} else if (g == max) {
			h = 2 + (b - r) / delta;
		} else if (b == max) {
			h = 4 + (r - g) / delta;
		}

		h *= 60;
		if(h < 0) {
			h += 360;
		}
	}
}


Number Color::getHue() const {
	Number h,s,v;
	Color::RGBtoHSV(r,g,b, h,s,v);
	return h;
}

Number Color::getSaturation() const {
	Number h,s,v;
	Color::RGBtoHSV(r,g,b, h,s,v);
	return s;
}

Number Color::getValue() const {
	Number h,s,v;
	Color::RGBtoHSV(r,g,b, h,s,v);
	return v;
}

void Color::setColorHSV(Number H, Number S, Number V) {
	Number r,g,b;

	if (S == 0) {
		r = g = b = V;
	} else {
		int i = (int)(H/60.0f);
		Number f = (H/60.0f) - (Number)i;
		Number p = V*(1.0f-S);
		Number q = V*(1.0f-S*f);
		Number t = V*(1.0f-(1.0f-f)*S);
		switch (i) {
			case 0: r = V; g = t; b = p; break;
			case 1: r = q; g = V; b = p; break;
			case 2: r = p; g = V; b = t; break;
			case 3: r = p; g = q; b = V; break;
			case 4: r = t; g = p; b = V; break;
			case 5: r = V; g = p; b = q; break;
		}
	}

	setColor(r, g, b, a);
}

void Color::Random() {
	setColor((Number)rand()/RAND_MAX, (Number)rand()/RAND_MAX, (Number)rand()/RAND_MAX, 1.0f);
}

void Color::setColorRGB(int r, int g, int b) {
	this->r = ((Number)r)/255.0f;
	this->g = ((Number)g)/255.0f;
	this->b = ((Number)b)/255.0f;
}

void Color::setColorRGBA(int r, int g, int b, int a) {
	this->r = ((Number)r)/255.0f;
	this->g = ((Number)g)/255.0f;
	this->b = ((Number)b)/255.0f;
	this->a = ((Number)a)/255.0f;
}

void Color::setColor(const Color *color) {
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;
	this->a = color->a;
}


void Color::setColor(Number r, Number g, Number b, Number a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

unsigned int Color::getUint() const {

	unsigned int ir = 255.0f*r;
	unsigned int ig = 255.0f*g;
	unsigned int ib = 255.0f*b;
	unsigned int ia = 255.0f*a;

	unsigned int val = ((ia & 0xFF) << 24) | ((ib & 0xFF) << 16) | ((ig & 0xFF) << 8) | (ir & 0xFF);
	return val;
}

Color::~Color() {

}
