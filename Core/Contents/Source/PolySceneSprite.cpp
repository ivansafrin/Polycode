/*
 Copyright (C) 2013 by Ivan Safrin
 
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

#include "PolySceneSprite.h"
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyTexture.h"

using std::vector;
using namespace Polycode;

SceneSpriteResourceEntry::SceneSpriteResourceEntry(SceneSprite *sprite)  : Resource(Resource::RESOURCE_SCREEN_ENTITY_INSTANCE) {
	this->sprite = sprite;
}

SceneSpriteResourceEntry::~SceneSpriteResourceEntry() {

}

SceneSprite *SceneSpriteResourceEntry::getSprite() {
	return sprite;
}

void SceneSpriteResourceEntry::reloadResource() {
	sprite->reloadSprite();
	Resource::reloadResource();
}

SceneSprite* SceneSprite::SceneSpriteFromImageFile(const String& fileName, Number spriteWidth, Number spriteHeight) {
	return new SceneSprite(fileName, spriteWidth, spriteHeight);
}

SceneSprite::SceneSprite(const String& fileName) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1) {

	currentFrame = 0;
	currentAnimation = NULL;	
	paused = false;

	resourceEntry = new SceneSpriteResourceEntry(this);		
	loadFromFile(fileName);
	resourceEntry->setResourceName(fileName);
	resourceEntry->setResourcePath(fileName);	
}

Entity *SceneSprite::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneSprite *newSprite = new SceneSprite(getTexture()->getResourcePath(), spriteWidth, spriteHeight);
	for(int i=0; i < animations.size(); i++) {
		newSprite->addAnimation(animations[i]->name, animations[i]->frames, animations[i]->speed);
	}
	if(currentAnimation) {
		newSprite->playAnimation(currentAnimation->name, currentFrame, playingOnce);
	}
	applyClone(newSprite, deepClone, ignoreEditorOnly);
	return newSprite;
}

void SceneSprite::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
//	ScreenShape::applyClone(clone, deepClone, ignoreEditorOnly);	
}

bool SceneSprite::loadFromFile(const String& fileName) {
	Object loadObject;
	
	animations.clear();
	
	if(!loadObject.loadFromXML(fileName)) {
		return false;
	}
	
	this->fileName = fileName;
	
	ObjectEntry *image = loadObject.root["image"];
	if(image) {
		ObjectEntry *frameWidth = (*image)["frameWidth"];
		ObjectEntry *frameHeight = (*image)["frameHeight"];	
		ObjectEntry *fileName = (*image)["fileName"];
		
		if(fileName) {
			loadTexture(fileName->stringVal);
		}

		if(frameWidth && frameHeight) {
			
			setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, frameWidth->NumberVal, frameHeight->NumberVal);
			setSpriteSize(frameWidth->NumberVal, frameHeight->NumberVal);
		}
	}
	
	ObjectEntry *animationsEntry = loadObject.root["animations"];
	
	if(animationsEntry) {
		for(int i=0; i < animationsEntry->length; i++) {
			ObjectEntry *animation = (*animationsEntry)[i];
			if(animation) {
				ObjectEntry *name = (*animation)["name"];
				ObjectEntry *frames = (*animation)["frames"];	
				ObjectEntry *speed = (*animation)["speed"];
				
				if(name && frames && speed) {
					addAnimation(name->stringVal, frames->stringVal, speed->NumberVal);
				} else {
					printf("Error parsing animation node\n");
				}
			}
		}
	}
	
	recalculateSpriteDimensions();

	return true;
}

unsigned int SceneSprite::getNumAnimations() {
	return animations.size();
}

SpriteAnimation *SceneSprite::getAnimationAtIndex(unsigned int index) {
	if(index < animations.size()) {
		return animations[index];
	} else {
		return NULL;
	}
}

void SceneSprite::reloadSprite() {
	
	String _animName = "";
	int _currentFrame;
	bool _playingOnce;
	
	if(currentAnimation) {
		_animName = currentAnimation->name;
		_currentFrame = currentFrame;
		_playingOnce = playingOnce;
	}
	loadFromFile(fileName);
	
	if(_animName != "") {
		playAnimation(_animName, _currentFrame, _playingOnce);
	}
}

SceneSpriteResourceEntry *SceneSprite::getResourceEntry() {
	return resourceEntry;
}

SceneSprite::SceneSprite(const String& fileName, Number spriteWidth, Number spriteHeight) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;	
	loadTexture(fileName);
		
	recalculateSpriteDimensions();
	currentFrame = 0;
	currentAnimation = NULL;	
	paused = false;
	setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, spriteWidth, spriteHeight);	
}

SceneSprite::~SceneSprite() {
	
}

void SceneSprite::recalculateSpriteDimensions() {
	if(!texture)
		return;
		
	spriteUVWidth = 1.0f / ((Number) texture->getWidth() / spriteWidth);
	spriteUVHeight = 1.0f / ((Number) texture->getHeight() / spriteHeight);
	
	for(int i =0 ; i < animations.size(); i++) {
		animations[i]->numFramesX = texture->getWidth() / spriteWidth;	
		if(animations[i]->numFramesX < 1) {
			animations[i]->numFramesX = 1;
		}
		animations[i]->numFramesY = texture->getHeight() / spriteHeight;
		if(animations[i]->numFramesY < 1) {
			animations[i]->numFramesY = 1;
		}		
		animations[i]->spriteUVWidth = spriteUVWidth;
		animations[i]->spriteUVHeight = spriteUVHeight;	
		animations[i]->setOffsetsFromFrameString(animations[i]->frames);
	}
}

Vector2 SceneSprite::getSpriteSize() {
	return Vector2(spriteWidth, spriteHeight);
}

String SceneSprite::getFileName() const {
	return fileName;
}

void SceneSprite::setSpriteSize(const Number spriteWidth, const Number spriteHeight) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;	
	
	recalculateSpriteDimensions();	
}

SpriteAnimation *SceneSprite::getCurrentAnimation() {
	return currentAnimation;
}

unsigned int SceneSprite::getCurrentAnimationFrame() { 
   return currentFrame; 
}

bool SceneSprite::isCurrentAnimationFinished() {
    if(currentAnimation) {
        if(currentFrame >= currentAnimation->numFrames)
            return true;
    }
    return false;
}

void SpriteAnimation::setOffsetsFromFrameString(const String& frames) {
	framesOffsets.clear();
	vector<String> frameNumbers = frames.split(",");
	
	int frameNumber;
	int frameX;
	int frameY;
	
	numFrames = 0;
	
	for(int i=0; i < frameNumbers.size(); i++) {
		if(frameNumbers[i].find_first_of("-") != -1) {
			vector<String> _frameNumbers = frameNumbers[i].split("-");
			if(_frameNumbers.size() > 1) {
				int frameNumberStart = atoi(_frameNumbers[0].c_str());
				int frameNumberEnd = atoi(_frameNumbers[1].c_str());
				int dir = 1;
				if(frameNumberEnd < frameNumberStart) {
					dir = -1;
				}				
				for(int j=frameNumberStart; j != frameNumberEnd + dir; j += dir) {
					frameX = j % numFramesX;
					frameY = j/numFramesX;
					framesOffsets.push_back(Vector2(spriteUVWidth * frameX, spriteUVHeight * frameY));
					numFrames++;
				}
			}
		} else if(frameNumbers[i].find_first_of("x") != -1) {
			vector<String> _frameNumbers = frameNumbers[i].split("x");
			if(_frameNumbers.size() > 1) {
				int _frameNumber = atoi(_frameNumbers[0].c_str());
				int frameNumberCount = atoi(_frameNumbers[1].c_str());				
				for(int j=0; j < frameNumberCount; j++) {
					frameX = _frameNumber % numFramesX;
					frameY = _frameNumber/numFramesX;
					framesOffsets.push_back(Vector2(spriteUVWidth * frameX, spriteUVHeight * frameY));
					numFrames++;					
				}
			}				
		} else {	
			frameNumber = atoi(frameNumbers[i].c_str());
			frameX = frameNumber % numFramesX;
			frameY = frameNumber/numFramesX;
			framesOffsets.push_back(Vector2(spriteUVWidth * frameX, spriteUVHeight * frameY));
			numFrames++;			
		}
	}
	
	this->frames = frames;

}

SpriteAnimation *SceneSprite::addAnimation(const String& name, const String& frames, Number speed) {
	SpriteAnimation *newAnimation = new SpriteAnimation();	
	
	
	newAnimation->numFramesX = texture->getWidth() / spriteWidth;	
	if(newAnimation->numFramesX < 1) {
		newAnimation->numFramesX = 1;
	}
	newAnimation->numFramesY = texture->getHeight() / spriteHeight;
	if(newAnimation->numFramesY < 1) {
		newAnimation->numFramesY = 1;
	}	
	newAnimation->spriteUVWidth = spriteUVWidth;
	newAnimation->spriteUVHeight = spriteUVHeight;
	
	newAnimation->setOffsetsFromFrameString(frames);
			
	newAnimation->speed = speed;
	newAnimation->name = name;
	animations.push_back(newAnimation);
	return newAnimation;
}

void SceneSprite::playAnimation(const String& name, int startFrame, bool once) {
	paused = false;
	for(int i=0; i < animations.size(); i++) {
		if(animations[i]->name == name) {
			if(currentAnimation == animations[i] && !playingOnce && !once)
				return;
			currentFrame = 0;			
			currentAnimation = animations[i];
			if(startFrame == -1) {
				currentFrame = rand() % currentAnimation->numFrames;
			} else {
				if(startFrame < currentAnimation->numFrames) {
					currentFrame = startFrame;
				}
			}
			playingOnce = once;
			lastTick = 0;
		}
	}
}

void SceneSprite::Pause(bool val) {
	paused = val;
}

void SceneSprite::showFrame(unsigned int frameIndex) {
	if(!currentAnimation)
		return;

	if(frameIndex < currentAnimation->numFrames) {
		currentFrame = frameIndex;
		updateSprite();
	}
}

void SceneSprite::Update() {
	if(!currentAnimation)
		return;
	
	Number newTick = CoreServices::getInstance()->getCore()->getTicksFloat();
	
	Number elapsed = newTick - lastTick;
	
	if(paused)
		return;
	
	if(elapsed > currentAnimation->speed) {
	currentFrame++;
	if(currentFrame >= currentAnimation->numFrames) {
		if(playingOnce) {
			dispatchEvent(new Event(), Event::COMPLETE_EVENT);
			return;			
		} else {
			currentFrame = 0;
		}
	}
	
	updateSprite();
			
	lastTick = newTick;
		
	}
}

void SceneSprite::updateSprite() {
	Number xOffset = currentAnimation->framesOffsets[currentFrame].x;
	Number yOffset = 1.0f - currentAnimation->framesOffsets[currentFrame].y - spriteUVHeight;
	
	Polygon *imagePolygon = mesh->getPolygon(0);
		
	imagePolygon->getVertex(0)->setTexCoord(xOffset, yOffset);	
	imagePolygon->getVertex(1)->setTexCoord(xOffset+spriteUVWidth, yOffset);
	imagePolygon->getVertex(2)->setTexCoord(xOffset+spriteUVWidth, yOffset+spriteUVHeight);
	imagePolygon->getVertex(3)->setTexCoord(xOffset, yOffset+spriteUVHeight);	
		
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;

}