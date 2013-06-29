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

#include "PolyScreenSprite.h"
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyTexture.h"

using std::vector;
using namespace Polycode;

ScreenSprite* ScreenSprite::ScreenSpriteFromImageFile(const String& fileName, Number spriteWidth, Number spriteHeight) {
	return new ScreenSprite(fileName, spriteWidth, spriteHeight);
}

ScreenSprite::ScreenSprite(const String& fileName) : ScreenShape(ScreenShape::SHAPE_RECT, 1, 1) {

	currentFrame = 0;
	currentAnimation = NULL;
	paused = false;

	loadFromFile(fileName);
}

Entity *ScreenSprite::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenSprite *newSprite = new ScreenSprite(getTexture()->getResourcePath(), spriteWidth, spriteHeight);
	for(int i=0; i < animations.size(); i++) {
		newSprite->addAnimation(animations[i]->name, animations[i]->frames, animations[i]->speed);
	}
	if(currentAnimation) {
		newSprite->playAnimation(currentAnimation->name, currentFrame, playingOnce);
	}
	applyClone(newSprite, deepClone, ignoreEditorOnly);
	return newSprite;
}

void ScreenSprite::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	ScreenShape::applyClone(clone, deepClone, ignoreEditorOnly);

}

bool ScreenSprite::loadFromFile(const String& fileName) {
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
			setShapeSize(frameWidth->NumberVal, frameHeight->NumberVal);
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

unsigned int ScreenSprite::getNumAnimations() {
	return animations.size();
}

SpriteAnimation *ScreenSprite::getAnimationAtIndex(unsigned int index) {
	if(index < animations.size()) {
		return animations[index];
	} else {
		return NULL;
	}
}


ScreenSprite::ScreenSprite(const String& fileName, Number spriteWidth, Number spriteHeight) : ScreenShape(ScreenShape::SHAPE_RECT, spriteWidth, spriteHeight) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	loadTexture(fileName);

	recalculateSpriteDimensions();
	currentFrame = 0;
	currentAnimation = NULL;
	paused = false;
}

ScreenSprite::~ScreenSprite() {

}

void ScreenSprite::recalculateSpriteDimensions() {
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

Vector2 ScreenSprite::getSpriteSize() {
	return Vector2(spriteWidth, spriteHeight);
}

String ScreenSprite::getFileName() const {
	return fileName;
}

void ScreenSprite::setSpriteSize(const Number spriteWidth, const Number spriteHeight) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;

	recalculateSpriteDimensions();
}

SpriteAnimation *ScreenSprite::getCurrentAnimation() {
	return currentAnimation;
}

unsigned int ScreenSprite::getCurrentAnimationFrame() { 
	return currentFrame; 
}

bool ScreenSprite::isCurrentAnimationFinished() {
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

	for(int i=0; i < frameNumbers.size(); i++) {
		frameNumber = atoi(frameNumbers[i].c_str());
		frameX = frameNumber % numFramesX;
		frameY = frameNumber/numFramesX;
		framesOffsets.push_back(Vector2(spriteUVWidth * frameX, spriteUVHeight * frameY));
	}

	this->frames = frames;
	numFrames = frameNumbers.size();

}

SpriteAnimation *ScreenSprite::addAnimation(const String& name, const String& frames, Number speed) {
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

void ScreenSprite::playAnimation(const String& name, int startFrame, bool once) {
	paused = false;
	for(int i=0; i < animations.size(); i++) {
		if(animations[i]->name == name) {
			if(currentAnimation == animations[i] && !playingOnce && !once)
				return;
			currentFrame = 0;
			currentAnimation = animations[i];
			if(startFrame == -1) {
				currentFrame = rand() % currentAnimation->numFrames;
			} else if(startFrame < currentAnimation->numFrames) {
				currentFrame = startFrame;
			}
			playingOnce = once;
			lastTick = 0;
		}
	}
}

void ScreenSprite::Pause(bool val) {
	paused = val;
}

void ScreenSprite::showFrame(unsigned int frameIndex) {
	if(!currentAnimation)
		return;

	if(frameIndex < currentAnimation->numFrames) {
		currentFrame = frameIndex;
		updateSprite();
	}
}

void ScreenSprite::Update() {
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

void ScreenSprite::updateSprite() {
	Number xOffset = currentAnimation->framesOffsets[currentFrame].x;
	Number yOffset = 1.0f - currentAnimation->framesOffsets[currentFrame].y - spriteUVHeight;

	Polygon *imagePolygon = mesh->getPolygon(0);

	imagePolygon->getVertex(0)->setTexCoord(xOffset, yOffset+spriteUVHeight);
	imagePolygon->getVertex(1)->setTexCoord(xOffset+spriteUVWidth, yOffset+spriteUVHeight);
	imagePolygon->getVertex(2)->setTexCoord(xOffset+spriteUVWidth, yOffset);
	imagePolygon->getVertex(3)->setTexCoord(xOffset, yOffset);

	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;

}
