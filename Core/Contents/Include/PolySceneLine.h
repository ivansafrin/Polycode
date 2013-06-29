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
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"

namespace Polycode {

/**
* 3D line class. Can connect two SceneEntity classes with a line.
*/ 
class _PolyExport SceneLine : public SceneEntity {
	public:
		/**
		* Constructs the line with two taraget entities.
		* @param ent1 Starting entity.
		* @param ent2 Ending entity.
		*/
		SceneLine(SceneEntity *ent1, SceneEntity *ent2);

		/**
		* Constructs the line with two taraget positions.
		* @param start Starting position.
		* @param end Ending position.
		*/
		SceneLine(Vector3 start, Vector3 end);

		/**
		* Constructs the line with two taraget positions.
		* @param start Starting position.
		* @param end Ending position.
		*/
		static SceneLine *SceneLineWithPositions(Vector3 start, Vector3 end);

		virtual ~SceneLine();

		void setStart(Vector3 start);
		void setEnd(Vector3 end);

		void Render();

		Number lineWidth;
		bool lineSmooth;

	protected:

		Mesh *mesh;

		Vector3 start;
		Vector3 end;
		SceneEntity *ent1;
		SceneEntity *ent2;
};

}
