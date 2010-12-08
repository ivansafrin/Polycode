/*
 *  PolySkeleton.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySkeleton.h"

using namespace Polycode;

Skeleton::Skeleton(string fileName) : SceneEntity() {
	loadSkeleton(fileName);
	currentAnimation = NULL;
}

Skeleton::~Skeleton() {
}

int Skeleton::getNumBones() {
	return bones.size();
}

Bone *Skeleton::getBoneByName(string name) {
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->getName() == name)
			return bones[i];
	}
	return NULL;
}

Bone *Skeleton::getBone(int index) {
	return bones[index];
}

void Skeleton::enableBoneLabels(Font *font, float size, float scale) {
	for(int i=0; i < bones.size(); i++) {
		bones[i]->enableBoneLabel(font, size, scale);
	}	
}

void Skeleton::playAnimation(string animName) {
	SkeletonAnimation *anim = getAnimation(animName);
	if(!anim)
		return;
	
	if(anim == currentAnimation)
		return;
	
	if(currentAnimation)
		currentAnimation->Stop();
		
	currentAnimation = anim;
	anim->Play();
}

SkeletonAnimation *Skeleton::getAnimation(string name) {
	for(int i=0; i < animations.size(); i++) {
		if(animations[i]->getName() == name)
			return animations[i];
	}
	return NULL;
}

void Skeleton::Update() {

	if(currentAnimation != NULL) {
		currentAnimation->Update();
	}
}

void Skeleton::loadSkeleton(string fileName) {
	OSFILE *inFile = OSBasics::open(fileName.c_str(), "rb");
	if(!inFile) {
		return;
	}
	
	unsigned int numBones;
	float t[3],rq[4],s[3];
	
	OSBasics::read(&numBones, sizeof(unsigned int), 1, inFile);
	unsigned int namelen;
	char buffer[1024];
	
	Matrix4 mat;
	unsigned int hasParent, boneID;
	for(int i=0; i < numBones; i++) {
		
		OSBasics::read(&namelen, sizeof(unsigned int), 1, inFile);
		memset(buffer, 0, 1024);
		OSBasics::read(buffer, 1, namelen, inFile);
		
		Bone *newBone = new Bone(string(buffer));
		
		OSBasics::read(&hasParent, sizeof(unsigned int), 1, inFile);
		if(hasParent == 1) {
			OSBasics::read(&boneID, sizeof(unsigned int), 1, inFile);
			newBone->parentBoneId = boneID;
		} else {
			newBone->parentBoneId = -1;
		}

		OSBasics::read(t, sizeof(float), 3, inFile);
		OSBasics::read(s, sizeof(float), 3, inFile);
		OSBasics::read(rq, sizeof(float), 4, inFile);
		
		bones.push_back(newBone);
		
		newBone->setPosition(t[0], t[1], t[2]);
		newBone->setRotationQuat(rq[0], rq[1], rq[2], rq[3]);
		newBone->setScale(s[0], s[1], s[2]);
		newBone->rebuildTransformMatrix();
		newBone->setRestMatrix(newBone->getTransformMatrix());
	}

	Bone *parentBone;
//	SceneEntity *bProxy;
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->parentBoneId != -1) {
			parentBone = bones[bones[i]->parentBoneId];
			parentBone->addChildBone(bones[i]);
			bones[i]->setParentBone(parentBone);
			parentBone->addEntity(bones[i]);
			
		} else {
//			bProxy = new SceneEntity();
//			addEntity(bProxy);			
//			bProxy->addEntity(bones[i]);
			addEntity(bones[i]);
		}
		bones[i]->visible = false;			
	}
	
	unsigned int numAnimations, activeBones,boneIndex,numPoints,numCurves, curveType;
	OSBasics::read(&numAnimations, sizeof(unsigned int), 1, inFile);
	//Logger::log("numAnimations: %d\n", numAnimations);
	for(int i=0; i < numAnimations; i++) {
		OSBasics::read(&namelen, sizeof(unsigned int), 1, inFile);
		memset(buffer, 0, 1024);
		OSBasics::read(buffer, 1, namelen, inFile);
		SkeletonAnimation *newAnimation = new SkeletonAnimation(buffer, 3.0f);
		OSBasics::read(&activeBones, sizeof(unsigned int), 1, inFile);

	//	Logger::log("activeBones: %d\n", activeBones);		
		for(int j=0; j < activeBones; j++) {
			OSBasics::read(&boneIndex, sizeof(unsigned int), 1, inFile);
			BoneTrack *newTrack = new BoneTrack(bones[boneIndex]);
			
			BezierCurve *curve;
			float vec1[2],vec2[2],vec3[2];

			OSBasics::read(&numCurves, sizeof(unsigned int), 1, inFile);
			//Logger::log("numCurves: %d\n", numCurves);					
			for(int l=0; l < numCurves; l++) {
				curve = new BezierCurve();
				OSBasics::read(&curveType, sizeof(unsigned int), 1, inFile);
				OSBasics::read(&numPoints, sizeof(unsigned int), 1, inFile);
			//	Logger::log("numPoints: %d\n", numPoints);									
				for(int k=0; k < numPoints; k++) {
					OSBasics::read(vec1, sizeof(float), 2, inFile);
					OSBasics::read(vec2, sizeof(float), 2, inFile);
					OSBasics::read(vec3, sizeof(float), 2, inFile);								
					curve->addControlPoint(vec1[0], vec1[1], 0, vec2[0], vec2[1], 0, vec3[0], vec3[1], 0);
				}
				switch(curveType) {
					case 0:
						newTrack->scaleX = curve;
					break;
					case 1:
						newTrack->scaleY = curve;
					break;
					case 2:
						newTrack->scaleZ = curve;					
					break;
					case 3:
						newTrack->QuatW = curve;					
					break;
					case 4:
						newTrack->QuatX = curve;					
					break;
					case 5:
						newTrack->QuatY = curve;					
					break;
					case 6:
						newTrack->QuatZ = curve;					
					break;
					case 7:
						newTrack->LocX = curve;					
					break;
					case 8:
						newTrack->LocY = curve;					
					break;
					case 9:
						newTrack->LocZ = curve;					
					break;
				}
			}
			
			newAnimation->addBoneTrack(newTrack);
		}
		animations.push_back(newAnimation);
	}
	
	OSBasics::close(inFile);
}

void Skeleton::bonesVisible(bool val) {
	for(int i=0; i < bones.size(); i++) {
		bones[i]->visible = val;		
	}
}

BoneTrack::BoneTrack(Bone *bone) {
	targetBone = bone;
	scaleX = NULL;
	scaleY = NULL;
	scaleZ = NULL;
	QuatW = NULL;
	QuatX = NULL;
	QuatY = NULL;
	QuatZ = NULL;
	LocX = NULL;			
	LocY = NULL;
	LocZ = NULL;
	initialized = false;
}

BoneTrack::~BoneTrack() {
}


void BoneTrack::Stop() {
	if(initialized) {
		for(int i=0; i < pathTweens.size(); i++) {
			pathTweens[i]->Pause(true);
		}	
		quatTween->Pause(true);		
	}
}

void BoneTrack::Play() {

	if(!initialized ) {
	// TODO: change it so that you can set the tweens to not manually restart so you can calculate the
	// time per tween
	
	float durTime = (LocX->getControlPoint(LocX->getNumControlPoints()-1)->p2.x)/25.0f;

	BezierPathTween *testTween = new BezierPathTween(&LocXVec, LocX, Tween::EASE_NONE, durTime, true);
	pathTweens.push_back(testTween);
	testTween = new BezierPathTween(&LocYVec, LocY, Tween::EASE_NONE, durTime, true);
	pathTweens.push_back(testTween);
	testTween = new BezierPathTween(&LocZVec, LocZ, Tween::EASE_NONE, durTime, true);
	pathTweens.push_back(testTween);

	if(QuatW)
		quatTween = new QuaternionTween(&boneQuat, QuatW, QuatX, QuatY, QuatZ, Tween::EASE_NONE, durTime, true);

	initialized = true;
	} else {
		for(int i=0; i < pathTweens.size(); i++) {
			pathTweens[i]->Pause(false);
		}	
		quatTween->Pause(false);
	}
/*
	if(QuatW) {
		testTween = new BezierPathTween(&QuatWVec, QuatW, Tween::EASE_NONE, durTime, true);
		pathTweens.push_back(testTween);
	}
	
	if(QuatX) {
		testTween = new BezierPathTween(&QuatXVec, QuatX, Tween::EASE_NONE, durTime, true);
		pathTweens.push_back(testTween);
	}
	
	if(QuatY) {
		testTween = new BezierPathTween(&QuatYVec, QuatY, Tween::EASE_NONE, durTime, true);
		pathTweens.push_back(testTween);
	}
	
	if(QuatZ) {
		testTween = new BezierPathTween(&QuatZVec, QuatZ, Tween::EASE_NONE, durTime, true);
		pathTweens.push_back(testTween);
	}
*/
}


void BoneTrack::Update() {

	//TODO: IMPLEMENT setTransform
	//newMatrix.setTransform(Vector3(LocXVec.y, LocYVec.y, LocZVec.y), Vector3(1.0f, 1.0f, 1.0f), Quaternion (QuatWVec.y, QuatXVec.y, QuatYVec.y, QuatZVec.y));

//	Quaternion quat(QuatWVec.y, QuatXVec.y, QuatYVec.y, QuatZVec.y);
//	Quaternion quat; quat.createFromAxisAngle(1,0,0,30);
	
	Matrix4 newMatrix;
	newMatrix = boneQuat.createMatrix();
	
	Matrix4 scaleMatrix;
	scaleMatrix.m[0][0] *= 1;
	scaleMatrix.m[1][1] *= 1;
	scaleMatrix.m[2][2] *= 1;

	Matrix4 posMatrix;
	posMatrix.m[3][0] = LocXVec.y;
	posMatrix.m[3][1] = LocYVec.y;
	posMatrix.m[3][2] = LocZVec.y;
	
	newMatrix = scaleMatrix*newMatrix*posMatrix;
	
	targetBone->setBoneMatrix(newMatrix);
	targetBone->setMatrix(newMatrix * targetBone->getRestMatrix());
}

void BoneTrack::setSpeed(float speed) {
	for(int i=0; i < pathTweens.size(); i++) {
		pathTweens[i]->setSpeed(speed);
	}	
	quatTween->setSpeed(speed);
}


SkeletonAnimation::SkeletonAnimation(string name, float duration) {
	this->name = name;
	this->duration = duration;
}

void SkeletonAnimation::setSpeed(float speed) {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->setSpeed(speed);
	}	
}

void SkeletonAnimation::Update() {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Update();
	}
}

void SkeletonAnimation::Stop() {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Stop();
	}
}

void SkeletonAnimation::Play() {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Play();
	}
}

SkeletonAnimation::~SkeletonAnimation() {

}

string SkeletonAnimation::getName() {
	return name;
}

void SkeletonAnimation::addBoneTrack(BoneTrack *boneTrack) {
	boneTracks.push_back(boneTrack);
}
