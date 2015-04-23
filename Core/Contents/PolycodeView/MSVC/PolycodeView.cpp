
#include "PolycodeView.h"
#include "PolyWinCore.h"
#include "PolyCoreServices.h"
#include "PolyCoreInput.h"
#include "PolyRenderer.h"
#include <io.h>
#include <fcntl.h>
#include <ios>

using namespace Polycode;

Win32Core *core = NULL;


static void OpenConsole()
{
    int outHandle, errHandle, inHandle;
    FILE *outFile, *errFile, *inFile;
    AllocConsole();
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = 9999;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    outHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    errHandle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);
    inHandle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE),_O_TEXT );

    outFile = _fdopen(outHandle, "w" );
    errFile = _fdopen(errHandle, "w");
    inFile =  _fdopen(inHandle, "r");

    *stdout = *outFile;
    *stderr = *errFile;
    *stdin = *inFile;

    setvbuf( stdout, NULL, _IONBF, 0 );
    setvbuf( stderr, NULL, _IONBF, 0 );
    setvbuf( stdin, NULL, _IONBF, 0 );

    std::ios::sync_with_stdio();

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int nWidth, nHeight;
	bool useDefault = false;

	if(!core)
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_COPYDATA:
	{
		COPYDATASTRUCT *cp = (COPYDATASTRUCT*)lParam;
		wchar_t *stringData = (wchar_t*)cp->lpData;
		core->copyDataString = String(stringData);
		core->hasCopyDataString = true;
	}
	break;
	case WM_SIZE:
		nWidth = LOWORD(lParam); 
		nHeight = HIWORD(lParam);
		if(core) {
			core->handleViewResize(nWidth, nHeight);
		}
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

#ifndef NO_TOUCH_API 
	#ifdef NO_PEN_API
		case WM_TOUCH:
			if(core) {
				if(core->isMultiTouchEnabled()) {
					core->handleTouchEvent(lParam, wParam);
				}
			}
		break;
	#else
		case WM_POINTERUPDATE:
		case WM_POINTERUP:
		case WM_POINTERDOWN:
			if (core)
				core->handlePointerUpdate(lParam, wParam);
		break;
	#endif
#endif
	
	case WM_MBUTTONDOWN:
		if(core)
			core->handleMouseDown(CoreInput::MOUSE_BUTTON3, lParam,wParam);
	break;
	case WM_MBUTTONUP:
		if(core)
			core->handleMouseUp(CoreInput::MOUSE_BUTTON3, lParam,wParam);
	break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
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
	case WM_SYSKEYUP:
		if(core)
			core->handleKeyUp(lParam,wParam);
	break;
	case WM_CLOSE:
		if(core)
			core->Shutdown();
		useDefault = true;
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		useDefault = true;
		break;
	}
	
	if (useDefault)
		return DefWindowProc(hWnd, message, wParam, lParam);
	else
		return 0;
}


PolycodeView::PolycodeView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle, bool resizable, bool showDebugConsole) : PolycodeViewBase() {

	/*
	typedef BOOL(WINAPI *SetProcessDPIAwarePtr)(VOID);
	SetProcessDPIAwarePtr set_process_dpi_aware_func = GetProcAddress(GetModuleHandleA("user32.dll"), "SetProcessDPIAware");
	if (set_process_dpi_aware_func) {
		set_process_dpi_aware_func();
	}
	*/
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

	this->resizable = resizable;

	if(resizable) {
		hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_OVERLAPPEDWINDOW | WS_SYSMENU, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
	} else {
		hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_CAPTION | WS_POPUP | WS_SYSMENU, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
	}

  windowData = (void*)&hwnd;

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   if(showDebugConsole) {
		OpenConsole();
   }

}

PolycodeView::~PolycodeView() {

}