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
#include "PolyEntity.h"

using namespace Polycode;

Entity::Entity() {
	scale.set(1,1,1);
	pitch = 0;
	yaw = 0;
	roll = 0;
	renderer = NULL;
	enabled = true;
	depthTest = true;
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
	ignoreParentMatrix = false;
	alphaTest = false;
	blendingMode = Renderer::BLEND_MODE_NORMAL;	
	lockMatrix = false;
	renderWireframe  = false;
	colorAffectsChildren = true;
	visibilityAffectsChildren = true;
	maskEntity = NULL;
	isMask = false;
	hasMask = false;
}

Entity *Entity::getParentEntity() const {
	return parentEntity;
}

Color Entity::getCombinedColor() const {
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
		lookAt(entity->getParentEntity()->getConcatenatedMatrix() * (entity->getPosition()), upVector);		
	else
		lookAt(entity->getPosition(), upVector);
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

void Entity::setColor(Number r, Number g, Number b, Number a) {
	color.setColor(r,g,b,a);
}

void Entity::recalculateBBox() {
	
}

void Entity::setBlendingMode(int newBlendingMode) {
	blendingMode = newBlendingMode;
}

Number Entity::getBBoxRadius() const {
	Number compRad;
	Number biggest = bBoxRadius;
	for(int i=0;i<children.size();i++) {
		compRad = children[i]->getCompoundBBoxRadius();
		if(compRad > biggest)
			biggest = compRad;
	}	
	return biggest;
}

Number Entity::getCompoundBBoxRadius() const {
	Number compRad;
	Number biggest = bBoxRadius + position.distance(Vector3(0,0,0));
	for(int i=0;i<children.size();i++) {
		compRad = children[i]->getCompoundBBoxRadius();
		if(compRad > biggest)
			biggest = compRad;
	}	
	return biggest;
}

void Entity::setBBoxRadius(Number rad) {
	bBoxRadius = rad;
}

Entity::~Entity() {
}

Vector3 Entity::getChildCenter() const {
	return childCenter;
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

Vector3 Entity::getCompoundScale() const {
	if(parentEntity != NULL) {
		Vector3 parentScale = parentEntity->getCompoundScale();
		return Vector3(scale.x * parentScale.x, scale.y * parentScale.y,scale.z * parentScale.z);
		
	}
	else
		return scale;	
}


Matrix4 Entity::getConcatenatedRollMatrix() const {
	Quaternion q;
	q.createFromAxisAngle(0.0f, 0.0f, 1.0f, roll*matrixAdj);
	Matrix4 transformMatrix = q.createMatrix();	
	
	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedRollMatrix();
	else
		return transformMatrix;	
}

void Entity::setMask(Entity *mask) {	
	mask->depthWrite = true;
	mask->depthOnly = true;
	mask->setPositionZ(0.999);
	mask->isMask = true;
	mask->enabled = false;
	maskEntity = mask;
	hasMask = true;
	
//	for(int i=0; i < children.size(); i++) {
//		children[i]->setMask(mask);
//	}
}

void Entity::clearMask() {
	maskEntity->depthWrite = false;
	maskEntity->depthOnly = false;	
	maskEntity->setPositionZ(0);	
	maskEntity->enabled = true;
	maskEntity = NULL;	
	hasMask = false;	
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
	if(ignoreParentMatrix && parentEntity) {
		renderer->multModelviewMatrix(parentEntity->getConcatenatedMatrix().inverse());
		renderer->setCurrentModelMatrix(parentEntity->getConcatenatedMatrix().inverse());
	}else {
		renderer->multModelviewMatrix(transformMatrix);
		renderer->setCurrentModelMatrix(transformMatrix);
	}
	renderer->setVertexColor(color.r,color.g,color.b,color.a);
	if(billboardMode) {
		renderer->billboardMatrixWithScale(getCompoundScale());
		if(billboardRoll) {
			renderer->multModelviewMatrix(getConcatenatedRollMatrix());
		}
	}

//	if(hasMask) {
//		renderer->enableDepthWrite(false);
//		renderer->enableDepthTest(true);		
//	} else {
	if(!depthWrite)
		renderer->enableDepthWrite(false);
	else
		renderer->enableDepthWrite(true);
	
	if(!depthTest) 
		renderer->enableDepthTest(false);
	else
		renderer->enableDepthTest(true);
//	}
		 
	renderer->enableAlphaTest(alphaTest);
	
	Color combined = getCombinedColor();
	renderer->setVertexColor(combined.r,combined.g,combined.b,combined.a);
	
	renderer->setBlendingMode(blendingMode);
	renderer->enableBackfaceCulling(backfaceCulled);
	
	int mode = renderer->getRenderMode();
	if(renderWireframe)
		renderer->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);
	else
		renderer->setRenderMode(Renderer::RENDER_MODE_NORMAL);	
	if(visible) {
		Render();
	}
		
	if(visible || (!visible && !visibilityAffectsChildren)) {
		adjustMatrixForChildren();
		renderChildren();	
	}
		
				
	renderer->setRenderMode(mode);	
	renderer->popMatrix();
	
	if(hasMask) {
		renderer->clearBuffer(false, true);
	}
	
	if(!depthWrite)
		renderer->enableDepthWrite(true);
	
	
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
	
	if(hasMask) {
		newChild->setMask(maskEntity);
	}
}


void Entity::renderChildren() {
	for(int i=0;i<children.size();i++) {
		children[i]->transformAndRender();
	}
}

void Entity::dirtyMatrix(bool val) {
	matrixDirty = val;
}

void Entity::setRotationQuat(Number w, Number x, Number y, Number z) {
	rotationQuat.w = w;
	rotationQuat.x = x;
	rotationQuat.y = y;
	rotationQuat.z = z;
	matrixDirty = true;
}

Quaternion Entity::getRotationQuat() const {
	return rotationQuat;
}

void Entity::setPitch(Number pitch) {
	this->pitch = pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::setYaw(Number yaw) {
	this->yaw = yaw;
	rebuildRotation();	
	matrixDirty = true;
}

Vector3 Entity::getScale() const {
	return scale;
}

Matrix4 Entity::getConcatenatedMatrix() const {
	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedMatrix();
	else
		return transformMatrix;
}

const Matrix4& Entity::getTransformMatrix() const {
	return transformMatrix;
}

void Entity::Pitch(Number pitch) {
	this->pitch += pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Yaw(Number yaw) {
	this->yaw += yaw;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Roll(Number roll) {
	this->roll += roll;
	rebuildRotation();
	matrixDirty = true;
}

void Entity::setRoll(Number roll) {
	this->roll= roll;
	rebuildRotation();
	matrixDirty = true;
}

void Entity::rebuildRotation() {
	rotationQuat.fromAxes(pitch, yaw, roll);
}

String Entity::getEntityProp(const String& propName) {
	for(int i=0; i < entityProps.size(); i++) {
		if(entityProps[i].propName == propName) {
			return entityProps[i].propValue;
		}
	}
	return "null";
}

Vector3 Entity::getCombinedPosition() const {
	if(parentEntity != NULL)
		return (parentEntity->getCombinedPosition())+position;
	else
		return position;
}

void Entity::setParentEntity(Entity *entity) {
	parentEntity = entity;
}

Number Entity::getPitch() const {
	return pitch;
}

Number Entity::getYaw() const {
	return yaw;
}

Number Entity::getRoll() const {
	return roll;
}

void Entity::setTransformByMatrixPure(const Matrix4& matrix) {
	transformMatrix = matrix;
}

void Entity::setTransformByMatrix(const Matrix4& matrix) {
	setPosition(matrix.getPosition());	
	Number x,y,z;
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

void Entity::setPositionX(Number x) {
	position.x = x;
	matrixDirty = true;
}

void Entity::setPositionY(Number y) {
	position.y = y;
	matrixDirty = true;	
}

void Entity::setPositionZ(Number z) {
	position.z = z;
	matrixDirty = true;	
}


void Entity::setScaleX(Number x) {
	scale.x = x;
	matrixDirty = true;	
}

void Entity::setScaleY(Number y) {
	scale.y = y;
	matrixDirty = true;		
}

void Entity::setScaleZ(Number z) {
	scale.z = z;
	matrixDirty = true;		
}


void Entity::setPosition(Number x, Number y, Number z) {
	position.x = x;
	position.y = y;
	position.z = z;
	matrixDirty = true;
}

void Entity::Translate(Vector3 tVec) {
	position += tVec;
	matrixDirty = true;
}

void Entity::Translate(Number x, Number y, Number z) {
	position.x += x;
	position.y += y;
	position.z += z;
	matrixDirty = true;
}

void Entity::Scale(Number x, Number y, Number z) {
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;	
	matrixDirty = true;
}

void Entity::setScale(Number x, Number y, Number z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
	matrixDirty = true;
}

Vector3 Entity::getPosition() const {
	return position;
}

Number Entity::getCombinedPitch() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedPitch()+pitch;
	else
		return pitch;
}

Number Entity::getCombinedYaw() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedYaw()+yaw;
	else
		return yaw;
}

Number Entity::getCombinedRoll() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedRoll()+roll;
	else
		return roll;
	
}
