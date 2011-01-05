/*
 *  PolyEntity.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 1/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyEntity.h"

using namespace Polycode;

Entity::Entity() {
	scale.set(1,1,1);
	pitch = 0;
	yaw = 0;
	roll = 0;
	renderer = NULL;
	enabled = true;
	visible = true;
	bBoxRadius = 0;
	color.setColor(1.0f,1.0f,1.0f,1.0f);
	parentEntity = NULL;
	matrixDirty = true;
	matrixAdj = 1.0f;
	billboardMode = false;
	billboardRoll = false;
	backfaceCulled = true;
	depthOnly = false;
	depthWrite = true;
	alphaTest = false;
	blendingMode = Renderer::BLEND_MODE_NORMAL;	
	lockMatrix = false;
	renderWireframe  = false;
	colorAffectsChildren = true;
	maskEntity = NULL;
	isMask = false;
	hasMask = false;
}

Entity *Entity::getParentEntity() {
	return parentEntity;
}

Color Entity::getCombinedColor() {
	if(parentEntity) {
		if(parentEntity->colorAffectsChildren)
			return color * parentEntity->getCombinedColor();
		else
			return color;			
	} else {
		return color;
	}
}

Matrix4 Entity::getLookAtMatrix(const Vector3 &loc, const Vector3 &upVector) {
	rebuildTransformMatrix();
	Vector3 D;
	if(parentEntity)
		D = loc - (parentEntity->getConcatenatedMatrix() *position);		
	else
		D = loc - position;
	
	Vector3 back = D * -1;
	back.Normalize();
	
	Vector3 right = back.crossProduct(upVector) ;
	right.Normalize();
	right = right * -1;
	
	Vector3 up = back.crossProduct(right);
	
	Matrix4 newMatrix(right.x, right.y, right.z, 0, 
					  up.x, up.y, up.z, 0, 
					  back.x, back.y, back.z, 0,
					  0, 0 , 0, 1);		
	return newMatrix;
}

void Entity::lookAt(const Vector3 &loc, const Vector3 &upVector) {	
	Matrix4 newMatrix = getLookAtMatrix(loc, upVector);
	rotationQuat.createFromMatrix(newMatrix);
	matrixDirty = true;
}

void Entity::lookAtEntity(Entity *entity,  const Vector3 &upVector) {
	if(entity->getParentEntity())
		lookAt(entity->getParentEntity()->getConcatenatedMatrix() * (*entity->getPosition()), upVector);		
	else
		lookAt(*entity->getPosition(), upVector);
}

void Entity::removeChild(Entity *entityToRemove) {
	for(int i=0;i<children.size();i++) {
		if(children[i] == entityToRemove) {
			children.erase(children.begin()+i);
		}
	}	
}

void Entity::addChild(Entity *newChild) {
	addEntity(newChild);
}

void Entity::setColor(Color color) {
	this->color.setColor(&color);
}

void Entity::setColorInt(int r, int g, int b, int a) {
	color.setColorRGBA(r,g, b, a);
}

void Entity::setColor(float r, float g, float b, float a) {
	color.setColor(r,g,b,a);
}

void Entity::recalculateBBox() {
	
}

void Entity::setBlendingMode(int newBlendingMode) {
	blendingMode = newBlendingMode;
}

float Entity::getBBoxRadius() {
	float compRad;
	float biggest = bBoxRadius;
	for(int i=0;i<children.size();i++) {
		compRad = children[i]->getCompoundBBoxRadius();
		if(compRad > biggest)
			biggest = compRad;
	}	
	return biggest;
}

float Entity::getCompoundBBoxRadius() {
	float compRad;
	float biggest = bBoxRadius + position.distance(Vector3(0,0,0));
	for(int i=0;i<children.size();i++) {
		compRad = children[i]->getCompoundBBoxRadius();
		if(compRad > biggest)
			biggest = compRad;
	}	
	return biggest;
}

void Entity::setBBoxRadius(float rad) {
	bBoxRadius = rad;
}

Entity::~Entity() {
}

Vector3 Entity::getChildCenter() {
	return childCenter;
}

void Entity::setMatrix(Matrix4 matrix) {
	transformMatrix = matrix;
	matrixDirty = false;
}

Matrix4 Entity::buildPositionMatrix() {
	Matrix4 posMatrix;
	posMatrix.m[3][0] = position.x*matrixAdj;
	posMatrix.m[3][1] = position.y*matrixAdj;
	posMatrix.m[3][2] = position.z*matrixAdj;
	return posMatrix;
}

void Entity::rebuildTransformMatrix() {
	if(lockMatrix)
		return;
	
	if(billboardMode){ 
		transformMatrix.identity();
	} else {
		transformMatrix = rotationQuat.createMatrix();
	}
	
	Matrix4 scaleMatrix;
	scaleMatrix.m[0][0] *= scale.x;
	scaleMatrix.m[1][1] *= scale.y;
	scaleMatrix.m[2][2] *= scale.z;
	
	Matrix4 posMatrix = buildPositionMatrix();

	transformMatrix = scaleMatrix*transformMatrix*posMatrix;
	matrixDirty = false;
}

void Entity::doUpdates() {
	Update();
	for(int i=0; i < children.size(); i++) {
		children[i]->doUpdates();
	}	
}

void Entity::updateEntityMatrix() {	
	if(matrixDirty)
		rebuildTransformMatrix();
	
	for(int i=0; i < children.size(); i++) {
		children[i]->updateEntityMatrix();
	}
}

Vector3 Entity::getCompoundScale() {
	if(parentEntity != NULL) {
		Vector3 parentScale = parentEntity->getCompoundScale();
		return Vector3(scale.x * parentScale.x, scale.y * parentScale.y,scale.z * parentScale.z);
		
	}
	else
		return scale;	
}


Matrix4 Entity::getConcatenatedRollMatrix() {
	Quaternion q;
	q.createFromAxisAngle(0.0f, 0.0f, 1.0f, roll*matrixAdj);
	Matrix4 transformMatrix = q.createMatrix();	
	
	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedRollMatrix();
	else
		return transformMatrix;	
}

void Entity::setMask(Entity *mask) {	
	mask->setDepthWrite(true);
	mask->depthOnly = true;
	mask->setPositionZ(0.999);
	mask->isMask = true;
	mask->enabled = false;
	maskEntity = mask;
	hasMask = true;
}

void Entity::clearMask() {
	maskEntity->setDepthWrite(false);
	maskEntity->depthOnly = false;	
	maskEntity->setPositionZ(0);	
	maskEntity->enabled = true;
	maskEntity = NULL;	
	hasMask = false;	
}

void Entity::setDepthWrite(bool val) {
	depthWrite = val;
	for(int i=0;i<children.size();i++) {
		children[i]->setDepthWrite(val);
	}	
}

void Entity::transformAndRender() {
	if(!renderer || !enabled)
		return;

	if(depthOnly) {
		renderer->drawToColorBuffer(false);
	}
	
	if(hasMask) {
		renderer->clearBuffer(false, true);
		maskEntity->enabled = true;
		maskEntity->transformAndRender();		
		maskEntity->enabled = false;		
		renderer->setDepthFunction(Renderer::DEPTH_FUNCTION_GREATER);
	}
	
	renderer->pushMatrix();	
	renderer->multModelviewMatrix(transformMatrix);
	renderer->setVertexColor(color.r,color.g,color.b,color.a);
	if(billboardMode) {
		renderer->billboardMatrixWithScale(getCompoundScale());
		if(billboardRoll) {
			renderer->multModelviewMatrix(getConcatenatedRollMatrix());
		}
	}
		
	if(!depthWrite)
		renderer->enableDepthTest(false);
	else
		renderer->enableDepthTest(true);
		
	renderer->enableAlphaTest(alphaTest);
	
	Color combined = getCombinedColor();
	renderer->setVertexColor(combined.r,combined.g,combined.b,combined.a);
	
	renderer->setBlendingMode(blendingMode);
	renderer->enableBackfaceCulling(backfaceCulled);
	
	int mode = renderer->getRenderMode();
	if(renderWireframe)
		renderer->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);
		
	if(visible) {
		Render();
		renderer->setRenderMode(mode);
	
	
//	renderer->pushMatrix();
	adjustMatrixForChildren();
	renderChildren();	
//	renderer->popMatrix();	
	
	}		
	
	renderer->popMatrix();
	
	if(hasMask) {
		renderer->clearBuffer(false, true);
	}
	
	if(!depthWrite)
		renderer->enableDepthTest(true);
	
	
	if(hasMask) {
		renderer->setDepthFunction(Renderer::DEPTH_FUNCTION_LEQUAL);
	}
	
	if(depthOnly) {
		renderer->drawToColorBuffer(true);
	}	
}

void Entity::setRenderer(Renderer *renderer) {
	this->renderer = renderer;
	for(int i=0;i<children.size();i++) {
		children[i]->setRenderer(renderer);
	}
}

void Entity::addEntity(Entity *newChild) {
	newChild->setRenderer(renderer);
	newChild->setParentEntity(this);
	children.push_back(newChild);
}


void Entity::renderChildren() {
	for(int i=0;i<children.size();i++) {
		children[i]->transformAndRender();
	}
}

void Entity::dirtyMatrix(bool val) {
	matrixDirty = val;
}

void Entity::setRotationQuat(float w, float x, float y, float z) {
	rotationQuat.w = w;
	rotationQuat.x = x;
	rotationQuat.y = y;
	rotationQuat.z = z;
	matrixDirty = true;
}

Quaternion Entity::getRotationQuat() {
	return rotationQuat;
}

void Entity::setPitch(float pitch) {
	this->pitch = pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::setYaw(float yaw) {
	this->yaw = yaw;
	rebuildRotation();	
	matrixDirty = true;
}

Vector3 Entity::getScale() {
	return scale;
}

Matrix4 Entity::getConcatenatedMatrix() {
	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedMatrix();
	else
		return transformMatrix;
}

Matrix4 Entity::getTransformMatrix() {
	return transformMatrix;
}

void Entity::Pitch(float pitch) {
	this->pitch += pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Yaw(float yaw) {
	this->yaw += yaw;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Roll(float roll) {
	this->roll += roll;
	rebuildRotation();
	matrixDirty = true;
}

void Entity::setRoll(float roll) {
	this->roll= roll;
	rebuildRotation();
	matrixDirty = true;
}

void Entity::rebuildRotation() {
	rotationQuat.fromAxes(pitch, yaw, roll);
}

String Entity::getEntityProp(String propName) {
	for(int i=0; i < entityProps.size(); i++) {
		if(entityProps[i].propName == propName) {
			return entityProps[i].propValue;
		}
	}
	return "null";
}

Vector3 Entity::getCombinedPosition() {
	if(parentEntity != NULL)
		return (parentEntity->getCombinedPosition())+position;
	else
		return position;
}

void Entity::setParentEntity(Entity *entity) {
	parentEntity = entity;
}

float Entity::getPitch() {
	return pitch;
}

float Entity::getYaw() {
	return yaw;
}

float Entity::getRoll() {
	return roll;
}

void Entity::setTransformByMatrixPure(Matrix4 matrix) {
	transformMatrix = matrix;
}

void Entity::setTransformByMatrix(Matrix4 matrix) {
	setPosition(matrix.getPosition());	
	float x,y,z;
	matrix.getEulerAngles(&x,&y,&z);

	setPitch(x);
	setYaw(y);
	setRoll(z);
	
//	setYaw(-asin(matrix.m[0][2]) * TODEGREES);	
///	setPitch(atan2(-matrix.m[0][1], matrix.m[0][0]) * TODEGREES);
//	setRoll(atan2(-matrix.m[1][2], matrix.m[2][2]) * TODEGREES);
	matrixDirty = true;
}

void Entity::setPosition(Vector3 posVec) {
	position = posVec;
	matrixDirty = true;
}

void Entity::setPositionX(float x) {
	position.x = x;
	matrixDirty = true;
}

void Entity::setPositionY(float y) {
	position.y = y;
	matrixDirty = true;	
}

void Entity::setPositionZ(float z) {
	position.z = z;
	matrixDirty = true;	
}


void Entity::setScaleX(float x) {
	scale.x = x;
	matrixDirty = true;	
}

void Entity::setScaleY(float y) {
	scale.y = y;
	matrixDirty = true;		
}

void Entity::setScaleZ(float z) {
	scale.z = z;
	matrixDirty = true;		
}


void Entity::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	matrixDirty = true;
}

void Entity::Translate(Vector3 tVec) {
	position += tVec;
	matrixDirty = true;
}

void Entity::Translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
	matrixDirty = true;
}

void Entity::Scale(float x, float y, float z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;	
	matrixDirty = true;
}

void Entity::setScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
	matrixDirty = true;
}

Vector3 *Entity::getPosition() {
	return &position;
}

float Entity::getCombinedPitch() {
	if(parentEntity != NULL)
		return parentEntity->getCombinedPitch()+pitch;
	else
		return pitch;
}

float Entity::getCombinedYaw() {
	if(parentEntity != NULL)
		return parentEntity->getCombinedYaw()+yaw;
	else
		return yaw;
}

float Entity::getCombinedRoll() {
	if(parentEntity != NULL)
		return parentEntity->getCombinedRoll()+roll;
	else
		return roll;
	
}