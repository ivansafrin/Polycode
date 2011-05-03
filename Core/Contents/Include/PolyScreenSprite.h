/*
 *  PolyScreenSprite.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/13/09.
 *  Copyright 2009 Ivan Safrin. All rights reserved.
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
		Number speed;
		String name;
		int numFrames;
	
		vector<Vector2> framesOffsets;
};

class ScreenSprite : public ScreenShape 
{
	public:
		ScreenSprite(String fileName, Number spriteWidth, Number spriteHeight);
		~ScreenSprite();
		
		void addAnimation(String name, String frames, Number speed);
		void playAnimation(String name, int startFrame, bool once);
		void Update();
		
	private:
	
		Number spriteWidth;
		Number spriteHeight;
			
		bool playingOnce;
		Number lastTick;
		
		Number spriteUVWidth;
		Number spriteUVHeight;
		int currentFrame;
		SpriteAnimation *currentAnimation;
		
		vector<SpriteAnimation*> animations;
};
	
}
