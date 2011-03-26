/*
 *  PolyVertex.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 // @package BasicTypes

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
			
			Vector2 *getTexCoord();
			void setTexCoord(Number u, Number v);
			void setNormal(Number x, Number y, Number z);

			Vector3 restNormal;
			Vector3 *normal;
			Vector3 restPosition;

			Color vertexColor;		
			bool useVertexColor;
				
		private:
		
			vector <BoneAssignment*> boneAssignments;
			Vector2 *texCoord;
		
	};
}