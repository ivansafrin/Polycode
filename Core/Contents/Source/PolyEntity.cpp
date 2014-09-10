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
#include "PolyCoreServices.h"
#include "PolyInputEvent.h"

using namespace Polycode;


int Entity::defaultBlendingMode = Renderer::BLEND_MODE_NORMAL;

Rotation::Rotation() {
	pitch = 0;
	yaw = 0;
	roll = 0;		
}

Entity::Entity() : EventDispatcher() {
	initEntity();
}

Entity::Entity(Number width, Number height, Number depth) : EventDispatcher() {
	initEntity();
	bBox.x = width;
	bBox.y = height;
	bBox.z = depth;		
}

void Entity::initEntity() {
	userData = NULL;
	scale.set(1,1,1);
	renderer = NULL;
	enabled = true;
	depthTest = true;
	visible = true;
	color.setColor(1.0f,1.0f,1.0f,1.0f);
	parentEntity = NULL;
	matrixDirty = true;
	billboardMode = false;
	billboardRoll = false;
	billboardIgnoreScale = false;
	depthOnly = false;
	depthWrite = true;
	ignoreParentMatrix = false;
	blendingMode = Entity::defaultBlendingMode;
	lockMatrix = false;
	colorAffectsChildren = true;
	visibilityAffectsChildren = true;
	ownsChildren = false;
	enableScissor = false;
	processInputEvents = false;
	blockMouseInput = false;
	editorOnly = false; 
	snapToPixels = false;
	tags = NULL;
	bBox.z = 0.001;
	mouseOver = false;
	yAdjust = 1.0;
	lastClickTicks = 0.0;
    rendererVis = true;
    layerID = 0;
}

Entity *Entity::getEntityById(String id, bool recursive) const {
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

Entity *Entity::Clone(bool deepClone, bool ignoreEditorOnly) const {
	Entity *newEntity = new Entity();
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void Entity::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
	clone->ownsChildren = ownsChildren;
	clone->setPosition(position);
	clone->setRotationByQuaternion(rotationQuat);
	clone->setScale(scale);
	clone->color = color;
	clone->billboardMode = billboardMode;	
	clone->billboardRoll = billboardRoll;
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
	clone->snapToPixels = snapToPixels;
    clone->setAnchorPoint(anchorPoint);
    clone->layerID = layerID;
    
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
			if(children[i]->editorOnly && ignoreEditorOnly) {
			} else {
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

std::vector<Entity*> Entity::getEntitiesByLayerID(unsigned char layerID, bool recursive) const {
	std::vector<Entity*> retVector;
    
	for(int i=0;i<children.size();i++) {
		if(children[i]->layerID == layerID) {
			retVector.push_back(children[i]);
		}
		
		if(recursive) {
			std::vector<Entity*> childVector = children[i]->getEntitiesByLayerID(layerID, recursive);
			retVector.insert(retVector.end(), childVector.begin(), childVector.end());
		}
	}
	
	return retVector;
}

std::vector<Entity*> Entity::getEntitiesByTag(String tag, bool recursive) const {

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

void *Entity::getUserData() const {
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
    rotation = rotationQuat.toEulerAngles();
    rotation = rotation * TODEGREES; 
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
            entityToRemove->setParentEntity(NULL);
			children.erase(children.begin()+i);
			return;
		}
	}	
}

void Entity::moveChildUp(Entity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i < children.size()-1) {
			Entity *next = (Entity*)children[i+1];
			children[i+1] = child;
			children[i] = next;
			break;
		}
	}
}

void Entity::moveChildDown(Entity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i > 0) {
			Entity *prev = (Entity*)children[i-1];
			children[i-1] = child;
			children[i] = prev;
			break;
		}
	}
}

void Entity::moveChildTop(Entity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i < children.size()-1) {
			children.erase(children.begin()+i);
			children.push_back(child);
			break;
		}
	}
}

void Entity::moveChildBottom(Entity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i > 0) {
			children.erase(children.begin()+i);
			children.insert(children.begin(), child);
			break;
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
	newChild->setRenderer(renderer);
	newChild->setParentEntity(this);
	newChild->setInverseY(getInverseY());
	children.push_back(newChild);
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

void Entity::setBlendingMode(int newBlendingMode) {
	blendingMode = newBlendingMode;
}

Entity::~Entity() {
	if(ownsChildren) {
		for(int i=0; i < children.size(); i++) {	
			delete children[i];
		}
	}
	if(tags) delete tags;
}

void Entity::setInverseY(bool val) {
	if(val) {
		yAdjust = -1.0;
	} else {
		yAdjust = 1.0;	
	}
	for(int i=0; i < children.size(); i++) {
		children[i]->setInverseY(val);
	}
    matrixDirty = true;
}

bool Entity::getInverseY() {
	return (yAdjust == -1.0);
}

Matrix4 Entity::buildPositionMatrix() {
	Matrix4 posMatrix;
	
	posMatrix.m[3][0] = position.x;
	posMatrix.m[3][1] = position.y * yAdjust;
	posMatrix.m[3][2] = position.z;

	if(snapToPixels) {
		posMatrix.m[3][0] = round(posMatrix.m[3][0]);
		posMatrix.m[3][1] = round(posMatrix.m[3][1]);
		posMatrix.m[3][2] = round(posMatrix.m[3][2]);		
	}

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
	if (enabled) {
		Update();
		for(int i=0; i < children.size(); i++) {
			children[i]->doUpdates();
		}
	}
}

void Entity::doFixedUpdates() {
	if (enabled) {
		fixedUpdate();
		for(int i=0; i < children.size(); i++) {
			children[i]->doFixedUpdates();
		}
	}
}

void Entity::updateEntityMatrix() {

	if(matrixDirty) {
		rebuildTransformMatrix();
        recalculateAABBAllChildren();
	}
    
	for(int i=0; i < children.size(); i++) {
		children[i]->updateEntityMatrix();
	}
}

Vector3 Entity::getCompoundScale() const {
	if(parentEntity != NULL) {
		Vector3 parentScale = parentEntity->getCompoundScale();
		return Vector3(scale.x * parentScale.x, scale.y * parentScale.y, scale.z * parentScale.z);
		
	} else {
		return scale;
	}
}


Matrix4 Entity::getConcatenatedRollMatrix() const {
	Quaternion q;
	q.createFromAxisAngle(0.0f, 0.0f, 1.0f, rotation.z);
	Matrix4 transformMatrix = q.createMatrix();	
	
	if(parentEntity != NULL) 
		return transformMatrix * parentEntity->getConcatenatedRollMatrix();
	else
		return transformMatrix;	
}

Vector2 Entity::getScreenPosition(const Matrix4 &projectionMatrix, const Matrix4 &cameraMatrix, const Polycode::Rectangle &viewport) {
	if(renderer){
		return renderer->Project(cameraMatrix, projectionMatrix, viewport, getConcatenatedMatrix().getPosition());
	} else {
		return Vector2();
	}
}

Vector2 Entity::getScreenPositionForMainCamera() {
	if(renderer) {
		return getScreenPosition(renderer->getProjectionMatrix(), renderer->getCameraMatrix(), renderer->getViewport());
	} else {
		return Vector2();
	}
}

void Entity::transformAndRender() {
	if(!renderer || !enabled)
		return;

	if(matrixDirty) {
		rebuildTransformMatrix();
    }
    
	if(depthOnly) {
		renderer->drawToColorBuffer(false);
	}
	
	bool isScissorEnabled;
	Polycode::Rectangle oldScissorBox;
	
	if(enableScissor) {
		isScissorEnabled = renderer->isScissorEnabled();
		oldScissorBox = renderer->getScissorBox();
		renderer->enableScissor(true);

		Rectangle finalScissorBox = scissorBox;

		// make sure that our scissor box is constrained to the parent one if it exists
		if(isScissorEnabled) {
			finalScissorBox = finalScissorBox.Clipped(renderer->getScissorBox());
		}

		renderer->setScissorBox(finalScissorBox);
	}
		
	renderer->pushMatrix();
	if(ignoreParentMatrix && parentEntity) {
		renderer->multModelviewMatrix(parentEntity->getConcatenatedMatrix().Inverse());
	}

    renderer->multModelviewMatrix(transformMatrix);
	
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
	
    renderer->pushVertexColor();
	renderer->multiplyVertexColor(color);
	
	renderer->setBlendingMode(blendingMode);
	   
	if(visible && rendererVis) {
		renderer->pushMatrix();		
		renderer->translate3D(-anchorPoint.x * bBox.x * 0.5, -anchorPoint.y * bBox.y * 0.5 * yAdjust, -anchorPoint.z * bBox.z * 0.5);
		Render();
		renderer->popMatrix();
	}
    
    if(!colorAffectsChildren) {
        renderer->pushVertexColor();
        renderer->loadVertexColorIdentity();
        if(visible || (!visible && !visibilityAffectsChildren)) {
            renderChildren();
        }
        renderer->popVertexColor();
    } else {
        if(visible || (!visible && !visibilityAffectsChildren)) {
            renderChildren();
        }
    }
		
    renderer->popVertexColor();
    
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


void Entity::renderChildren() {
	for(int i=0;i<children.size();i++) {
		children[i]->transformAndRender();
	}
}

void Entity::dirtyMatrix(bool val) {
	matrixDirty = val;
}

void Entity::recalculateAABBAllChildren() {
    recalculateAABB();
    for(int i=0; i< children.size(); i++) {
        children[i]->recalculateAABBAllChildren();
    }
}

void Entity::recalculateAABB() {

    aabb.min = Vector3();
    aabb.max = Vector3();
    
    Vector3 bBoxCoords[8] = {
        Vector3(-bBox.x * 0.5, -bBox.y * 0.5, bBox.z * 0.5),
        Vector3(bBox.x * 0.5, -bBox.y * 0.5, bBox.z * 0.5),
        Vector3(-bBox.x * 0.5, -bBox.y * 0.5, -bBox.z * 0.5),
        Vector3(bBox.x * 0.5, -bBox.y * 0.5, -bBox.z * 0.5),
        Vector3(-bBox.x * 0.5, bBox.y * 0.5, bBox.z * 0.5),
        Vector3(bBox.x * 0.5, bBox.y * 0.5, bBox.z * 0.5),
        Vector3(-bBox.x * 0.5, bBox.y * 0.5, -bBox.z * 0.5),
        Vector3(bBox.x * 0.5, bBox.y * 0.5, -bBox.z * 0.5)
    };
    
    Matrix4 fullMatrix = getAnchorAdjustedMatrix();
    if(ignoreParentMatrix) {
        if(matrixDirty) {
            rebuildTransformMatrix();
        }
        fullMatrix = transformMatrix;
    }
    
    for(int i=0; i < 8; i++) {
        bBoxCoords[i] = fullMatrix * bBoxCoords[i];
        if(i ==0 ) {
            aabb.min = bBoxCoords[i];
            aabb.max = bBoxCoords[i];
        } else {
            if(bBoxCoords[i].x < aabb.min.x) {
                aabb.min.x = bBoxCoords[i].x;
            }
            if(bBoxCoords[i].y < aabb.min.y) {
                aabb.min.y = bBoxCoords[i].y;
            }
            if(bBoxCoords[i].z < aabb.min.z) {
                aabb.min.z = bBoxCoords[i].z;
            }
            
            if(bBoxCoords[i].x > aabb.max.x) {
                aabb.max.x = bBoxCoords[i].x;
            }
            if(bBoxCoords[i].y > aabb.max.y) {
                aabb.max.y = bBoxCoords[i].y;
            }
            if(bBoxCoords[i].z > aabb.max.z) {
                aabb.max.z = bBoxCoords[i].z;
            }
        }
    }
        
}

AABB Entity::getWorldAABB() {
    return aabb;
}

Vector3 Entity::getLocalBoundingBox() {
    return bBox;
}

void Entity::setLocalBoundingBox(const Vector3 box) {
    bBox = box;
    recalculateAABB();
    matrixDirty = true;
}

void Entity::setLocalBoundingBox(Number x, Number y, Number z) {
    bBox.set(x, y, z);
    recalculateAABB();
    matrixDirty = true;
}

void Entity::setLocalBoundingBoxX(Number x) {
    bBox.x = x;
    recalculateAABB();
    matrixDirty = true;
}

void Entity::setLocalBoundingBoxY(Number y) {
    bBox.y = y;
    recalculateAABB();
    matrixDirty = true;
}

void Entity::setLocalBoundingBoxZ(Number z) {
    bBox.z = z;
    recalculateAABB();
    matrixDirty = true;
}

void Entity::setRotationQuat(Number w, Number x, Number y, Number z) {
	rotationQuat.w = w;
	rotationQuat.x = x;
	rotationQuat.y = y;
	rotationQuat.z = z;
    rotation = rotationQuat.toEulerAngles();
    rotation = rotation * TODEGREES;
	matrixDirty = true;
}

void Entity::setRotationByQuaternion(const Quaternion &quaternion) {
	rotationQuat = quaternion;
    rotation = quaternion.toEulerAngles();
    rotation = rotation * TODEGREES;
	matrixDirty = true;
}

Quaternion Entity::getRotationQuat() const {
	return rotationQuat;
}

Quaternion Entity::getConcatenatedQuat() const {
    if(parentEntity ) {
        return rotationQuat * parentEntity->getConcatenatedQuat();
    } else {
        return rotationQuat;
    }
}

Vector3 Entity::getScale() const {
	return scale;
}

Vector3 Entity::getRotationEuler() const {
    return rotation;
}

Matrix4 Entity::getConcatenatedMatrixRelativeTo(Entity *relativeEntity) {
	
	if(matrixDirty) {
		rebuildTransformMatrix();
    }

	if(parentEntity != NULL && parentEntity != relativeEntity)
		return transformMatrix * parentEntity->getConcatenatedMatrixRelativeTo(relativeEntity);
	else
		return transformMatrix;
}

Matrix4 Entity::getAnchorAdjustedMatrix() {
	Matrix4 mat = getConcatenatedMatrix();
	Matrix4 adjust;
	adjust.setPosition(-anchorPoint.x * bBox.x * 0.5, -anchorPoint.y * bBox.y * 0.5 * yAdjust, -anchorPoint.z * bBox.z * 0.5);
	return adjust * mat;
}

Matrix4 Entity::getConcatenatedMatrix() {
	if(matrixDirty) {
		rebuildTransformMatrix();
    }
    
	if(parentEntity != NULL && !ignoreParentMatrix) 
		return transformMatrix * parentEntity->getConcatenatedMatrix();
	else
		return transformMatrix;
}

const Matrix4& Entity::getTransformMatrix() const {
	return transformMatrix;
}

void Entity::Pitch(Number pitch) {
	rotation.x += pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Yaw(Number yaw) {
	rotation.y += yaw;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::Roll(Number roll) {
	rotation.z += roll;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::setRoll(Number roll) {
	rotation.z = roll;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::setPitch(Number pitch) {
	rotation.x = pitch;
	rebuildRotation();	
	matrixDirty = true;
}

void Entity::setYaw(Number yaw) {
	rotation.y = yaw;
	rebuildRotation();
	matrixDirty = true;
}

void Entity::setRotationEuler(const Vector3 &rotation) {
    this->rotation = rotation;
    rebuildRotation();
    matrixDirty = true;
}

void Entity::rebuildRotation() {
	rotationQuat.fromAxes(rotation.x, rotation.y, rotation.z);
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

void Entity::setWidth(Number width) {
	setLocalBoundingBoxX(width);
}

void Entity::setHeight(Number height) {
	setLocalBoundingBoxY(height);
}

void Entity::setDepth(Number depth) {
	setLocalBoundingBoxZ(depth);
}

Number Entity::getWidth() const {
	return bBox.x;
}

Number Entity::getHeight() const {
	return bBox.y;
}

Number Entity::getDepth() const {
	return bBox.z;
}

Number Entity::getPitch() const {
	return rotation.x;
}

Number Entity::getYaw() const {
	return rotation.y;
}

Number Entity::getRoll() const {
	return rotation.z;
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

void Entity::Scale(const Vector3 &scale) {
	this->scale = this->scale * scale;
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

Vector2 Entity::getPosition2D() const {
	return Vector2(position.x, position.y);
}

Number Entity::getCombinedPitch() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedPitch()+rotation.x;
	else
		return rotation.x;
}

Number Entity::getCombinedYaw() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedYaw()+rotation.y;
	else
		return rotation.y;
}

Number Entity::getCombinedRoll() const {
	if(parentEntity != NULL)
		return parentEntity->getCombinedRoll()+rotation.z;
	else
		return rotation.z;
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

void Entity::setAnchorPoint(const Vector3 &anchorPoint) {
	this->anchorPoint = anchorPoint;
    matrixDirty = true;
}

void Entity::setAnchorPoint(Number x, Number y, Number z) {
	anchorPoint.set(x,y,z);
    matrixDirty = true;
}

Vector3 Entity::getAnchorPoint() const {
	return anchorPoint;
}


MouseEventResult Entity::onMouseDown(const Ray &ray, int mouseButton, int timestamp) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;
    Number hitDistance;
	
	if(processInputEvents && enabled) {
        hitDistance = ray.boxIntersect(bBox, getAnchorAdjustedMatrix());
		if(hitDistance >= 0.0) {
			if(customHitDetection(ray)) {
				ret.hit = true;	
				
				Vector3 localCoordinate = Vector3(ray.origin.x,ray.origin.y,0);
				Matrix4 inverse = getConcatenatedMatrix().Inverse();
				localCoordinate = inverse * localCoordinate;			
				
				InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
                inputEvent->hitDistance = hitDistance;
				inputEvent->mouseButton = mouseButton;
				dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEDOWN);
				
				if(timestamp - lastClickTicks < 400) {
					InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
					inputEvent->mouseButton = mouseButton;
					dispatchEvent(inputEvent, InputEvent::EVENT_DOUBLECLICK);
				}
				lastClickTicks = timestamp;			
							
				if(blockMouseInput) {
					ret.blocked = true;
				}
			}
		}
		
		for(int i=children.size()-1; i>=0; i--) {
			MouseEventResult childRes = children[i]->onMouseDown(ray, mouseButton, timestamp);
				if(childRes.hit)
					ret.hit = true;
				
				if(childRes.blocked) {
					ret.blocked = true;
					break;
				}			
		}
	}
	return ret;
}

MouseEventResult Entity::onMouseUp(const Ray &ray, int mouseButton, int timestamp) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;
	Number hitDistance;
    
	if(processInputEvents && enabled) {
	
		Vector3 localCoordinate = Vector3(ray.origin.x,ray.origin.y,0);
		Matrix4 inverse = getConcatenatedMatrix().Inverse();
		localCoordinate = inverse * localCoordinate;			
	
		InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
		inputEvent->mouseButton = mouseButton;			

        hitDistance = ray.boxIntersect(bBox, getAnchorAdjustedMatrix());
		if(hitDistance >= 0.0) {
			ret.hit = true;
			inputEvent->hitDistance = hitDistance;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP);
			if(blockMouseInput) {
				ret.blocked = true;
			}
		} else {
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP_OUTSIDE);
		}
		
		for(int i=children.size()-1; i>=0; i--) {
			MouseEventResult childRes = children[i]->onMouseUp(ray, mouseButton, timestamp);
				if(childRes.hit)
					ret.hit = true;
				
				if(childRes.blocked) {
					ret.blocked = true;
					break;
				}			
		}
	}
	return ret;}

MouseEventResult Entity::onMouseMove(const Ray &ray, int timestamp) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;
    Number hitDistance;
    
	if(processInputEvents && enabled) {
	
		Vector3 localCoordinate = Vector3(ray.origin.x,ray.origin.y,0);
		Matrix4 inverse = getConcatenatedMatrix().Inverse();
		localCoordinate = inverse * localCoordinate;	
        
        hitDistance = ray.boxIntersect(bBox, getAnchorAdjustedMatrix());
		if(hitDistance >= 0.0) {
			//setColor(1.0, 0.0, 0.0, 1.0);
			ret.hit = true;
            InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
            inputEvent->hitDistance = hitDistance;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEMOVE);
			
			if(!mouseOver) {
                InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
                inputEvent->hitDistance = hitDistance;
				dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEOVER);
				mouseOver = true;
			}			
			
			if(blockMouseInput) {
				ret.blocked = true;
			}
		} else {
			if(mouseOver) {
				dispatchEvent(new InputEvent(Vector2(localCoordinate.x, localCoordinate.y), timestamp), InputEvent::EVENT_MOUSEOUT);
				mouseOver = false;
			}		
		}
		
		for(int i=children.size()-1; i>=0; i--) {
			MouseEventResult childRes = children[i]->onMouseMove(ray, timestamp);
				if(childRes.hit)
					ret.hit = true;
				
				if(childRes.blocked) {
					ret.blocked = true;
					break;
				}			
		}
	}
	return ret;
}

MouseEventResult Entity::onMouseWheelUp(const Ray &ray, int timestamp) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;
    Number hitDistance;
	
	if(processInputEvents && enabled) {
        hitDistance = ray.boxIntersect(bBox, getAnchorAdjustedMatrix());
		if(hitDistance >= 0.0) {
			ret.hit = true;	
			
			Vector3 localCoordinate = Vector3(ray.origin.x,ray.origin.y,0);
			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;			
			
			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
            inputEvent->hitDistance = hitDistance;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEWHEEL_UP);
												
			if(blockMouseInput) {
				ret.blocked = true;
			}
		}
		
		for(int i=children.size()-1; i>=0; i--) {
			MouseEventResult childRes = children[i]->onMouseWheelUp(ray, timestamp);
				if(childRes.hit)
					ret.hit = true;
				
				if(childRes.blocked) {
					ret.blocked = true;
					break;
				}			
		}
	}
	return ret;
}

MouseEventResult Entity::onMouseWheelDown(const Ray &ray, int timestamp) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;
	Number hitDistance;
    
	if(processInputEvents && enabled) {
        hitDistance = ray.boxIntersect(bBox, getAnchorAdjustedMatrix());
		if(hitDistance >= 0.0) {
			ret.hit = true;	
			
			Vector3 localCoordinate = Vector3(ray.origin.x,ray.origin.y,0);
			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;			
			
			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x, localCoordinate.y*yAdjust), timestamp);
            inputEvent->hitDistance = hitDistance;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEWHEEL_DOWN);
												
			if(blockMouseInput) {
				ret.blocked = true;
			}
		}
		
		for(int i=children.size()-1; i>=0; i--) {
			MouseEventResult childRes = children[i]->onMouseWheelDown(ray, timestamp);
				if(childRes.hit)
					ret.hit = true;
				
				if(childRes.blocked) {
					ret.blocked = true;
					break;
				}			
		}
	}
	return ret;
}
