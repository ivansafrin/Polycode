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

#include "PolySoundManager.h"
#include "PolyLogger.h"

using namespace Polycode;

SoundManager::SoundManager() {
	initAL();
}

void SoundManager::initAL() {
    captureDevice = NULL;
    
	device = alcOpenDevice(0);
	if(device == 0) {
		Logger::log("InitializeAL: Cannot open preferred device\n");
		return;
	}

	ALCenum error = alcGetError(device);
	if (error != ALC_NO_ERROR) {
		alcCloseDevice(device);
		Logger::log("InitializeAL: Could not open device (%d).", error);
		return;
	}
	
	context = alcCreateContext(device, 0);
	if (context == 0) {
		alcCloseDevice(device);
		Logger::log("InitializeAL: Could not create context");
		return;
	}

	error = alcGetError(device);
	if (error != ALC_NO_ERROR) {
		alcDestroyContext(context);
		alcCloseDevice(device);
		Logger::log("InitializeAL: Could not open device (%d).", error);
		return;
	}
	
	if (alcMakeContextCurrent(context) != ALC_TRUE) {
		alcDestroyContext(context);
		alcCloseDevice(device);
		Logger::log("InitializeAL: Could not make context current");
		return;
	}
	
	ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };	
	ALfloat listenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
	
	Logger::log("OpenAL initialized...\n");
}

void SoundManager::setGlobalVolume(Number globalVolume) {
	alListenerf(AL_GAIN, globalVolume);
}

void SoundManager::setListenerPosition(Vector3 position) {
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void SoundManager::setListenerOrientation(Vector3 orientation, Vector3 upVector) {
	ALfloat ori[6];
	ori[0] = orientation.x;
	ori[1] = orientation.y;
	ori[2] = orientation.z;
	
	ori[3] = upVector.x;
	ori[4] = upVector.y;
	ori[5] = upVector.z;	
	alListenerfv(AL_ORIENTATION,ori);
}

bool SoundManager::recordSound(unsigned int rate, unsigned int sampleSize) {
    
    if(captureDevice) {
        Logger::log("Error: Audio capture already in progress\n");
        return false;
    }
    
    captureDevice = alcCaptureOpenDevice(NULL, rate, AL_FORMAT_STEREO16, sampleSize);
    if (alGetError() != AL_NO_ERROR) {
        captureDevice = NULL;
        return false;
    }
    recordingBufferRate = rate;
    
    recordingBuffer = (ALbyte*) malloc(1);
    recordingBufferSize = 0;
    
    alcCaptureStart(captureDevice);
    return true;
}

Sound *SoundManager::stopRecording(bool generateFloatBuffer) {
    if(!captureDevice) {
        Logger::log("No recording in process\n");
        return NULL;
    }
    alcCaptureStop(captureDevice);
    alcCaptureCloseDevice(captureDevice);
    captureDevice = NULL;
    
    Sound *newSound = new Sound(recordingBufferSize, (const char*)recordingBuffer, 2, recordingBufferRate, 16, generateFloatBuffer);
    
    free(recordingBuffer);
    
    return newSound;
}

void SoundManager::registerStreamingSound(Sound *sound) {
    streamingSounds.push_back(sound);
}

void SoundManager::unregisterStreamingSound(Sound *sound) {
    for(int i=0; i < streamingSounds.size(); i++) {
        if(streamingSounds[i] == sound) {
            streamingSounds.erase(streamingSounds.begin()+i);
            return;
        }
    }
}

void SoundManager::Update() {
    // if recording sound, save samples
    if(captureDevice) {
        ALint samples;
        alcGetIntegerv(captureDevice, ALC_CAPTURE_SAMPLES, (ALCsizei)sizeof(ALint), &samples);
        if(samples) {
            unsigned int newBufferSize = sizeof(ALbyte) * samples * 4;
            recordingBuffer = (ALbyte*) realloc(recordingBuffer, recordingBufferSize + newBufferSize);
        
            alcCaptureSamples(captureDevice, (ALCvoid *)(recordingBuffer+recordingBufferSize), samples);
            recordingBufferSize += newBufferSize;
        }
    }
    
    for(int i=0; i < streamingSounds.size(); i++) {
        streamingSounds[i]->updateStream();
    }
}

SoundManager::~SoundManager() {
	if (context != 0 ) {
		alcSuspendContext(context);
		alcMakeContextCurrent(0);
		alcDestroyContext(context);
	}
	if (device != 0) {
		alcCloseDevice(device);
	}
}
