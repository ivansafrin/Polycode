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
#include "PolyColor.h"
#include "PolyVector3.h"
#include "PolyQuaternion.h"
#include "PolyQuaternionCurve.h"
#include "PolyEntity.h"
#include <vector>

namespace Polycode {
	
	class BezierCurve;
	class Bone;
	class QuaternionTween;
	class BezierPathTween;
	
	class _PolyExport BoneTrack : public PolyBase {
		public:
			BoneTrack(Bone *bone, Number length);
			~BoneTrack();
        
			void Play(bool once=false);
			void Stop();
			void Update(Number elapsed);
            void Reset();
		
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
			
			Vector3 position;
            Vector3 scale;
			Quaternion boneQuat;
            QuaternionCurve *quatCurve;
        
            Number weight;
			
		protected:
		
			Number length;
            Number speed;
            bool paused;
            Number time;
			Bone *targetBone;
            bool playOnce;
		
	};

	/**
	* Skeleton animation.
	*/ 
	class _PolyExport SkeletonAnimation : public PolyBase {
		public:
		
			SkeletonAnimation(const String& name, Number duration);
			~SkeletonAnimation();		
			
			/**
			* Adds a new bone track
			* @param boneTrack New bone track to add.
			*/
			void addBoneTrack(BoneTrack *boneTrack);
			
			/**
			* Returns the animation name.
			*/
			const String& getName() const;
			
			/**
			* Plays the animation.
			*/
			void Play(bool once);			
			/**
			* Stops the animation.
			*/			
			void Stop();
        
            void Reset();
        
			void Update();

			/**
			* Sets the animation multiplier speed.
			* @param speed Number to multiply the animation speed by.
			*/					
			void setSpeed(Number speed);
			
            void setWeight(Number newWeight);
            Number getWeight() const;
        
            bool isPlaying() const;
        
		protected:
			
            Number weight;
            bool playing;
			String name;
			Number duration;
			std::vector<BoneTrack*> boneTracks;
	};

	/**
	* 3D skeleton. Skeletons are applied to scene meshes and can be animated with loaded animations.
	*/
	class _PolyExport Skeleton : public Entity {
		public:
		
			/**
			* Construct skeleton from a skeleton file.
			* @param fileName Skeleton file to load.
			*/
			Skeleton(const String& fileName);

			/**
			* Construct a blank skeleton.
			*/			
			Skeleton();

			/**
			* Construct a blank skeleton.
			*/			
			static Skeleton *BlankSkeleton();
			
			/**
			* Loads a new skeleton from file.
			* @param fileName Skeleton file to load.
			*/ 
			void loadSkeleton(const String& fileName);
			
			virtual ~Skeleton();
		
			/**
			* Play back a loaded animation.
			* @param animName Name of animation to play.
			* @param once If true, will only play the animation once.
			*/
			void playAnimationByName(const String& animName, Number weight = 1.0, bool once = false, bool restartIfPlaying = false);
			

            void playAnimation(SkeletonAnimation *animation, Number weight = 1.0, bool once = false, bool restartIfPlaying = false);
        
            void setBaseAnimationByName(const String &animName);
            void setBaseAnimation(SkeletonAnimation *animation);
        
            void stopAllAnimations();
        
            SkeletonAnimation *getBaseAnimation();
        
			/**
			* Loads in a new animation from a file and adds it to the skeleton.
			* @param name Name of the new animation.
			* @param fileName File to load animation from.
			*/			
			void addAnimation(const String& name, const String& fileName);
			
			/**
			* Returns a SkeletonAnimation by its name.
			* @param Name of animation to return.
			*/
			SkeletonAnimation *getAnimation(const String& name) const;

        
            void stopAnimationByName(const String &name);
            void stopAnimation(SkeletonAnimation *animation);
        
			void Update();
			
			/**
			* Get bone instance by its name
			* @param name Name of the bone.
			*/
			Bone *getBoneByName(const String& name) const;
			
			/**
			* Toggles bone visibility on and off.
			* @param val If true, bones will be rendered, if false, they will not.
			*/
			void bonesVisible(bool val);
								
			/**
			* Returns the number of bones in the skeleton
			*/
			int getNumBones() const;
			
			/**
			* Returns a bone at the specified index.
			* @param index Bone index.
			*/
			Bone *getBone(int index) const;
		
		
		protected:
		
			Entity *bonesEntity;
		
            SkeletonAnimation *baseAnimation;
            std::vector<SkeletonAnimation*> playingAnimations;
			std::vector<Bone*> bones;
			std::vector<SkeletonAnimation*> animations;
	};

}
