#pragma once

#include <windows.h>
#include <Polycode.h>
#include <PolyWinCore.h>

using namespace Polycode;

namespace Polycode {

class _PolyExport PolycodeView : public PolycodeViewBase {
public:
	PolycodeView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle);
	~PolycodeView();

	HWND hwnd;
};

}