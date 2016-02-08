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


#include "polycode/core/PolyIOSCore.h"

using namespace Polycode;


IOSCore::IOSCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport)
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

}

IOSCore::~IOSCore() {

}

void IOSCore::Render() {

}


void IOSCore::checkEvents() {


}

bool IOSCore::systemUpdate() {
	if (!running) {
		return false;
	}
	doSleep();
	updateCore();

	checkEvents();
	return running;
}

void IOSCore::setCursor(int cursorType) {

}

void launchThread(Threaded *target) {
	target->runThread();
	target->scheduledForRemoval = true;
}

void IOSCore::createThread(Threaded * target) {

	 
}

CoreMutex *IOSCore::createMutex() {
    return NULL;
}

void IOSCore::copyStringToClipboard(const String& str) {

}

String IOSCore::getClipboardString() {
	return "";
}

void IOSCore::createFolder(const String& folderPath) {

}

void IOSCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void IOSCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void IOSCore::removeDiskItem(const String& itemPath) {

}

String IOSCore::openFolderPicker() {
	return "";
}

std::vector<String> IOSCore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String IOSCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void IOSCore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {

}

void IOSCore::flushRenderContext() {

}

void IOSCore::openURL(String url) {

}

unsigned int IOSCore::getTicks() {

	return 0;
}

String IOSCore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}




bool IOSCore::systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {

	return true; 
}


void Core::getScreenInfo(int *width, int *height, int *hz) {

}

void IOSCore::setDeviceSize(Number x, Number y) {

}

Number IOSCore::getBackingXRes() {
	return 1.0;
}

Number IOSCore::getBackingYRes() {
	return 1.0;
}