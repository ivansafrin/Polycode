#pragma once

#include <winsock2.h>
#include <windows.h>
#include "PolyCore.h"

using namespace Polycode;

class PolycodeIDEApp;

namespace Polycode {

class _PolyExport PolycodeWinIDEView : public PolycodeViewBase {
public:
	PolycodeWinIDEView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle, bool resizable = false, bool showDebugConsole = false);
	~PolycodeWinIDEView();

	HWND hwnd;
	HACCEL haccel;

};

}