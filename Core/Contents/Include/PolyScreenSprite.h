/*
 *  PolyScreenSprite.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenShape.h"
#include <vector>
#include <string>

namespace Polycode {

class SpriteAnimation {
	public:
		float speed;
		String name;
		int numFrames;
	
		vector<Vector2> framesOffsets;
};

class ScreenSprite : public ScreenShape 
{
	public:
		ScreenSprite(String fileName, float spriteWidth, float spriteHeight);
		~ScreenSprite();
		
		void addAnimation(String name, String frames, float speed);
		void playAnimation(String name, int startFrame, bool once);
		void Update();
		
	private:
	
		float spriteWidth;
		float spriteHeight;
			
		bool playingOnce;
		float lastTick;
		
		float spriteUVWidth;
		float spriteUVHeight;
		int currentFrame;
		SpriteAnimation *currentAnimation;
		
		vector<SpriteAnimation*> animations;
};
	
}
