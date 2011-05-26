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

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenShape.h"
#include <vector>
#include <string>

namespace Polycode {

class _PolyExport SpriteAnimation {
	public:
		Number speed;
		String name;
		int numFrames;
	
		vector<Vector2> framesOffsets;
};

/**
* Animated 2D image sprite. This screen entity can load spritesheet images and play back animations.
*/
class _PolyExport ScreenSprite : public ScreenShape 
{
	public:
		/**
		* Create a sprite from a spritesheet image of specified size.
		* @param fileName Image file to load spritesheet from.
		* @param spriteWidth Pixel width of each sprite cell.
		* @param spriteWidth Pixel height of each sprite cell.		
		*/
		ScreenSprite(String fileName, Number spriteWidth, Number spriteHeight);
		~ScreenSprite();
		
		/**
		* Adds a new animation to the sprite. Animations are added by specifying a list of frame indexes and then can be played back by the specified name.
		* @param name Name of the new animation.
		* @param frames A comma separated list of frames indexes to include in the animation.
		* @speed Speed at which to play back the animation.
		*/
		void addAnimation(String name, String frames, Number speed);
		
		/**
		* Play back a previously created animation by name.
		* @param name Name of the animation to play.
		* @param startFrame Starting frame for playback.
		* @param once If true, only plays once, otherwise loops.
		*/
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
