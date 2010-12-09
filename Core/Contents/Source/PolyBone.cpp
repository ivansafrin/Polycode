/*
 *  PolyBone.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyBone.h"

using namespace Polycode;

Bone::Bone(String boneName) : SceneEntity() {
	this->boneName = boneName;

	boneMesh = new Mesh(Mesh::QUAD_MESH);
	boneMesh->createBox(0.1,0.1,0.1);
	bBoxRadius = boneMesh->getRadius();
	bBox = boneMesh->calculateBBox();
//	color.setColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->setDepthWrite(false);
	parentBone = NULL;
	boneMatrix.init();
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

Matrix4 Bone::getBoneMatrix() {
	if(parentBone)
		return boneMatrix * parentBone->getBoneMatrix();
	else {
		return boneMatrix;
	}
}

Matrix4 Bone::getFinalMatrix() {
	Matrix4 final = boneMatrix * restMatrix;

	if(parentBone) {
		final = final * parentBone->getFinalMatrix();
	} 
	
	return final;
}

void Bone::setBoneMatrix(Matrix4 matrix) {
	boneMatrix = matrix;
}

Matrix4 Bone::getRestMatrix() {
	return restMatrix;
}

Matrix4 Bone::getParentRestMatrix() {
	if(parentBone)
		return parentBone->getFullRestMatrix();
	else {
		Matrix4 ident;
		ident.identity();
		return ident;
	}
}

Matrix4 Bone::getFullRestMatrix() {
	if(parentBone)
		return restMatrix * parentBone->getFullRestMatrix();
	else {
		return restMatrix;
	}
}

void Bone::setRestMatrix(Matrix4 matrix) {
	restMatrix = matrix;
}

String Bone::getName() {
	return boneName;
}

void Bone::enableBoneLabel(Font *font, float size, float scale) {
//	SceneLabel *label = new SceneLabel("", boneName, size, scale, Label::ANTIALIAS_FULL);
	SceneLabel *label = new SceneLabel("", L"FIX ME", size, scale, Label::ANTIALIAS_FULL);	
	label->billboardMode = true;
	label->setDepthWrite(false);
	addEntity(label);
}

void Bone::Render() {
	CoreServices::getInstance()->getRenderer()->setTexture(NULL);	
//	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::COLOR_DATA_ARRAY);
//	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::VERTEX_DATA_ARRAY);
//	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
//	renderer->pushDataArrayForMesh(boneMesh, RenderDataArray::NORMAL_DATA_ARRAY);		
//	renderer->drawArrays(boneMesh->getMeshType());	
}
