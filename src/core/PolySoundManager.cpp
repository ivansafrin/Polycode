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

#include "polycode/core/PolySoundManager.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyLogger.h"
#include <stdint.h>
#include <limits>

using namespace Polycode;

#ifndef INT16_MAX
	#define INT16_MAX (std::numeric_limits<int16_t>::max())
#endif

SoundManager::SoundManager() {
    audioInterface = NULL;
    testVal = 0.0;
    leftOver = 0.0;
    mixer = new AudioMixer();
    mixer->globalVolume = 1.0;    
}

void SoundManager::setGlobalVolume(Number globalVolume) {
    mixer->globalVolume = globalVolume;
}

void SoundManager::setListenerPosition(Vector3 position) {
    // NOAL_TODO
//	alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void SoundManager::setListenerOrientation(Vector3 orientation, Vector3 upVector) {
    /*
	ALfloat ori[6];
	ori[0] = orientation.x;
	ori[1] = orientation.y;
	ori[2] = orientation.z;
	
	ori[3] = upVector.x;
	ori[4] = upVector.y;
	ori[5] = upVector.z;	
	alListenerfv(AL_ORIENTATION,ori);
     */
    // NOAL_TODO
}

bool SoundManager::recordSound(unsigned int rate, unsigned int sampleSize) {
    // NOAL_TODO
    /*
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
     */
    return false;
}

Sound *SoundManager::stopRecording(bool generateFloatBuffer) {
    /*
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
     */
        // NOAL_TODO
    return NULL;
}

void SoundManager::registerSound(Sound *sound) {
	Services()->getCore()->lockMutex(mixer->mixerMutex);
    mixer->sounds.push_back(sound);
	Services()->getCore()->unlockMutex(mixer->mixerMutex);
}

void SoundManager::unregisterSound(Sound *sound) {
	Services()->getCore()->lockMutex(mixer->mixerMutex);
    for(int i=0; i < mixer->sounds.size(); i++) {
        if(mixer->sounds[i] == sound) {
            mixer->sounds.erase(mixer->sounds.begin()+i);
			Services()->getCore()->unlockMutex(mixer->mixerMutex);
            return;
        }
    }
	Services()->getCore()->unlockMutex(mixer->mixerMutex);
}

void SoundManager::setAudioInterface(AudioInterface *audioInterface) {
    this->audioInterface = audioInterface;
	if (!mixer->mixerMutex) {
		mixer->mixerMutex = Services()->getCore()->createMutex();
	}
    audioInterface->setMixer(mixer);
}


AudioInterface::AudioInterface() {
}

void AudioInterface::setMixer(AudioMixer *mixer) {
    this->mixer = mixer;
}

AudioMixer *AudioInterface::getMixer() {
    return mixer;
}

inline Number mixSamples(Number A, Number B) {
    
    if (A < 0 && B < 0 ) {
        return  (A + B) - (A * B)/-1.0;
    } else if (A > 0 && B > 0 ) {
        return (A + B) - (A * B)/1.0;
    } else {
        return A + B;
    }
}

AudioMixer::AudioMixer() {
	mixerMutex = NULL;
}

AudioMixer::~AudioMixer() {
	delete mixerMutex;
}

void AudioMixer::mixIntoBuffer(int16_t *buffer, unsigned int numSamples) {
	mixerMutex->lock();

	if (sounds.size() == 0) {
        memset(buffer, 0, sizeof(int16_t) * numSamples * POLY_NUM_CHANNELS);
		mixerMutex->unlock();
		return;
	}

    for(int i=0; i < sounds.size(); i++) {
        sounds[i]->updateStream(numSamples);
    }
    
    int16_t *bufferPtr = buffer;
    for(int i=0; i < numSamples; i++) {
        
        Number mixResults[POLY_NUM_CHANNELS];
        memset(mixResults, 0, sizeof(Number) * POLY_NUM_CHANNELS);
        
        int mixNum = 0;
        for(int i=0; i < sounds.size(); i++) {
            if(sounds[i]->isPlaying()) {

                for(int c=0; c < POLY_NUM_CHANNELS; c++) {
                    Number sampleA = mixResults[c];
                    Number sampleB = sounds[i]->getSampleAsNumber(sounds[i]->getOffset(), c);
                    
                    if(mixNum == 0) {
                        mixResults[c] = sampleB;
                    } else {
                        mixResults[c] = mixSamples(sampleA, sampleB);
                    }
                }
                sounds[i]->setOffset(sounds[i]->getOffset()+1);
                mixNum++;
            }
        }
        
        for(int c=0; c < POLY_NUM_CHANNELS; c++) {
            *bufferPtr = (int16_t)(((Number)INT16_MAX) * (mixResults[c] * globalVolume));
            bufferPtr++;
        }
    }
	 mixerMutex->unlock();
}

void SoundManager::Update() {
}

SoundManager::~SoundManager() {
    delete audioInterface;
}
