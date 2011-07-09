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
#include "PolySceneMesh.h"
#include "PolyCoreServices.h"

#include <string>
using std::string;

namespace Polycode {

	/**
	* 3D primitive mesh. 
	*/
	
	class _PolyExport ScenePrimitive : public SceneMesh {
		public:
		
			/**
			* Create a primitive mesh of specified type and size.
			* @param type Type of primitive to create. Current types are ScenePrimitive::TYPE_BOX, ScenePrimitive::TYPE_PLANE, ScenePrimitive::TYPE_VPLANE, ScenePrimitive::TYPE_SPHERE, ScenePrimitive::TYPE_CYLINDER, ScenePrimitive::TYPE_CONE and ScenePrimitive::TYPE_TORUS
			*/
			ScenePrimitive(int type, Number v1=1.0f, Number v2=1.0f, Number v3=1.0f,Number v4=0.0f,Number v5=0.0f);
			virtual ~ScenePrimitive();

			/**
			* A cube.
			*/
			static const int TYPE_BOX = 0;		
			/**
			* A plane.
			*/			
			static const int TYPE_PLANE = 1;			
			/**
			* A sphere.
			*/			
			static const int TYPE_SPHERE = 2;
			/**
			* A cylinder.
			*/			
			static const int TYPE_CYLINDER = 3;
			/**
			* A cone.
			*/			
			static const int TYPE_CONE = 4;
			/**
			* A vertical plane.
			*/			
			static const int TYPE_VPLANE = 5;			
			/**
			* A torus.
			*/			
			static const int TYPE_TORUS = 6;			

		
		protected:
		
	};
	
}