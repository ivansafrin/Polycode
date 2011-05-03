/*
 *  PolySkeleton.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/4/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyBone.h"
#include <string>
#include <vector>
#include "PolyBezierCurve.h"
#include "PolyTween.h"

using std::string;
using std::vector;

namespace Polycode {
	
	class _PolyExport BoneTrack {
		public:
			BoneTrack(Bone *bone, Number length);
			~BoneTrack();
			void Play();
			void Stop();
			void Update();
		
			void setSpeed(Number speed);
			
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

			Vector3 ScaleXVec;
			Vector3 ScaleYVec;
			Vector3 ScaleZVec;						
		
		
			Quaternion boneQuat;
			QuaternionTween *quatTween;
			
			Vector3 QuatWVec;
			Vector3 QuatXVec;
			Vector3 QuatYVec;			
			Vector3 QuatZVec;		
		
			
		protected:
		
			Number length;
		
			bool initialized;
		
			Bone *targetBone;
			vector <BezierPathTween*> pathTweens;
		
	};

	class _PolyExport SkeletonAnimation {
		public:
			SkeletonAnimation(String name, Number duration);
			~SkeletonAnimation();			
			void addBoneTrack(BoneTrack *boneTrack);
			String getName();
			void Play();
			void Stop();
			void Update();
		
			void setSpeed(Number speed);
			
		private:
			
			String name;
			Number duration;
			vector<BoneTrack*> boneTracks;
	};

	class _PolyExport Skeleton : public SceneEntity {
		public:
			Skeleton(String fileName);
			Skeleton();
			void loadSkeleton(String fileName);
			~Skeleton();
		
			void playAnimation(String animName);
			void playAnimationByIndex(int index);		
			void addAnimation(String name, String fileName);
			SkeletonAnimation *getAnimation(String name);
			void Update();
			
			Bone *getBoneByName(String name);
			void bonesVisible(bool val);
			void enableBoneLabels(String labelFont, Number size, Number scale, Color labelColor);
					
			int getNumBones();
			Bone *getBone(int index);
		
			SkeletonAnimation *getCurrentAnimation() { return currentAnimation; }
		
		private:
		
			SceneEntity *bonesEntity;
		
			SkeletonAnimation *currentAnimation;
			vector<Bone*> bones;
			vector<SkeletonAnimation*> animations;
	};

}