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

#include "PolyRectangle.h"
#include <algorithm> // for min/max

using namespace Polycode;

void Rectangle::setRect(Number x, Number y, Number w, Number h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;		
}

Rectangle Rectangle::Clipped(const Rectangle& rect) const
{
	Rectangle result;

	result.x = std::min(std::max(x, rect.x), rect.maxX());
	result.w = std::max(std::min(maxX(), rect.maxX()), result.x) - result.x;

	result.y = std::min(std::max(y, rect.y), rect.maxY());
	result.h = std::max(std::min(maxY(), rect.maxY()), result.y) - result.y;

	return result;
}

bool Rectangle::operator==(const Rectangle& rect) const
{
	if( x == rect.x && y == rect.y && w == rect.w && h == rect.h)
		return true;

	return false;
}
