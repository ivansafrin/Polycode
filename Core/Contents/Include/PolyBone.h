/*
 *  PolyBone.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyMesh.h"
#include "PolyFont.h"
#include "PolyCoreServices.h"
#include "PolySceneLabel.h"

namespace Polycode {

	class _PolyExport Bone : public SceneEntity {
		public:
			Bone(string boneName);
			~Bone();
			void enableBoneLabel(Font *font, float size, float scale);
			string getName();
			void Render();

			void setParentBone(Bone *bone);
			void addChildBone(Bone *bone);
			Bone* getParentBone();
			int getNumChildBones();
			Bone *getChildBone(unsigned int index);

			Matrix4 getBoneMatrix();
			void setBoneMatrix(Matrix4 matrix);
			Matrix4 getRestMatrix();
			Matrix4 getFullRestMatrix();
			Matrix4 getParentRestMatrix();
			Matrix4 getFinalMatrix();
			void setRestMatrix(Matrix4 matrix);

			int parentBoneId;			
		
		protected:
		
			Matrix4 boneMatrix;
			Matrix4 restMatrix;
			Bone* parentBone;
			vector<Bone*> childBones;
			string boneName;
			Mesh *boneMesh;
	};

}