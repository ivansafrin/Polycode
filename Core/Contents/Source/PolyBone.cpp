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

Bone::Bone(const String& boneName) : SceneEntity() {
	this->boneName = boneName;
//	boneMesh = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	this->depthTest = false;
	parentBone = NULL;
	boneMatrix.identity();
//	addChild(boneMesh);

	boneMesh = new Mesh(Mesh::QUAD_MESH);
	boneMesh->createBox(0.2,0.2,0.2);

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

Matrix4 Bone::getFinalMatrix() const {
	Matrix4 final = boneMatrix;

	if(parentBone) {
		final = final * parentBone->getFinalMatrix();
	} 

	return final;
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

const String& Bone::getName() const {
	return boneName;
}

void Bone::enableBoneLabel(const String& fontLabel, Number size, Number scale, Color labelColor) {
	SceneLabel *label = new SceneLabel(fontLabel, boneName, size, scale, Label::ANTIALIAS_FULL);
	label->setColor(labelColor);
	label->billboardMode = true;
	label->depthTest = false;
	addEntity(label);
}

void Bone::Render() {

	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
//	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::COLOR_DATA_ARRAY);
	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::TEXCOORD_DATA_ARRAY);
	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::NORMAL_DATA_ARRAY);
	renderer->drawArrays(boneMesh->getMeshType());

}
