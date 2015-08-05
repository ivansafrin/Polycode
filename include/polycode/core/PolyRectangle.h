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

namespace Polycode {

	/**
	* Basic rectangle.
	*/
	class _PolyExport Rectangle : public PolyBase {
		public:
			/**
			* Default constructor.
			*/
			Rectangle(){x=0;y=0;w=0;h=0;}
			
			/**
			* Constructor with values.
			*/			
			Rectangle(Number px, Number py, Number pw, Number ph){x=px;y=py;w=pw;h=ph;}
			
			/**
			* Set rectangle values.
			*/						
			void setRect(Number x, Number y, Number w, Number h);

			/**
			* Return a Rectangle formed by clipping this rectangle to the
			* bounds of the passed rectangle.
			*/
			Rectangle Clipped(const Rectangle& rect) const;

			/**
			* Return the minimum X coordinate (the left edge).
			*/
			Number minX() const { return x; }

			/**
			* Return the maximum X coordinate (the right edge).
			*/
			Number maxX() const { return x + w; }

			/**
			 * Return the minimum Y coordinate (the top edge in a Y-down coordinate
			 * system).
			 */
			Number minY() const { return y; }

			/**
			* Return the maximum Y coordinate (the bottom edge in a Y-down coordinate
			* system).
			*/
			Number maxY() const { return y + h; }

			bool operator==(const Rectangle& rect) const;
			bool operator!=(const Rectangle& rect) const { return !(*this == rect); }

			/**
			* X position
			*/									
			Number x;
			/**
			* Y position
			*/												
			Number y;
		
			/**
			* Width
			*/													
			Number w;
			
			/**
			* Height
			*/																
			Number h;
	};
}
