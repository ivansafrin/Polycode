
#include "PolycodeView.h"
#include "PolyWinCore.h"
#include "PolyCoreServices.h"
#include "PolyCoreInput.h"
#include "PolyRenderer.h"

using namespace Polycode;

Win32Core *core = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;		
	int nWidth, nHeight;

	if(!core)
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_SIZE:
		nWidth = LOWORD(lParam); 
		nHeight = HIWORD(lParam);
		if(core)
			core->getServices()->getRenderer()->Resize(nWidth, nHeight);
	break;

	case WM_MOUSEMOVE:
		if(core)
			core->handleMouseMove(lParam,wParam);
	break;

	case WM_MOUSEWHEEL:
		if(core)
			core->handleMouseWheel(lParam,wParam);
	break;

	case WM_LBUTTONDOWN:
		if(core)
			core->handleMouseDown(CoreInput::MOUSE_BUTTON1, lParam,wParam);
	break;
	case WM_LBUTTONUP:
		if(core)
			core->handleMouseUp(CoreInput::MOUSE_BUTTON1, lParam,wParam);
	break;

	case WM_RBUTTONDOWN:
		if(core)
			core->handleMouseDown(CoreInput::MOUSE_BUTTON2, lParam,wParam);
	break;
	case WM_RBUTTONUP:
		if(core)
			core->handleMouseUp(CoreInput::MOUSE_BUTTON2, lParam,wParam);
	break;

	case WM_MBUTTONDOWN:
		if(core)
			core->handleMouseDown(CoreInput::MOUSE_BUTTON3, lParam,wParam);
	break;
	case WM_MBUTTONUP:
		if(core)
			core->handleMouseUp(CoreInput::MOUSE_BUTTON3, lParam,wParam);
	break;
	case WM_KEYDOWN:
		if(core) {
				wchar_t unicodeChar = 0;
				MSG m;
				m.hwnd = hWnd;
				m.message = message;
				m.wParam = wParam;
				m.lParam = lParam;
				m.time = 0;
				if ( PeekMessage(&m, hWnd, 0, WM_USER, PM_NOREMOVE) && (m.message == WM_CHAR) ) {
					GetMessage(&m, hWnd, 0, WM_USER);
			    		unicodeChar = (wchar_t)m.wParam;
				}

			core->handleKeyDown(lParam,wParam, unicodeChar);
		}
	break;
	case WM_KEYUP:
		if(core)
			core->handleKeyUp(lParam,wParam);
	break;
	case WM_CLOSE:
		if(core)
			core->Shutdown();
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


PolycodeView::PolycodeView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle) : PolycodeViewBase() {

WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"POLYCODEAPPLICATION";
	wcex.hIconSm		= LoadIcon(hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

  hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_OVERLAPPED|WS_SYSMENU,
      0, 0, 640, 480, NULL, NULL, hInstance, NULL);

  windowData = (void*)&hwnd;

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

}

PolycodeView::~PolycodeView() {

}