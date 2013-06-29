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
#include "PolyScreenMesh.h"

namespace Polycode {

class Polygon;

/**
* 2D primitive. Screen shape can create 2d shapes (Currently only rectangles and circles). 
*/ 
class _PolyExport ScreenShape : public ScreenMesh {
	public:

		/**
		* Create a new shape of specified type and size/options.
		* @param shapeType Type of shape to create. Currently the only options are ScreenShape::SHAPE_RECT and ScreenShape::SHAPE_CIRCLE.
		* @param option1 Width option.
		* @param option2 Height option.
		* @param option3 Number of vertices for the the circle (defaults to 360). Unused for rectangle.
		* @param option4 Reserved.
		*/
		ScreenShape(int shapeType, Number option1=0, Number option2=0, Number option3=0, Number option4=0);

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

		virtual ~ScreenShape();
		void Render();

		/**
		* Sets the color of the shape stroke if it's enabled.
		* @param r Red value 0-1.
		* @param g Green value 0-1
		* @param b Blue value 0-1
		* @param a Alpha value 0-1
		* @see strokeEnabled
		*/
		void setStrokeColor(Number r, Number g, Number b, Number a);

		/**
		* Sets the width of the shape stroke if it's enabled.
		* @param width New stroke width.
		* @see strokeEnabled
		*/
		void setStrokeWidth(Number width);

		/**
		* Colors the shape with a gradient. Radial for circles, linear for rectangles.
		* @param width New stroke width.
		* @param r1 Red value of the first gradient color 0-1.
		* @param g1 Green value of the first gradient color 0-1
		* @param b1 Blue value of the first gradient color 0-1
		* @param a1 Alpha value of the first gradient color 0-1
		* @param r2 Red value of the second gradient color 0-1.
		* @param g2 Green value of the second gradient color 0-1
		* @param b2 Blue value of the second gradient color 0-1
		* @param a2 Alpha value of the second gradient color 0-1
		* @see strokeEnabled
		*/
		void setGradient(Number r1, Number g1, Number b1, Number a1, Number r2, Number g2, Number b2, Number a2);

		/**
		* Removes the gradient from the shape.
		*/
		void clearGradient();

		int getShapeType() const;

		void setShapeType(unsigned int type);

		void setShapeSize(Number newWidth, Number newHeight);

		void buildShapeMesh();

		/**
		* Assignment operator
		*/
		void operator=(const ScreenShape& copy);

		static const int SHAPE_RECT = 1;
		static const int SHAPE_CIRCLE = 2;
		static const int SHAPE_CUSTOM = 4;

		/**
		* If set to true, the shape will be drawn over with a stroke.
		*/
		bool strokeEnabled;

		/**
		* Color of the shape stroke.
		*/
		Color strokeColor;

		/**
		* Width of the shape stroke.
		*/
		Number strokeWidth;

	protected:

		Number option1;
		Number option2;
		Number option3;
		Number option4;

		int shapeType;

};

}
