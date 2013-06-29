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
#include "PolyGlobals.h"
#include "PolyScreenShape.h"
#include <vector>

namespace Polycode {

class _PolyExport SpriteAnimation {
	public:
		Number speed;
		String name;
		String frames;
		int numFrames;

		int numFramesX;
		int numFramesY;
		Number spriteUVWidth;
		Number spriteUVHeight;

		void setOffsetsFromFrameString(const String& frames);

		std::vector<Vector2> framesOffsets;
};

/**
* Animated 2D image sprite. This screen entity can load spritesheet images and play back animations.
*/
class _PolyExport ScreenSprite : public ScreenShape 
{
	public:

		/**
		* Create a sprite from a sprite file format
		* @param fileName Sprite file to load
		*/
		ScreenSprite(const String& fileName);

		/**
		* Create a sprite from a spritesheet image of specified size.
		* @param fileName Image file to load spritesheet from.
		* @param spriteWidth Pixel width of each sprite cell.
		* @param spriteWidth Pixel height of each sprite cell.
		*/
		ScreenSprite(const String& fileName, Number spriteWidth, Number spriteHeight);

		/**
		* Create a sprite from a spritesheet image of specified size.
		* @param fileName Image file to load spritesheet from.
		* @param spriteWidth Pixel width of each sprite cell.
		* @param spriteWidth Pixel height of each sprite cell.
		*/
		static ScreenSprite* ScreenSpriteFromImageFile(const String& fileName, Number spriteWidth, Number spriteHeight);

		virtual ~ScreenSprite();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

		/**
		* Adds a new animation to the sprite. Animations are added by specifying a list of frame indexes and then can be played back by the specified name.
		* @param name Name of the new animation.
		* @param frames A comma separated list of frames indexes to include in the animation.
		* @speed Speed at which to play back the animation.
		* @return Returns newly added animation
		*/
		SpriteAnimation *addAnimation(const String& name, const String& frames, Number speed);

		/**
		* Shows a specific frame of the current animation.
		* @param frameIndex Frame index of the frame to show.
		*/
		void showFrame(unsigned int frameIndex);

		/**
		* Play back a previously created animation by name.
		* @param name Name of the animation to play.
		* @param startFrame Starting frame for playback.
		* @param once If true, only plays once, otherwise loops.
		*/
		void playAnimation(const String& name, int startFrame, bool once);
		void Update();

		void setSpriteSize(const Number spriteWidth, const Number spriteHeight);

		Vector2 getSpriteSize();

		String getFileName() const;

		void recalculateSpriteDimensions();

		bool loadFromFile(const String& fileName);

		/**
		* Pauses or unpauses the current sprite animation.
		* @param val If true, pauses the current animation, if false, resumes playing it.
		*/ 
		void Pause(bool val);

		unsigned int getNumAnimations();
		SpriteAnimation *getAnimationAtIndex(unsigned int index);

		SpriteAnimation *getCurrentAnimation();
		unsigned int getCurrentAnimationFrame();
		bool isCurrentAnimationFinished();

		void updateSprite();

	protected:

		String fileName;

		bool paused;

		Number spriteWidth;
		Number spriteHeight;

		bool playingOnce;
		Number lastTick;

		Number spriteUVWidth;
		Number spriteUVHeight;
		int currentFrame;
		SpriteAnimation *currentAnimation;

		std::vector<SpriteAnimation*> animations;
};

}
