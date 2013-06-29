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
