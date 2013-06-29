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
#include "PolyRenderer.h"

using namespace Polycode;

Rotation::Rotation() {
	pitch = 0;
	yaw = 0;
	roll = 0;
}

Entity::Entity() : EventDispatcher() {
	userData = NULL;
	scale.set(1,1,1);
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
	billboardIgnoreScale = false;
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
	ownsChildren = false;
	enableScissor = false;

	editorOnly = false; 

	tags = NULL;
}

Entity *Entity::getEntityById(String id, bool recursive) {
	for(int i=0;i<children.size();i++) {
		if(children[i]->id == id) {
			return children[i];
		} else {
			if(recursive) {
				Entity *ret = children[i]->getEntityById(id, recursive);
				if(ret) {
					return ret;
				}
			}
		}
	}
	return NULL;
}

Entity *Entity::Clone(bool deepClone, bool ignoreEditorOnly) {
	Entity *newEntity = new Entity();
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void Entity::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	clone->ownsChildren = ownsChildren;
	clone->position = position;
	clone->rotation = rotation;
	clone->scale = scale;
	clone->color = color;
	clone->custEntityType = custEntityType;
	clone->billboardMode = billboardMode;
	clone->billboardRoll = billboardRoll;
	clone->alphaTest = alphaTest;
	clone->backfaceCulled = backfaceCulled;
	clone->renderWireframe = renderWireframe;
	clone->depthWrite = depthWrite;
	clone->depthTest = depthTest;
	clone->blendingMode = blendingMode;
	clone->colorAffectsChildren = colorAffectsChildren;
	clone->visibilityAffectsChildren = visibilityAffectsChildren;
	clone->depthOnly = depthOnly;
	clone->setUserData(getUserData());
	clone->entityProps = entityProps;
	clone->bBox = bBox;
	clone->ignoreParentMatrix = ignoreParentMatrix;
	clone->enableScissor = enableScissor;
	clone->scissorBox = scissorBox;
	clone->editorOnly = editorOnly;	
	clone->id = id;
	if(tags == NULL) {
		clone->tags = NULL;
	} else {
		clone->tags = new std::vector<String>();
		for(int i=0; i < tags->size(); i++) {
			clone->addTag((*tags)[i]);
		}
	}
	clone->setRenderer(renderer);

	if(deepClone) {
		for(int i=0; i < children.size(); i++) {
			if(!(children[i]->editorOnly && ignoreEditorOnly)) {
				Entity *childClone = children[i]->Clone(deepClone, ignoreEditorOnly);
				clone->addChild(childClone);
			}
		}
	}
}

void Entity::setOwnsChildrenRecursive(bool val) {
	ownsChildren = val;
	for(int i=0; i < children.size(); i++) {
		children[i]->setOwnsChildrenRecursive(val);
	}
}

std::vector<Entity*> Entity::getEntitiesByTag(String tag, bool recursive) {

	std::vector<Entity*> retVector;

	for(int i=0;i<children.size();i++) {
		if(children[i]->hasTag(tag)) {
			retVector.push_back(children[i]);
		}

		if(recursive) {
			std::vector<Entity*> childVector = children[i]->getEntitiesByTag(tag, recursive);
			retVector.insert(retVector.end(), childVector.begin(), childVector.end());
		}
	}

	return retVector;
}


void Entity::setUserData(void *userData) {
	this->userData = userData;
}

void *Entity::getUserData() {
	return userData;
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
			return;
		}
	}
}

unsigned int Entity::getNumChildren() {
	return children.size();
}

Entity *Entity::getChildAtIndex(unsigned int index) {
	if(index < children.size()) {
		return children[index];
	}
	return NULL;
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
	if(ownsChildren) {
		for(int i=0; i < children.size(); i++) {
			delete children[i];
		}
	}
	if(tags) delete tags;
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

void Entity::checkTransformSetters() {
	if(_position != position) {
		_position = position;
		matrixDirty = true;
	}

	if(_scale != scale) {
		_scale = scale;
		matrixDirty = true;
	}

	if(_rotation != rotation) {
		_rotation = rotation;
		rebuildRotation();
		matrixDirty = true;
	}
}

void Entity::updateEntityMatrix() {
	checkTransformSetters();

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
	q.createFromAxisAngle(0.0f, 0.0f, 1.0f, _rotation.roll*matrixAdj);
	Matrix4 transformMatrix = q.createMatrix();

	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedRollMatrix();
	else
		return transformMatrix;	
}


void Entity::transformAndRender() {
	if(!renderer || !enabled)
		return;

	if(depthOnly) {
		renderer->drawToColorBuffer(false);
	}

	bool isScissorEnabled;
	Polycode::Rectangle oldScissorBox;

	if(enableScissor) {
		isScissorEnabled = renderer->isScissorEnabled();
		oldScissorBox = renderer->getScissorBox();
		renderer->enableScissor(true);

		Polycode::Rectangle finalScrissorBox = scissorBox;

		// make sure that our scissor box is constrained to the parent one if it exists
		if(isScissorEnabled) {
			if(finalScrissorBox.x < oldScissorBox.x)
				finalScrissorBox.x = oldScissorBox.x;
			if(finalScrissorBox.x > oldScissorBox.x + oldScissorBox.w)
				finalScrissorBox.x = oldScissorBox.x + oldScissorBox.w;


			if(finalScrissorBox.x+finalScrissorBox.w > oldScissorBox.x + oldScissorBox.w)
				finalScrissorBox.w = oldScissorBox.x + oldScissorBox.w - finalScrissorBox.x;

			if(finalScrissorBox.y < oldScissorBox.y)
				finalScrissorBox.y = oldScissorBox.y;
			if(finalScrissorBox.y > oldScissorBox.y + oldScissorBox.h)
				finalScrissorBox.y = oldScissorBox.y + oldScissorBox.h;

			if(finalScrissorBox.y+finalScrissorBox.h > oldScissorBox.y + oldScissorBox.h)
				finalScrissorBox.h = oldScissorBox.y + oldScissorBox.h - finalScrissorBox.y;

		}

		renderer->setScissorBox(finalScrissorBox);
	}

	renderer->pushMatrix();
	if(ignoreParentMatrix && parentEntity) {
		renderer->multModelviewMatrix(parentEntity->getConcatenatedMatrix().Inverse());
//		renderer->setCurrentModelMatrix(parentEntity->getConcatenatedMatrix().Inverse());
	}

		renderer->multModelviewMatrix(transformMatrix);
		renderer->setCurrentModelMatrix(transformMatrix);
		
	renderer->setVertexColor(color.r,color.g,color.b,color.a);

	if(billboardMode) {
		if(billboardIgnoreScale) {
			renderer->billboardMatrix();
		} else {
			renderer->billboardMatrixWithScale(getCompoundScale());
		}
		if(billboardRoll) {
			renderer->multModelviewMatrix(getConcatenatedRollMatrix());
		}
	}

	if(!depthWrite)
		renderer->enableDepthWrite(false);
	else
		renderer->enableDepthWrite(true);

	if(!depthTest) 
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

	if(!depthWrite)
		renderer->enableDepthWrite(true);


	if(depthOnly) {
		renderer->drawToColorBuffer(true);
	}

	if(enableScissor) {
		renderer->enableScissor(isScissorEnabled);
		renderer->setScissorBox(oldScissorBox);
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

Vector3 Entity::getScale() const {
	return scale;
}

Matrix4 Entity::getConcatenatedMatrixRelativeTo(Entity *relativeEntity) {
	checkTransformSetters();

	if(matrixDirty)
		rebuildTransformMatrix();

	if(parentEntity != NULL && parentEntity != relativeEntity) 
		return transformMatrix * parentEntity->getConcatenatedMatrixRelativeTo(relativeEntity);
	else
		return transformMatrix;
}

Matrix4 Entity::getConcatenatedMatrix() {
	checkTransformSetters();
	if(matrixDirty)
		rebuildTransformMatrix();

	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedMatrix();
	else
		return transformMatrix;
}

const Matrix4& Entity::getTransformMatrix() const {
	return transformMatrix;
}

void Entity::Pitch(Number pitch) {
	rotation.pitch += pitch;
	matrixDirty = true;
}

void Entity::Yaw(Number yaw) {
	rotation.yaw += yaw;
	matrixDirty = true;
}

void Entity::Roll(Number roll) {
	rotation.roll += roll;
	matrixDirty = true;
}

void Entity::setRoll(Number roll) {
	rotation.roll = roll;
	matrixDirty = true;
}

void Entity::setPitch(Number pitch) {
	rotation.pitch = pitch;
	matrixDirty = true;
}

void Entity::setYaw(Number yaw) {
	rotation.yaw = yaw;
	matrixDirty = true;
}


void Entity::rebuildRotation() {
	rotationQuat.fromAxes(_rotation.pitch, _rotation.yaw, _rotation.roll);
}

void Entity::setEntityProp(const String& propName, const String& propValue) {

	for(int i=0; i < entityProps.size(); i++) {
		if(entityProps[i].propName == propName) {
			entityProps[i].propValue = propValue;
			return;
		}
	}

	EntityProp entityProp;
	entityProp.propName = propName;
	entityProp.propValue = propValue;
	entityProps.push_back(entityProp);
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
	return rotation.pitch;
}

Number Entity::getYaw() const {
	return rotation.yaw;
}

Number Entity::getRoll() const {
	return rotation.roll;
}

void Entity::setTransformByMatrixPure(const Matrix4& matrix) {
	transformMatrix = matrix;
}

void Entity::setPosition(const Vector3 &posVec) {
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

void Entity::setScale(const Vector3 &v) {
	scale.x = v.x;
	scale.y = v.y;
	scale.z = v.z;
	matrixDirty = true;
}

void Entity::setPosition(Number x, Number y, Number z) {
	position.x = x;
	position.y = y;
	position.z = z;
	matrixDirty = true;
}

void Entity::Translate(const Vector3 &tVec) {
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
		return parentEntity->getCombinedPitch()+rotation.pitch;
	else
		return rotation.pitch;
}

Number Entity::getCombinedYaw() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedYaw()+rotation.yaw;
	else
		return rotation.yaw;
}

Number Entity::getCombinedRoll() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedRoll()+rotation.roll;
	else
		return rotation.roll;
}

unsigned int Entity::getNumTags() const {
	if(!tags) return 0;
	return tags->size();
}

String Entity::getTagAtIndex(unsigned int index) const {
	if(!tags) return "";
	if(index < tags->size())
		return (*tags)[index];
	return "";
}

bool Entity::hasTag(String tag) const {
	if(!tags) return false;
	for(int i=0; i < tags->size(); i++) {
		if((*tags)[i] == tag)
			return true;
	}
	return false;
}

void Entity::clearTags() {
	if(!tags) return;
	tags->clear();
}

void Entity::addTag(String tag) {
	if(!tags) tags = new std::vector<String>();
	if(!hasTag(tag)) {
		tags->push_back(tag);
	}
}

