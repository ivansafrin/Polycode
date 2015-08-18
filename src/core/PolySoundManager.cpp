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

using namespace Polycode;


SoundManager::SoundManager() {
    audioInterface = NULL;
    testVal = 0.0;
}

void SoundManager::setGlobalVolume(Number globalVolume) {
    // NOAL_TODO
	//alListenerf(AL_GAIN, globalVolume);
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

void SoundManager::setAudioInterface(AudioInterface *audioInterface) {
    this->audioInterface = audioInterface;
}


AudioInterface::AudioInterface() {
    readOffset = 0;
    writeOffset = 0;
    memset(bufferData, 0, sizeof(float) * POLY_FRAMES_PER_BUFFER*POLY_CIRCULAR_BUFFER_SIZE);
}

void AudioInterface::addToBuffer(float *data, unsigned int count) {
    for(int i=0; i < count; i++) {
        for(int b=0; b < POLY_NUM_CHANNELS; b++) {
            bufferData[b][writeOffset] = data[(i*POLY_NUM_CHANNELS)+b];
        }
        writeOffset++;
        if(writeOffset >= POLY_FRAMES_PER_BUFFER * POLY_CIRCULAR_BUFFER_SIZE) {
            writeOffset = 0;
        }
        
    }
}

void SoundManager::Update() {
    Number elapsed = Services()->getCore()->getElapsed();
    
    if(audioInterface) {
        unsigned int numSamples = ((Number)POLY_AUDIO_FREQ)*elapsed;
        
        for(int i=0; i < numSamples; i++) {
            float sinVal = sin(testVal);
            float data[2] = {sinVal, sinVal};
            audioInterface->addToBuffer(data, 1);
            testVal += 1.0/44100.0 * 261.62 * 2.0 * PI; // middle C for testing
        }
    }
    
    // if recording sound, save samples
    /*
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
     */
        // NOAL_TODO
}

SoundManager::~SoundManager() {
    delete audioInterface;
}
