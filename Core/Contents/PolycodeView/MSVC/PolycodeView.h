#pragma once

#include <windows.h>
#include "PolyCore.h"

using namespace Polycode;

namespace Polycode {

class _PolyExport PolycodeView : public PolycodeViewBase {
public:
	PolycodeView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle);
	~PolycodeView();

	HWND hwnd;
};

}