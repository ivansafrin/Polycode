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
#include "PolyScreenEntity.h"

namespace Polycode {

class Sound;

/**
* Creates a positional 2D sound listener. There can be only one listener active at any one time.
*/
class _PolyExport ScreenSoundListener : public ScreenEntity {
	public:
		ScreenSoundListener();
		virtual ~ScreenSoundListener();
		void Update();
};


/**
* Creates a positional 2D sound.
*/
class _PolyExport ScreenSound : public ScreenEntity {
	public:
		ScreenSound(const String& fileName, Number referenceDistance, Number maxDistance);
		virtual ~ScreenSound();

		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);

		void Update();

		/**
		* Returns the sound object associated with this positional sound.
		*/
		Sound *getSound() const;

	protected:

		Sound *sound;
};

}
