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

#include "PolyScreenEntityInstance.h"
#include "PolyLogger.h"
#include "PolyCoreServices.h"
#include "PolyResourceManager.h"

using namespace Polycode;

ScreenEntityInstanceResourceEntry::ScreenEntityInstanceResourceEntry(ScreenEntityInstance *instance)  : Resource(Resource::RESOURCE_SCREEN_ENTITY_INSTANCE) {
	this->instance = instance;
}

ScreenEntityInstanceResourceEntry::~ScreenEntityInstanceResourceEntry() {

}

ScreenEntityInstance *ScreenEntityInstanceResourceEntry::getInstance() {
	return instance;
}

void ScreenEntityInstanceResourceEntry::reloadResource() {
	instance->reloadEntityInstance();
	Resource::reloadResource();
}

ScreenEntityInstance *ScreenEntityInstance::BlankScreenEntityInstance() {
	return new ScreenEntityInstance();
}

ScreenEntityInstance::ScreenEntityInstance(const String& fileName) : ScreenEntity() {
	setPositionMode(ScreenEntity::POSITION_CENTER);
	resourceEntry = new ScreenEntityInstanceResourceEntry(this);
	loadFromFile(fileName);
	resourceEntry->setResourceName(fileName);
	resourceEntry->setResourcePath(fileName);
	cloneUsingReload = false;
	ownsChildren = true;
}

ScreenEntityInstance::ScreenEntityInstance() : ScreenEntity() {
	cloneUsingReload = true;
	ownsChildren = true;
	resourceEntry = new ScreenEntityInstanceResourceEntry(this);
}

ScreenEntityInstance::~ScreenEntityInstance() {	
	CoreServices::getInstance()->getResourceManager()->removeResource(resourceEntry);
	delete resourceEntry;
}

void ScreenEntityInstance::reloadEntityInstance() {
	loadFromFile(fileName);
}

ScreenEntityInstanceResourceEntry *ScreenEntityInstance::getResourceEntry() {
	return resourceEntry;
}

Entity *ScreenEntityInstance::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenEntityInstance *newEntity;
	if(cloneUsingReload) {
		newEntity = new ScreenEntityInstance(fileName);
	} else {
		newEntity = new ScreenEntityInstance();
	}
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void ScreenEntityInstance::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	if(cloneUsingReload) {
		ScreenEntity::applyClone(clone, false, ignoreEditorOnly);
	} else {
		ScreenEntity::applyClone(clone, deepClone, ignoreEditorOnly);
		ScreenEntityInstance *_clone = (ScreenEntityInstance*) clone;
		_clone->fileName = fileName;
	}
}

void ScreenEntityInstance::applyScreenShape(ObjectEntry *entry, ScreenShape *shape) {
	if(!entry) 
		return;

	Number swidth = (*entry)["width"]->NumberVal;
	Number sheight = (*entry)["height"]->NumberVal;
	int type = (*entry)["type"]->intVal;

	shape->setShapeType(type);
	shape->setShapeSize(swidth, sheight);

	Number strokeColorR = (*entry)["strokeColorR"]->NumberVal;
	Number strokeColorG = (*entry)["strokeColorG"]->NumberVal;
	Number strokeColorB = (*entry)["strokeColorB"]->NumberVal;
	Number strokeColorA = (*entry)["strokeColorA"]->NumberVal;

	bool strokeEnabled = (*entry)["strokeEnabled"]->boolVal;
	Number strokeWidth = (*entry)["strokeWidth"]->NumberVal;

	shape->strokeEnabled = strokeEnabled;
	shape->strokeWidth = strokeWidth;
	shape->strokeColor = Color(strokeColorR, strokeColorG, strokeColorB, strokeColorA);

}

void ScreenEntityInstance::parseObjectIntoCurve(ObjectEntry *entry, BezierCurve *curve) {
	curve->clearControlPoints();
	ObjectEntry *controlPoints =(*entry)["controlPoints"];
	if(controlPoints) {
		for(int i=0; i < controlPoints->length; i++) {
			ObjectEntry *controlPoint = ((*controlPoints))[i];
			if(controlPoint) {
				Vector2 vpt1;
				Vector2 vpt2;
				Vector2 vpt3;

				ObjectEntry *pt1 = ((*controlPoint))["pt1"];
				if(pt1) {
					vpt1.x = ((*pt1))["x"]->NumberVal;
					vpt1.y = ((*pt1))["y"]->NumberVal;
				}

				ObjectEntry *pt2 = ((*controlPoint))["pt2"];
				if(pt2) {
					vpt2.x = ((*pt2))["x"]->NumberVal;
					vpt2.y = ((*pt2))["y"]->NumberVal;
				}

				ObjectEntry *pt3 = ((*controlPoint))["pt3"];
				if(pt3) {
					vpt3.x = ((*pt3))["x"]->NumberVal;
					vpt3.y = ((*pt3))["y"]->NumberVal;
				}

				curve->addControlPoint(vpt1.x, vpt1.y, 0.0, vpt2.x, vpt2.y, 0.0, vpt3.x, vpt3.y, 0.0);
			}
		}
	}

}

ScreenEntity *ScreenEntityInstance::loadObjectEntryIntoEntity(ObjectEntry *entry, ScreenEntity *targetEntity) {

	ScreenEntity *entity = NULL;

	ObjectEntry *entityType = (*entry)["type"];
	if(entityType) {

		if(entityType->stringVal == "ScreenImage") {
			ObjectEntry *screenImageEntry = (*entry)["ScreenImage"];
			String imagePath = (*screenImageEntry)["filePath"]->stringVal;
			ScreenImage *image = new ScreenImage(imagePath);

			ObjectEntry *screenShapeEntry = (*entry)["ScreenShape"];
			applyScreenShape(screenShapeEntry, image);
			entity = image;
		}

		if(entityType->stringVal == "ScreenParticleEmitter") {
			ObjectEntry *emitterEntry = (*entry)["ScreenParticleEmitter"];

			ScreenParticleEmitter *placingEmitter = new ScreenParticleEmitter((*emitterEntry)["texturePath"]->stringVal, Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, (*emitterEntry)["lifespan"]->NumberVal, (*emitterEntry)["particleCount"]->NumberVal, Vector3((*emitterEntry)["dirX"]->NumberVal, (*emitterEntry)["dirY"]->NumberVal, 0.0), Vector3((*emitterEntry)["gravX"]->NumberVal, (*emitterEntry)["gravY"]->NumberVal, 0.0), Vector3((*emitterEntry)["deviationX"]->NumberVal, (*emitterEntry)["deviationY"]->NumberVal, 0.0), Vector3((*emitterEntry)["radiusX"]->NumberVal, (*emitterEntry)["radiusY"]->NumberVal, 0.0));

			placingEmitter->brightnessDeviation = (*emitterEntry)["brightnessDeviation"]->NumberVal;
			placingEmitter->particleSize = (*emitterEntry)["particleSize"]->NumberVal;
			placingEmitter->perlinModSize = (*emitterEntry)["perlinModSize"]->NumberVal;
			placingEmitter->perlinEnabled = (*emitterEntry)["perlinEnabled"]->boolVal;
			placingEmitter->particleSpeedMod = (*emitterEntry)["particleSpeedMod"]->NumberVal;

			placingEmitter->rotationSpeed = (*emitterEntry)["rotationSpeed"]->NumberVal;
			placingEmitter->rotationFollowsPath = (*emitterEntry)["rotationFollowsPath"]->boolVal;
			placingEmitter->useScaleCurves = (*emitterEntry)["useScaleCurves"]->boolVal;
			placingEmitter->useColorCurves = (*emitterEntry)["useColorCurves"]->boolVal;
			
			bool boolVal;
			if(emitterEntry->readBool("ignoreParentMatrix", &boolVal)) {
				placingEmitter->setIgnoreParentMatrix(boolVal);
			}

			placingEmitter->setParticleBlendingMode((*emitterEntry)["particleBlendMode"]->intVal);

			placingEmitter->setWidth(placingEmitter->emitterRadius.x);
			placingEmitter->setHeight(placingEmitter->emitterRadius.y);

			parseObjectIntoCurve((*emitterEntry)["scaleCurve"], &placingEmitter->scaleCurve);
			parseObjectIntoCurve((*emitterEntry)["colorCurveR"], &placingEmitter->colorCurveR);
			parseObjectIntoCurve((*emitterEntry)["colorCurveG"], &placingEmitter->colorCurveG);
			parseObjectIntoCurve((*emitterEntry)["colorCurveB"], &placingEmitter->colorCurveB);
			parseObjectIntoCurve((*emitterEntry)["colorCurveA"], &placingEmitter->colorCurveA);

			entity = placingEmitter;

		}

		if(entityType->stringVal == "ScreenSprite") {
			ObjectEntry *screenSpriteEntry = (*entry)["ScreenSprite"];
			String filePath = (*screenSpriteEntry)["filePath"]->stringVal;

			ScreenSprite *sprite = new ScreenSprite(filePath);

			String animName = (*screenSpriteEntry)["anim"]->stringVal;
			sprite->playAnimation(animName, -1, false);

			ObjectEntry *screenShapeEntry = (*entry)["ScreenShape"];
			applyScreenShape(screenShapeEntry, sprite);
			entity = sprite;
		}

		if(entityType->stringVal == "ScreenEntityInstance") {
			ObjectEntry *screenInstanceEntry = (*entry)["ScreenEntityInstance"];
			String filePath = (*screenInstanceEntry)["filePath"]->stringVal;
			ScreenEntityInstance *instance = new ScreenEntityInstance(filePath);
			entity = instance;
		}

		if(entityType->stringVal == "ScreenShape") {
			ObjectEntry *screenShapeEntry = (*entry)["ScreenShape"];
			ScreenShape *shape = new ScreenShape(0, 1, 1);
			applyScreenShape(screenShapeEntry, shape);
			entity = shape;
		}

		if(entityType->stringVal == "ScreenSound") {
			ObjectEntry *screenSoundEntry = (*entry)["ScreenSound"];

			String filePath = (*screenSoundEntry)["filePath"]->stringVal;
			Number refDistance = (*screenSoundEntry)["refDistance"]->NumberVal;
			Number maxDistance = (*screenSoundEntry)["maxDistance"]->NumberVal;
			Number volume = (*screenSoundEntry)["volume"]->NumberVal;
			Number pitch = (*screenSoundEntry)["pitch"]->NumberVal;

			ScreenSound *sound = new ScreenSound(filePath, refDistance, maxDistance);
			sound->getSound()->setVolume(volume);
			sound->getSound()->setPitch(pitch);

			sound->setWidth(50);
			sound->setHeight(50);

			entity = sound;
		}

		if(entityType->stringVal == "ScreenLabel") {
			ObjectEntry *screenLabelEntry = (*entry)["ScreenLabel"];

			String text = (*screenLabelEntry)["text"]->stringVal;
			String font = (*screenLabelEntry)["font"]->stringVal;
			int size = (*screenLabelEntry)["size"]->intVal;
			int aaMode = (*screenLabelEntry)["aaMode"]->intVal;

			ScreenLabel *label = new ScreenLabel(text, size, font, aaMode);
			label->positionAtBaseline = false;

			ObjectEntry *screenShapeEntry = (*entry)["ScreenShape"];
			applyScreenShape(screenShapeEntry, label);
			entity = label;
		}

	} 

	if(!entity) {
		if(targetEntity) {
			entity = targetEntity;
		} else {
			entity = new ScreenEntity();
		}
	}

	entity->ownsChildren = true;

	if((*entry)["positionMode"]) {
		entity->setPositionMode((*entry)["positionMode"]->intVal);
	} else {
		entity->setPositionMode(ScreenEntity::POSITION_CENTER);
	}

	Number _width, _height;
	
	if(entry->readNumber("width", &_width)) {
		entity->setWidth(_width);
	}

	if(entry->readNumber("height", &_height)) {
		entity->setHeight(_height);
	}

	entity->color.r = (*entry)["colorR"]->NumberVal;
	entity->color.g = (*entry)["colorG"]->NumberVal;
	entity->color.b = (*entry)["colorB"]->NumberVal;
	entity->color.a = (*entry)["colorA"]->NumberVal;

	if(!targetEntity) {
		entity->blendingMode = (*entry)["blendMode"]->intVal;

		entity->scale.x = (*entry)["scaleX"]->NumberVal;
		entity->scale.y = (*entry)["scaleY"]->NumberVal;

		entity->position.x = (*entry)["posX"]->NumberVal;
		entity->position.y = (*entry)["posY"]->NumberVal;

		entity->setRotation((*entry)["rotation"]->NumberVal);
	} 

	if((*entry)["id"]->stringVal != "") {
		entity->id = (*entry)["id"]->stringVal;
	}

	String tagString = (*entry)["tags"]->stringVal; 
	
	if(tagString != "") {
		std::vector<String> tags = tagString.split(",");
		for(int i=0; i < tags.size(); i++) {
			entity->addTag(tags[i]);
		}
	}

	ObjectEntry *props = (*entry)["props"];
	if(props) {
		for(int i=0; i < props->length; i++) {
			ObjectEntry *prop = ((*props))[i];
			if(prop) {
				entity->setEntityProp((*prop)["name"]->stringVal, (*prop)["value"]->stringVal);
			}
		}
	}

	ObjectEntry *children = (*entry)["children"];

	if(children) {
		for(int i=0; i < children->length; i++) {
			ObjectEntry *childEntry = ((*children))[i];
			ScreenEntity *childEntity = loadObjectEntryIntoEntity(childEntry);
			entity->addChild(childEntity);
		}
	}

	return entity;
}

String ScreenEntityInstance::getFileName() const {
	return fileName;
}

void ScreenEntityInstance::clearInstance() {
	for(int i=0; i < children.size(); i++) {
		removeChild(children[i]);
		children[i]->setOwnsChildrenRecursive(true);
		delete children[i];
	}
}

bool ScreenEntityInstance::loadFromFile(const String& fileName) {

	clearInstance();

	resourceEntry->resourceFileTime = OSBasics::getFileTime(fileName);

	this->ownsChildren = true;
	this->fileName = fileName;
	Object loadObject;
	if(!loadObject.loadFromBinary(fileName)) {
		Logger::log("Error loading entity instance.\n");
	}
	ObjectEntry *root = loadObject.root["root"];

	if(root) {
		loadObjectEntryIntoEntity(root, this);
	}

	return true;
}
