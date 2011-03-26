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
#include "PolyString.h"
#include "PolySceneEntity.h"
#include "PolyMesh.h"
#include "PolyCoreServices.h"
#include "PolySceneLabel.h"
#include "PolySceneLine.h"
namespace Polycode {

	class _PolyExport Bone : public SceneEntity {
		public:
			Bone(String boneName);
			~Bone();
			void enableBoneLabel(String labelFont, Number size, Number scale, Color labelColor);
			String getName();
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
			void setBaseMatrix(Matrix4 matrix);
			Matrix4 getBaseMatrix() { return baseMatrix; }
			Matrix4 getFullBaseMatrix();
		
			int parentBoneId;			

			Matrix4 boneMatrix;
			Matrix4 restMatrix;
			Matrix4 baseMatrix;
		
		
		
		protected:
			Mesh *boneMesh;
		
			Bone* parentBone;
			vector<Bone*> childBones;
			String boneName;
	};

}