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
#include "PolyVector3.h"
#include "PolyVector2.h"
#include "PolyColor.h"
#include <vector>

using std::vector;

namespace Polycode {

	class Bone;
	class _PolyExport BoneAssignment {
		public:
			BoneAssignment(){
				bone = NULL;
			}
			unsigned int boneID;
			Number weight;
			Bone *bone;
	};

	/**
	* A mesh vertex.
	*/
	class _PolyExport Vertex : public Vector3 {
		public:
		
			Vertex();
			Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z);
			Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z, Number u, Number v);		
			Vertex(Number x, Number y, Number z);
			Vertex(Number x, Number y, Number z, Number u, Number v);
			virtual ~Vertex();
			
			void addBoneAssignment(unsigned int boneID, Number boneWeight);
			int getNumBoneAssignments();
			BoneAssignment *getBoneAssignment(unsigned int index);
			
			void normalizeWeights();
			
			Vector2 getTexCoord();
			void setTexCoord(Number u, Number v);
			void setNormal(Number x, Number y, Number z);

			Vector3 restNormal;
			Vector3 normal;
			Vector3 restPosition;

			Color vertexColor;		
			bool useVertexColor;
				
		private:
		
			vector <BoneAssignment*> boneAssignments;
			Vector2 texCoord;
		
	};
}