/*
	Copyright (C) 2016 by Sang Hak Chun

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

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolySoundManager.h"

#include <SDL/SDL_audio.h>
#include <stdlib.h>

#define SDL_AUDIO_NUM_OF_SAMPLES 8192

namespace Polycode {

	class SDLAudioInterface : public Polycode::AudioInterface {
		public:
			SDLAudioInterface();
			~SDLAudioInterface();

			static void sdlCallback(void* userData, Uint8* _stream, int _length);
		private:
			SDL_AudioSpec *desired;
			SDL_AudioSpec *obtained;

			int16_t* buffer;
	};

}