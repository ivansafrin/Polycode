/*
 *  PolySoundManager.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 10/12/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */


#include "PolySoundManager.h"

using namespace Polycode;

SoundManager::SoundManager() {
	initAL();
}

void SoundManager::initAL() {
	alGetError();
	if(alcGetCurrentContext() == NULL) {
		Logger::log("AL already initialized\n");
	}
	
	device = alcOpenDevice(NULL);
	if(device == NULL) {
		Logger::log("InitializeAL: Cannot open preferred device\n");
		return;
	}
	
	if (alcGetError(device) != ALC_NO_ERROR) {
		alcCloseDevice(device);
	//	PCCE_THROW("InitializeAL: Could not open device (alc error)");
	}
	
	context = alcCreateContext(device, NULL);
	if (context == NULL) {
		alcCloseDevice(device);
	//	PCCE_THROW("InitializeAL: Could not create context");
	}
	if (alcGetError(device) != ALC_NO_ERROR) {
		alcDestroyContext(context);
		alcCloseDevice(device);
	//	PCCE_THROW("InitializeAL: Could not open device (alc error)");
	}
	
	if (alcMakeContextCurrent(context) != ALC_TRUE) {
		alcDestroyContext(context);
		alcCloseDevice(device);
	//	PCCE_THROW("InitializeAL: Could not make context current");
	}
	if (alcGetError(device) != ALC_NO_ERROR) {
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	//	PCCE_THROW("InitializeAL: Could not make context current (alc error)");
	}
	
	alGetError();
	
	ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };	
	ALfloat listenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	if (alGetError() != AL_NO_ERROR) {
//		ShutdownAL();
//		PCCE_THROW("InitializeAL: Could not set listener position");
	}
	Logger::log("OpenAL initialized...\n");
}

SoundManager::~SoundManager() {
	alcSuspendContext(context);
	alcDestroyContext(context);
	if (device != NULL) {
		alcCloseDevice(device);
	}
}