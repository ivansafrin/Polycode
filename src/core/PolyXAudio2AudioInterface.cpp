
/*
 Copyright (C) 2015 by Ivan Safrin
 
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

#include "polycode/core/PolyXAudio2AudioInterface.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCore.h"

using namespace Polycode;

XAudio2Stream::XAudio2Stream() {

	mixer = NULL;
	pXAudio2 = NULL;
	pMasterVoice = NULL;


}

HRESULT XAudio2Stream::initXAudio2() {

	hBufferEndEvent = CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR))) {
		Logger::log("Error creating XAudio2 instance\n");
		return hr;
	}

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice))) {
		Logger::log("Error creating XAudio2 voice\n");
		return hr;
	}

	WAVEFORMATEX wfx;
	wfx.cbSize = 0;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = POLY_NUM_CHANNELS;
	wfx.wBitsPerSample = 16;
	wfx.nSamplesPerSec = POLY_AUDIO_FREQ;
	wfx.nBlockAlign = POLY_NUM_CHANNELS * 2;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, &wfx, 0, 1.0f, this))) {
		Logger::log("Error creating XAudio2 sound source\n");
		return hr;
	}

	pSourceVoice->Start(0, 0);

	OVERLAPPED ovlCurrentRequest = { 0 };
	ovlCurrentRequest.hEvent = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE);
	
}

void XAudio2Stream::runThread() {

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);


	HRESULT hr = initXAudio2();
	if (FAILED(hr)) {
		Logger::log("ERROR INITIALIZING XAUDIO2!\n");
	}

	while (threadRunning) {

		XAUDIO2_VOICE_STATE state;
		for (;; )
		{
			pSourceVoice->GetState(&state);
			if (state.BuffersQueued == 0) {
				break;
			}
			WaitForSingleObject(hBufferEndEvent, INFINITE);
		}

		XAUDIO2_BUFFER buf = { 0 };

		buf.AudioBytes = POLY_FRAMES_PER_BUFFER*POLY_NUM_CHANNELS*2;

		//memset(buffer,0, POLY_FRAMES_PER_BUFFER * sizeof(int16_t));
		if (mixer) {
			Services()->getCore()->lockMutex(mixer->mixerMutex);
			mixer->mixIntoBuffer(buffer, POLY_FRAMES_PER_BUFFER);
			Services()->getCore()->unlockMutex(mixer->mixerMutex);
		}

		buf.pAudioData = (BYTE*) buffer;
		pSourceVoice->SubmitSourceBuffer(&buf);

	}

	pMasterVoice->DestroyVoice();
	SAFE_RELEASE(pXAudio2);

	CoUninitialize();


}

void XAudio2Stream::setMixer(AudioMixer *mixer) {
	this->mixer = mixer;
}

void XAudio2AudioInterface::setMixer(AudioMixer *mixer) {
	xAudioStream->setMixer(mixer);
	AudioInterface::setMixer(mixer);
}

XAudio2AudioInterface::XAudio2AudioInterface() {
	xAudioStream = new XAudio2Stream();
	Services()->getCore()->createThread(xAudioStream);
}

XAudio2AudioInterface::~XAudio2AudioInterface() {
	xAudioStream->killThread();
}