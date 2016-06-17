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

#include "polycode/core/PolySDLAudioInterface.h"
#include "polycode/core/PolyLogger.h"

using namespace Polycode;

SDLAudioInterface::SDLAudioInterface() {
	desired = (SDL_AudioSpec*) malloc(sizeof(SDL_AudioSpec));
	obtained = (SDL_AudioSpec*) malloc(sizeof(SDL_AudioSpec));

	desired->freq = POLY_AUDIO_FREQ;
	desired->format = AUDIO_S16SYS;
	desired->channels = POLY_NUM_CHANNELS;
	desired->samples = SDL_AUDIO_NUM_OF_SAMPLES;
	desired->callback = SDLAudioInterface::sdlCallback;
	desired->userdata = this;

	int error = SDL_OpenAudio(desired, obtained);

	if (error < 0) {
		Logger::log("Error opening SDL_audio stream\n");
	}

	free(desired);

	buffer = (int16_t*) malloc(sizeof(int16_t) * POLY_FRAMES_PER_BUFFER * POLY_NUM_CHANNELS);

	SDL_PauseAudio(0); // start playing
}

SDLAudioInterface::~SDLAudioInterface() {
	SDL_CloseAudio();
	free(buffer);
}

void SDLAudioInterface::sdlCallback(void *userData, Uint8 *_stream, int _length) {
	if ( _length == 0 )
		return;

	memset(_stream, 0, _length);
	SDLAudioInterface *audioInterface = (SDLAudioInterface*) userData;
	if(_stream && audioInterface->getMixer()) {
		audioInterface->getMixer()->mixIntoBuffer((int16_t*)_stream, (_length / (sizeof(int16_t) * POLY_NUM_CHANNELS)));
	}
};