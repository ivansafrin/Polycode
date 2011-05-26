#pragma once

#include <windows.h>
#include <Polycode.h>
#include <PolyWinCore.h>
#include <PolycodePlayer.h>

using namespace Polycode;

namespace Polycode {

class _PolyExport PolycodePlayerView : public PolycodeViewBase, public EventHandler {
public:
	PolycodePlayerView(bool standaloneMode, HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle);
	~PolycodePlayerView();

	void handleEvent(Event *event);

	HWND consoleTextArea;
	HWND hwnd;
};

}