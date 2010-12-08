/*
 *  PolyiPhoneCore.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 2/1/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyiPhoneCore.h"

using namespace Polycode;

long getThreadID() {
	return (long)pthread_self();
}

IPhoneCore::IPhoneCore(int frameRate) : Core(480, 320, true, 0, frameRate) {
	
}

IPhoneCore::~IPhoneCore() {
	
}

void IPhoneCore::enableMouse(bool newval) {
	
}

unsigned int IPhoneCore::getTicks() {
	return 0;
}

bool IPhoneCore::Update() {
	return running;
}

void IPhoneCore::setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel) {
	
}

void *PosixThreadFunc(void *data) {
	Threaded *target = static_cast<Threaded*>(data);
	target->runThread();
	return NULL;
}

void IPhoneCore::createThread(Threaded *target) {
	pthread_t thread;
	pthread_create( &thread, NULL, PosixThreadFunc, (void*)target);
}

void IPhoneCore::lockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_lock(&m->pMutex);	
}

void IPhoneCore::unlockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_unlock(&m->pMutex);
}

CoreMutex *IPhoneCore::createMutex() {
	PosixMutex *mutex = new PosixMutex();	
	pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;
}

void IPhoneCore::checkEvents() {
	
}

vector<Rectangle> IPhoneCore::getVideoModes() {
	vector<Rectangle> modes;
	
	return modes;
}
