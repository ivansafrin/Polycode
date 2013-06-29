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
#include "PolyEntity.h"
#include "PolyEventDispatcher.h"

namespace Polycode {

/**
* 3D base entity. SceneEntities are the base class for all 3D entities in Polycode. A thin wrapper around Entity, it inherits most of its functionality.
@see Entity
*/
class _PolyExport SceneEntity : public Entity {
	public:
		SceneEntity();
		virtual ~SceneEntity();

		/**
		* Test mouse collision on the scene entity at a specified screen point. Each SceneEntity subclass must implement this if it wants to support this feature.
		* @param x X position on screen.
		* @param y Y position on screen.
		* @return True if the entity is at the specified screen coordinate.
		*/
		virtual bool testMouseCollision(Number x, Number y) { return false;}

		/**
		* If set to true, will cast shadows (Defaults to true).
		*/
		bool castShadows;

		int collisionShapeType;	

	protected:

};

}
