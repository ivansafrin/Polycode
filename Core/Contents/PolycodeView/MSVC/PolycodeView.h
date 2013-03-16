#pragma once

#include <winsock2.h>
#include <windows.h>
#include "PolyCore.h"

using namespace Polycode;

namespace Polycode {

class _PolyExport PolycodeView : public PolycodeViewBase {
public:
	PolycodeView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle, bool resizable=false, bool showDebugConsole = false);
	~PolycodeView();

	HWND hwnd;
};

}