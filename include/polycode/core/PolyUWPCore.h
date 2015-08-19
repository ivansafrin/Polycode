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

#pragma once

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyCore.h"
#include <ppltasks.h>

#include <Windows.Foundation.h>
#include <Windows.Storage.h>
#include <wrl\wrappers\corewrappers.h>
#include <wrl\client.h>
#include <wrl.h>


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <angle_windowsstore.h>

using namespace concurrency;

#define POLYCODE_CORE UWPCore

namespace Polycode {

	class PolycodeView {
	public:

		EGLNativeWindowType eglWindow;
		IUnknown *window;
		EGLDisplay mEglDisplay;
		EGLContext mEglContext;
		EGLSurface mEglSurface;
	};

	class UWPCoreMutex : public CoreMutex {
	public:
		std::mutex mutex;
	};

	class OpenGLGraphicsInterface;

	class _PolyExport UWPCore : public Core {
	public:

		UWPCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex = -1, bool retinaSupport = false);
		~UWPCore();

		void Render();
		bool systemUpdate();
		void setCursor(int cursorType);
		void createThread(Threaded *target);
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
		void openURL(String url);
		unsigned int getTicks();
		String executeExternalCommand(String command, String args, String inDirectory);
		bool systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector);



	private:

		OpenGLGraphicsInterface *graphicsInterface;
		IUnknown *m_Window;

		EGLNativeWindowType m_eglWindow;

		EGLDisplay mEglDisplay;
		EGLContext mEglContext;
		EGLSurface mEglSurface;

	};
}