/*
 *  PolyScreenSprite.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/13/09.
 *  Copyright 2009 Ivan Safrin. All rights reserved.
 *
 */



#include "PolyScreenSprite.h"

using namespace Polycode;

ScreenSprite::ScreenSprite(String fileName, Number spriteWidth, Number spriteHeight) : ScreenShape(ScreenShape::SHAPE_RECT, spriteWidth, spriteHeight) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;	
	loadTexture(fileName);
		
	spriteUVWidth = 1.0f / ((Number) texture->getWidth() / spriteWidth);
	spriteUVHeight = 1.0f / ((Number) texture->getHeight() / spriteHeight);
	
	currentFrame = 0;
	currentAnimation = NULL;
}

ScreenSprite::~ScreenSprite() {
	
}

void ScreenSprite::addAnimation(String name, String frames, Number speed) {
	SpriteAnimation *newAnimation = new SpriteAnimation();
	
	vector<String> frameNumbers = frames.split(",");
	
	int numFramesX = texture->getWidth() / spriteWidth;
	int numFramesY = texture->getHeight() / spriteHeight;
	
	int frameNumber;
	int frameX;
	int frameY;
	
	for(int i=0; i < frameNumbers.size(); i++) {
		frameNumber = atoi(frameNumbers[i].c_str());
		frameX = frameNumber % numFramesX;
		frameY = frameNumber/numFramesX;
		newAnimation->framesOffsets.push_back(Vector2(spriteUVWidth * frameX, spriteUVHeight * frameY));		
	}
	
	newAnimation->speed = speed;
	newAnimation->name = name;
	newAnimation->numFrames = frameNumbers.size();
	animations.push_back(newAnimation);
}

void ScreenSprite::playAnimation(String name, int startFrame, bool once) {
	for(int i=0; i < animations.size(); i++) {
		if(animations[i]->name == name) {
			currentAnimation = animations[i];
			currentFrame = 0;			
			if(currentFrame < currentAnimation->numFrames)
				currentFrame = startFrame;
			playingOnce = once;
			lastTick = 0;
		}
	}
}

void ScreenSprite::Update() {
	if(!currentAnimation)
		return;
	
	Number newTick = CoreServices::getInstance()->getCore()->getTicksFloat();
	
	Number elapsed = newTick - lastTick;
	
	if(elapsed > currentAnimation->speed) {
	currentFrame++;
	if(currentFrame >= currentAnimation->numFrames) {
		if(playingOnce)
			return;
		else
			currentFrame = 0;
	}
	
	Number xOffset = currentAnimation->framesOffsets[currentFrame].x;
	Number yOffset = 1.0f - currentAnimation->framesOffsets[currentFrame].y - spriteUVHeight;
	
	Polygon *imagePolygon = mesh->getPolygon(0);
		
	imagePolygon->getVertex(0)->setTexCoord(xOffset, yOffset+spriteUVHeight);	
	imagePolygon->getVertex(1)->setTexCoord(xOffset+spriteUVWidth, yOffset+spriteUVHeight);
	imagePolygon->getVertex(2)->setTexCoord(xOffset+spriteUVWidth, yOffset);
	imagePolygon->getVertex(3)->setTexCoord(xOffset, yOffset);	
		
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
		
	lastTick = newTick;
		
	}
}
