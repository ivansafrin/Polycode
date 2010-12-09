/*
 *  PolySkeleton.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyBone.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Polycode {

	class _PolyExport BoneTrack {
		public:
			BoneTrack(Bone *bone);
			~BoneTrack();
			void Play();
			void Stop();
			void Update();
		
			void setSpeed(float speed);
			
			BezierCurve *scaleX;
			BezierCurve *scaleY;
			BezierCurve *scaleZ;
			BezierCurve *QuatW;
			BezierCurve *QuatX;
			BezierCurve *QuatY;
			BezierCurve *QuatZ;
			BezierCurve *LocX;			
			BezierCurve *LocY;
			BezierCurve *LocZ;
			
			Vector3 LocXVec;
			Vector3 LocYVec;
			Vector3 LocZVec;						

			Quaternion boneQuat;
			QuaternionTween *quatTween;
			
			Vector3 QuatWVec;
			Vector3 QuatXVec;
			Vector3 QuatYVec;			
			Vector3 QuatZVec;		
			
		protected:
			
			bool initialized;
		
			Bone *targetBone;
			vector <BezierPathTween*> pathTweens;
		
	};

	class _PolyExport SkeletonAnimation {
		public:
			SkeletonAnimation(String name, float duration);
			~SkeletonAnimation();			
			void addBoneTrack(BoneTrack *boneTrack);
			String getName();
			void Play();
			void Stop();
			void Update();
		
			void setSpeed(float speed);
			
		private:
			
			String name;
			float duration;
			vector<BoneTrack*> boneTracks;
	};

	class _PolyExport Skeleton : public SceneEntity {
		public:
			Skeleton(String fileName);
			void loadSkeleton(String fileName);
			~Skeleton();
		
			void playAnimation(String animName);
			SkeletonAnimation *getAnimation(String name);
			void Update();
			
			Bone *getBoneByName(String name);
			void bonesVisible(bool val);
			void enableBoneLabels(Font *font, float size, float scale);
					
			int getNumBones();
			Bone *getBone(int index);
		
			SkeletonAnimation *getCurrentAnimation() { return currentAnimation; }
		
		private:
			SkeletonAnimation *currentAnimation;
			vector<Bone*> bones;
			vector<SkeletonAnimation*> animations;
	};

}