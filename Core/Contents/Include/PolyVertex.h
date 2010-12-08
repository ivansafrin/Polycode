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
			float weight;
			Bone *bone;
	};

	class _PolyExport Vertex : public Vector3 {
		public:
		
			Vertex();
			Vertex(float pos_x, float pos_y, float pos_z, float nor_x, float nor_y, float nor_z);
			Vertex(float pos_x, float pos_y, float pos_z, float nor_x, float nor_y, float nor_z, float u, float v);		
			Vertex(float x, float y, float z);
			Vertex(float x, float y, float z, float u, float v);
			~Vertex();
			
			void addBoneAssignment(unsigned int boneID, float boneWeight);
			int getNumBoneAssignments();
			BoneAssignment *getBoneAssignment(unsigned int index);
			
			void normalizeWeights();
			
			Vector2 *getTexCoord();
			void setTexCoord(float u, float v);
			void setNormal(float x, float y, float z);

			Vector3 *normal;
			Vector3 restPosition;

			Color vertexColor;		
			bool useVertexColor;
				
		private:
		
			vector <BoneAssignment*> boneAssignments;
			Vector2 *texCoord;
		
	};
}