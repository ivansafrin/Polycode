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

class Vertex;

/**
* A 2D line between two points or two ScreenEntity instances.
*/ 
class _PolyExport ScreenLine : public ScreenMesh {
	public:
		/**
		* Create a line between two points.
		* @start Starting point.
		* @end Enfing point.
		*/
		ScreenLine(Vector2 start, Vector2 end);

		/**
		* Create a line between two entities. It's automatically updated every frame to follow the entities.
		* @target1 Starting target.
		* @target2 Ending target.
		*/
		ScreenLine(ScreenEntity* target1, ScreenEntity* target2);
		virtual ~ScreenLine();

		void setStart(Vector2 point);
		void setEnd(Vector2 point);

		/**
		* Create a line between two entities. It's automatically updated every frame to follow the entities.
		* @target1 Starting target.
		* @target2 Ending target.
		*/
		static ScreenLine *ScreenLineBetweenEntities(ScreenEntity* target1, ScreenEntity* target2);

		void Update();
		void Render();

		/**
		* Sets the line width.
		* @param width New line width.
		*/
		void setLineWidth(Number width);

	protected:

		void initMesh();

		Number lineWidth;

		Vertex *startVertex;
		Vertex *endVertex;

		ScreenEntity *target1;
		ScreenEntity *target2;

};

}
