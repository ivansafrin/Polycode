
#pragma once

#include "PolyCore.h"
#include <vector>

using namespace Polycode;


#define POLYCODE_CORE UWPCore

class PolycodeView {
	public:
};

class UWPCore : public Core {
	public:
	
	UWPCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex = -1, bool retinaSupport = false);
	~UWPCore();

	void Render();
	bool systemUpdate();
	void setCursor(int cursorType);
	void lockMutex(CoreMutex *mutex);
	void unlockMutex(CoreMutex *mutex);
	CoreMutex *createMutex();
	void copyStringToClipboard(const String& str);
	String getClipboardString();
	void createFolder(const String& folderPath);
	void copyDiskItem(const String& itemPath, const String& destItemPath);
	void moveDiskItem(const String& itemPath, const String& destItemPath);
	void removeDiskItem(const String& itemPath);
	String openFolderPicker();
	std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
	String saveFilePicker(std::vector<CoreFileExtension> extensions);
	void handleVideoModeChange(VideoModeChangeInfo *modeInfo);
	void flushRenderContext();
	void resizeTo(int xRes, int yRes);
	void openURL(String url);
	unsigned int getTicks();
	String executeExternalCommand(String command, String args, String inDirectory);

};