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

#include "PolyBone.h"
#include "PolyCoreServices.h"
#include "PolyLabel.h"
#include "PolyMesh.h"
#include "PolyRenderer.h"
#include "PolySceneLabel.h"

using namespace Polycode;

Bone::Bone(const String& boneName) : Entity() {
	this->boneName = boneName;
	parentBone = NULL;
	boneMatrix.identity();
    disableAnimation = false;
}

Bone::~Bone() {

}

void Bone::setParentBone(Bone *bone) {
	parentBone = bone;
}

void Bone::addChildBone(Bone *bone) {
	childBones.push_back(bone);
}

Bone* Bone::getParentBone() {
	return parentBone;
}

int Bone::getNumChildBones() {
	return childBones.size();
}

Bone *Bone::getChildBone(unsigned int index) {
	if(index > childBones.size()-1)
		index = childBones.size()-1;
		
	return childBones[index];
}

Matrix4 Bone::getBoneMatrix() const {
	if(parentBone)
		return boneMatrix * parentBone->getBoneMatrix();
	else {
		return boneMatrix;
	}
}

void Bone::intializeBone(const Vector3 &basePosition, const Vector3 &baseScale, const Quaternion &baseRotation, const Vector3 &restPosition, const Vector3 &restScale, const Quaternion &restRotation) {
    
    this->baseRotation = baseRotation;
    this->baseScale = baseScale;
    this->basePosition = basePosition;
    
    setPosition(basePosition);
    setRotationByQuaternion(baseRotation);
    setScale(baseScale);
    rebuildTransformMatrix();
    
    setBaseMatrix(getTransformMatrix());
    setBoneMatrix(getTransformMatrix());
    
    Matrix4 restRotationMatrix = restRotation.createMatrix();

    Matrix4 restPositionMatrix;
    restPositionMatrix.identity();
    restPositionMatrix.setPosition(restPosition.x, restPosition.y, restPosition.z);

    Matrix4 restScaleMatrix;
    restScaleMatrix.identity();
    restScaleMatrix.setScale(restScale);
    
    
    setRestMatrix(restScaleMatrix*restRotationMatrix*restPositionMatrix);
}

Matrix4 Bone::getFinalMatrix() const {
    return finalMatrix;
}

Matrix4 Bone::buildFinalMatrix() const {
    if(parentBone) {
        return boneMatrix * parentBone->buildFinalMatrix();
    } else {
        return boneMatrix;
    }
}

void Bone::rebuildFinalMatrix() {
    finalMatrix = restMatrix * buildFinalMatrix();
}

void Bone::setBoneMatrix(const Matrix4& matrix) {
	boneMatrix = matrix;
}

void Bone::setBaseMatrix(const Matrix4& matrix) {
	baseMatrix = matrix;
}

Matrix4 Bone::getRestMatrix() const {
	return restMatrix;
}

Matrix4 Bone::getParentRestMatrix() const {
	if(parentBone)
		return parentBone->getFullRestMatrix();
	else {
		Matrix4 ident;
		ident.identity();
		return ident;
	}
}

Matrix4 Bone::getFullBaseMatrix() const {
	if(parentBone)
		return baseMatrix * parentBone->getFullBaseMatrix();
	else {
		return baseMatrix;
	}
	
}

Matrix4 Bone::getFullRestMatrix() const {
	if(parentBone)
		return restMatrix * parentBone->getFullRestMatrix();
	else {
		return restMatrix;
	}
}

void Bone::setRestMatrix(const Matrix4& matrix) {
	restMatrix = matrix;
}

String Bone::getName() const {
	return boneName;
}
