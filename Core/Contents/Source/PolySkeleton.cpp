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

#include "PolySkeleton.h"
#include "PolyBezierCurve.h"
#include "PolyBone.h"
#include "PolyLabel.h"
#include "PolySceneLabel.h"
#include "PolySceneLine.h"
#include "PolyTween.h"
#include "PolyTweenManager.h"
#include "OSBasics.h"

using namespace Polycode;

Skeleton *Skeleton::BlankSkeleton() {
	return new Skeleton();
}

Skeleton::Skeleton(const String& fileName) : Entity() {
    baseAnimation = NULL;
	loadSkeleton(fileName);
}

Skeleton::Skeleton() {
}

Skeleton::~Skeleton() {
}

int Skeleton::getNumBones() const {
	return bones.size();
}

Bone *Skeleton::getBoneByName(const String& name) const {
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->getName() == name)
			return bones[i];
	}
	return NULL;
}

Bone *Skeleton::getBone(int index) const {
	return bones[index];
}

void Skeleton::setBaseAnimationByName(const String &animName) {
	SkeletonAnimation *anim = getAnimation(animName);
	if(anim) {
        setBaseAnimation(anim);
    }
}

void Skeleton::setBaseAnimation(SkeletonAnimation *animation){
    baseAnimation = animation;
    baseAnimation->setWeight(1.0);
    animation->Play(false);
}


void Skeleton::playAnimationByName(const String& animName, Number weight, bool once, bool restartIfPlaying) {
	SkeletonAnimation *anim = getAnimation(animName);
	if(anim) {
        playAnimation(anim, weight, once, restartIfPlaying);
    }
}

void Skeleton::playAnimation(SkeletonAnimation *animation, Number weight, bool once, bool restartIfPlaying) {
    
    if(weight > 1.0) {
        weight = 1.0;
    }
    if(weight < 0.0) {
        weight = 0.0;
    }
    
    animation->setWeight(weight);
    
    if(animation->isPlaying()) {
        if(restartIfPlaying) {
            animation->Reset();
        }
        return;
    }
    
    animation->Reset();
    playingAnimations.push_back(animation);
    animation->Play(once);
}

SkeletonAnimation *Skeleton::getAnimation(const String& name) const {
	for(int i=0; i < animations.size(); i++) {
		if(animations[i]->getName() == name)
			return animations[i];
	}
	return NULL;
}

void Skeleton::Update() {
    
    for(int i=0; i < bones.size(); i++) {
        bones[i]->setRotationByQuaternion(bones[i]->baseRotation);
        bones[i]->setPosition(bones[i]->basePosition);
        bones[i]->setScale(bones[i]->baseScale);
    }
    
    if(baseAnimation) {
        baseAnimation->Update();
    }
    
    for(int i=0; i < playingAnimations.size(); i++) {
        playingAnimations[i]->Update();
    }
    
    for(int i=0; i < bones.size(); i++) {
        bones[i]->rebuildTransformMatrix();
        bones[i]->setBoneMatrix(bones[i]->getTransformMatrix());
    }
}

void Skeleton::loadSkeleton(const String& fileName) {
	OSFILE *inFile = OSBasics::open(fileName.c_str(), "rb");
	if(!inFile) {
		return;
	}
	
	bonesEntity	= new Entity();
	bonesEntity->visible = false;
	addChild(bonesEntity);
	
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
		
		Bone *newBone = new Bone(String(buffer));
		
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
		
		Quaternion bq;
		bq.set(rq[0], rq[1], rq[2], rq[3]);
        
        newBone->baseRotation = bq;
        newBone->baseScale = Vector3(s[0], s[1], s[2]);
        newBone->basePosition = Vector3(t[0], t[1], t[2]);
        
		newBone->setPosition(t[0], t[1], t[2]);
		newBone->setRotationQuat(rq[0], rq[1], rq[2], rq[3]);
		newBone->setScale(s[0], s[1], s[2]);
		newBone->rebuildTransformMatrix();
		
		newBone->setBaseMatrix(newBone->getTransformMatrix());
		newBone->setBoneMatrix(newBone->getTransformMatrix());

		OSBasics::read(t, sizeof(float), 3, inFile);
		OSBasics::read(s, sizeof(float), 3, inFile);
		OSBasics::read(rq, sizeof(float), 4, inFile);
		
		Quaternion q;
		q.set(rq[0], rq[1], rq[2], rq[3]);
		Matrix4 m = q.createMatrix();
		m.setPosition(t[0], t[1], t[2]);
		
		newBone->setRestMatrix(m);
		
	}

	Bone *parentBone;
	
	for(int i=0; i < bones.size(); i++) {
		if(bones[i]->parentBoneId != -1) {
			parentBone = bones[bones[i]->parentBoneId];
			parentBone->addChildBone(bones[i]);
			bones[i]->setParentBone(parentBone);
			parentBone->addChild(bones[i]);
		} else {
			bonesEntity->addChild(bones[i]);
		}
	}
	OSBasics::close(inFile);
}

SkeletonAnimation *Skeleton::getBaseAnimation() {
    return baseAnimation;
}

void Skeleton::stopAllAnimations() {
    for(int i=0; i < playingAnimations.size(); i++) {
        playingAnimations[i]->Stop();
    }
    playingAnimations.clear();
}

void Skeleton::stopAnimationByName(const String &name) {
	SkeletonAnimation *anim = getAnimation(name);
	if(anim) {
        stopAnimation(anim);
    }
}

void Skeleton::stopAnimation(SkeletonAnimation *animation) {
    for(int i=0; i < playingAnimations.size(); i++) {
        if(playingAnimations[i] == animation) {
            playingAnimations[i]->Stop();            
            playingAnimations.erase(playingAnimations.begin()+i);
            return;
        }
    }
}

void Skeleton::addAnimation(const String& name, const String& fileName) {

    OSFILE *inFile = OSBasics::open(fileName.c_str(), "rb");
    
    if(!inFile) {
		return;
	}
	
    unsigned int activeBones,numPoints,numCurves, curveType;
    float length;
    OSBasics::read(&length, 1, sizeof(float), inFile);

    SkeletonAnimation *newAnimation = new SkeletonAnimation(name, length);
    OSBasics::read(&activeBones, sizeof(unsigned int), 1, inFile);
    
    unsigned short boneNameLen;
    char boneNameBuffer[1024];

    for(int j=0; j < activeBones; j++) {
        
        OSBasics::read(&boneNameLen, sizeof(unsigned short), 1, inFile);
        OSBasics::read(boneNameBuffer, 1, boneNameLen, inFile);
        boneNameBuffer[boneNameLen] = '\0';
        
        Bone *trackBone = getBoneByName(boneNameBuffer);
        if(!trackBone) {
            printf("WARNING, INVALID BONE NAME: %s\n", boneNameBuffer);
            continue;
        }
        
        BoneTrack *newTrack = new BoneTrack(trackBone, length);
        
        BezierCurve *curve;
        float vec1[2];
        
        OSBasics::read(&numCurves, sizeof(unsigned int), 1, inFile);
        for(int l=0; l < numCurves; l++) {
            curve = new BezierCurve();
            OSBasics::read(&curveType, sizeof(unsigned int), 1, inFile);
            OSBasics::read(&numPoints, sizeof(unsigned int), 1, inFile);
            
            for(int k=0; k < numPoints; k++) {
                OSBasics::read(vec1, sizeof(float), 2, inFile);					
                curve->addControlPoint2d(vec1[1], vec1[0]);
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
                case 7:;
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
        newTrack->initTweens();
        newAnimation->addBoneTrack(newTrack);
    }
    
    animations.push_back(newAnimation);
	OSBasics::close(inFile);	
}

void Skeleton::bonesVisible(bool val) {
	bonesEntity->visible = val;
}

BoneTrack::BoneTrack(Bone *bone, Number length) {
    weight = 0.0;
	this->length = length;
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
}

BoneTrack::~BoneTrack() {
	delete scaleX;
	delete scaleY;
	delete scaleZ;
	delete QuatW;
	delete QuatX;
	delete QuatY;
	delete QuatZ;
	delete LocX;
	delete LocY;
	delete LocZ;
}

void BoneTrack::Reset() {
    for(int i=0; i < pathTweens.size(); i++) {
        if(pathTweens[i]->isComplete()) {
            CoreServices::getInstance()->getTweenManager()->addTween(pathTweens[i]);
        }
        pathTweens[i]->Reset();
    }
    if(quatTween->isComplete()) {
        CoreServices::getInstance()->getTweenManager()->addTween(quatTween);
    }
    quatTween->Reset();
}

void BoneTrack::Stop() {
    for(int i=0; i < pathTweens.size(); i++) {
        pathTweens[i]->Pause(true);
    }
    quatTween->Pause(true);
}

void BoneTrack::initTweens() {
    
    BezierPathTween *tween;
	if(LocX) {
		tween = new BezierPathTween(&LocXVec, LocX, Tween::EASE_NONE, length, true);
		pathTweens.push_back(tween);
	}
	if(LocY) {
		tween = new BezierPathTween(&LocYVec, LocY, Tween::EASE_NONE, length, true);
		pathTweens.push_back(tween);
	}
    
	if(LocZ) {
		tween = new BezierPathTween(&LocZVec, LocZ, Tween::EASE_NONE, length, true);
		pathTweens.push_back(tween);
	}
	tween = new BezierPathTween(&ScaleXVec, scaleX, Tween::EASE_NONE, length, true);
	pathTweens.push_back(tween);
	tween = new BezierPathTween(&ScaleYVec, scaleY, Tween::EASE_NONE, length, true);
	pathTweens.push_back(tween);
	tween = new BezierPathTween(&ScaleZVec, scaleZ, Tween::EASE_NONE, length, true);
	pathTweens.push_back(tween);
    
	if(QuatW) {
        quatTween = new QuaternionTween(&boneQuat, QuatW, QuatX, QuatY, QuatZ, Tween::EASE_NONE, length, true);
    }
}

void BoneTrack::Play(bool once) {
    for(int i=0; i < pathTweens.size(); i++) {
            pathTweens[i]->Reset();
			pathTweens[i]->Pause(false);
            pathTweens[i]->repeat = !once;
    }
    if(quatTween) {
        quatTween->Reset();
        quatTween->Pause(false);
        quatTween->repeat = !once;
    }
}


void BoneTrack::Update() {
	if(!targetBone)
		return;
    
    if(quatTween->isComplete()) {
        return;
    }
    
    Quaternion rotationQuat = targetBone->getRotationQuat();
    rotationQuat = Quaternion::Slerp(weight, rotationQuat, boneQuat, true);
    targetBone->setRotationByQuaternion(rotationQuat);

    Vector3 trackPosition = Vector3(LocXVec.y, LocYVec.y, LocZVec.y);
    targetBone->setPosition((trackPosition * weight) + (targetBone->getPosition() * (1.0 - weight)));

    Vector3 trackScale = Vector3(ScaleXVec.y, ScaleYVec.y, ScaleZVec.y);
    Vector3 newScale = ((trackScale - Vector3(1.0, 1.0, 1.0)) * weight) + Vector3(1.0, 1.0, 1.0);
}

void BoneTrack::setSpeed(Number speed) {
	for(int i=0; i < pathTweens.size(); i++) {
		pathTweens[i]->setSpeed(speed);
	}	
	quatTween->setSpeed(speed);
}


SkeletonAnimation::SkeletonAnimation(const String& name, Number duration) {
	this->name = name;
	this->duration = duration;
    this->weight = 1.0;
    this->playing = false;
}

bool SkeletonAnimation::isPlaying() const {
    return playing;
}

void SkeletonAnimation::setWeight(Number newWeight) {
    weight = newWeight;
}

Number SkeletonAnimation::getWeight() const {
    return weight;
}


void SkeletonAnimation::setSpeed(Number speed) {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->setSpeed(speed);
	}	
}

void SkeletonAnimation::Update() {
	for(int i=0; i < boneTracks.size(); i++) {
        boneTracks[i]->weight = weight;
		boneTracks[i]->Update();
	}
}

void SkeletonAnimation::Reset() {
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Reset();
	}
}

void SkeletonAnimation::Stop() {
    playing = false;
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Stop();
	}
}

void SkeletonAnimation::Play(bool once) {
    playing = true;
	for(int i=0; i < boneTracks.size(); i++) {
		boneTracks[i]->Play(once);
	}
}

SkeletonAnimation::~SkeletonAnimation() {
    for(int i=0; i < boneTracks.size(); i++) {
        delete boneTracks[i];
    }
}

const String& SkeletonAnimation::getName() const {
	return name;
}

void SkeletonAnimation::addBoneTrack(BoneTrack *boneTrack) {
	boneTracks.push_back(boneTrack);
}
