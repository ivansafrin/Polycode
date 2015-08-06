
#include "polycode/core/PolyUWPCore.h"


UWPCore::UWPCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) 
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

}

UWPCore::~UWPCore() {

}

void UWPCore::Render() {

}

bool UWPCore::systemUpdate() {
	return true;
}

void UWPCore::setCursor(int cursorType) {

}

void UWPCore::lockMutex(CoreMutex *mutex) {

}

void UWPCore::unlockMutex(CoreMutex *mutex) {

}

CoreMutex *UWPCore::createMutex() {
	return NULL;
}

void UWPCore::copyStringToClipboard(const String& str) {

}

String UWPCore::getClipboardString() {
	return "";
}

void UWPCore::createFolder(const String& folderPath) {

}

void UWPCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void UWPCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void UWPCore::removeDiskItem(const String& itemPath) {

}

String UWPCore::openFolderPicker() {
	return "";
}

std::vector<String> UWPCore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String UWPCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void UWPCore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {

}

void UWPCore::flushRenderContext() {

}

void UWPCore::resizeTo(int xRes, int yRes) {

}

void UWPCore::openURL(String url) {

}

unsigned int UWPCore::getTicks() {
	return 0;
}

String UWPCore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}