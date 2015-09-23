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
    bonesEntity	= new Entity();
    bonesEntity->visible = false;
    addChild(bonesEntity);        
	loadSkeleton(fileName);
}

Skeleton::Skeleton() {
    baseAnimation = NULL;
    bonesEntity	= new Entity();
    bonesEntity->visible = false;
    addChild(bonesEntity);
}

Skeleton::~Skeleton() {
    for(int i=0; i < animations.size(); i++) {
        delete animations[i];
    }
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

Bone *Skeleton::getBone(unsigned int index) const {
    if(index >= bones.size()) {
        return NULL;
    }
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
        if(!bones[i]->disableAnimation) {
            bones[i]->setRotationByQuaternion(bones[i]->baseRotation);
            bones[i]->setPosition(bones[i]->basePosition);
            bones[i]->setScale(bones[i]->baseScale);
        }
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
    
    for(int i=0; i < bones.size(); i++) {
        bones[i]->rebuildFinalMatrix();
    }
}

void Skeleton::addBone(Bone *bone) {
    bones.push_back(bone);
}

void Skeleton::removeBone(Bone *bone) {
    for(int i=0; i < bones.size(); i++) {
        if(bones[i] == bone) {
            bones.erase(bones.begin()+i);
            return;
        }
    }
}

unsigned int Skeleton::getBoneIndexByBone(Bone *bone) {
    for(int i=0; i < bones.size(); i++) {
        if(bones[i] == bone) {
            return i;
        }
    }
    return 0;
}

void Skeleton::loadSkeleton(const String& fileName) {
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
    paused = false;
    time = 0.0;
    speed = 1.0;
    playOnce = false;
    
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
    
    quatCurve = NULL;
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
    delete quatCurve;
}

void BoneTrack::Reset() {
    time = 0.0;
}

void BoneTrack::Stop() {
    paused = true;
}


void BoneTrack::Play(bool once) {
    paused = true;
    playOnce = once;
}


void BoneTrack::Update(Number elapsed) {
	if(!targetBone)
		return;
    
//    if(!paused) {
        time += elapsed * speed;
//    }
    
    if(time > length) {
        if(playOnce) {
            time = length;
            return;
        } else {
            time = time - length;
        }
    }
    
    if(LocX) {
        position.x = LocX->getYValueAtX(time);
    }
    if(LocY) {
        position.y = LocY->getYValueAtX(time);
    }
    if(LocZ) {
        position.z = LocZ->getYValueAtX(time);
    }
    
    if(scaleX) {
        scale.x = scaleX->getYValueAtX(time);
    }
    if(scaleY) {
        scale.y = scaleY->getYValueAtX(time);
    }
    if(scaleZ) {
        scale.z = scaleZ->getYValueAtX(time);
    }
    
    if(!quatCurve) {
        if(QuatW) {
            quatCurve = new QuaternionCurve(QuatW, QuatX, QuatY, QuatZ);
        }
    }
    
    if(quatCurve) {
        boneQuat = quatCurve->interpolate(time/length, true);
    }

    if(targetBone->disableAnimation) {
        return;
    }
    
    Quaternion rotationQuat = targetBone->getRotationQuat();
    rotationQuat = Quaternion::Slerp(weight, rotationQuat, boneQuat, true);
    targetBone->setRotationByQuaternion(rotationQuat);

    targetBone->setPosition((position * weight) + (targetBone->getPosition() * (1.0 - weight)));
    
    targetBone->setScale((scale * weight) + (targetBone->getScale() * (1.0 - weight)));
    
}

void BoneTrack::setSpeed(Number speed) {
    this->speed = speed;
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
    Number elapsed = CoreServices::getInstance()->getCore()->getElapsed();
	for(int i=0; i < boneTracks.size(); i++) {
        boneTracks[i]->weight = weight;
		boneTracks[i]->Update(elapsed);
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
