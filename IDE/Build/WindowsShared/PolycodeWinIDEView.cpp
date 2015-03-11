
#include "PolycodeWinIDEView.h"
#include "PolyWinCore.h"
#include "PolyCoreServices.h"
#include "PolyCoreInput.h"
#include "PolyRenderer.h"
#include <io.h>
#include <fcntl.h>
#include <ios>
#include "resource.h"
#include "PolycodeIDEApp.h"

using namespace Polycode;

Win32Core *core = NULL;
PolycodeIDEApp *globalApp = NULL;

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
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_FILE_NEW_FILE:
					globalApp->newFile();
				break;
				case ID_FILE_NEW_PROJECT:
					globalApp->newProject();
				break;
				case ID_FILE_NEW_FOLDER:
					globalApp->newGroup();
				break;
				case ID_FILE_OPEN_PROJECT:
					globalApp->openProject();
					break;
				case ID_FILE_CLOSE_FILE:
					globalApp->closeFile();
					break;
				case ID_FILE_CLOSE_PROJECT:
					globalApp->closeProject();
					break;
				case ID_FILE_REMOVE_FILE:
					globalApp->removeFile();
					break;
				case ID_FILE_REFRESH_PROJECT:
					globalApp->refreshProject();
					break;
				case ID_FILE_SAVE_FILE:
					globalApp->saveFile();
					break;
				case ID_FILE_BROWSE_EXAMPLES:
					globalApp->browseExamples();
					break;
				case ID_FILE_EXIT:
				{
					 globalApp->saveConfigFile();
					 bool retVal = globalApp->quitApp();
					 if (retVal) {
						 core->Shutdown();
						 useDefault = true;
					 }
				}
				break;

				case ID_EDIT_UNDO:
					core->dispatchEvent(new Event(), Core::EVENT_UNDO);
					break;
				case ID_EDIT_REDO:
					core->dispatchEvent(new Event(), Core::EVENT_REDO);
					break;
				case ID_EDIT_CUT:
					core->dispatchEvent(new Event(), Core::EVENT_CUT);
					break;
				case ID_EDIT_COPY:
					core->dispatchEvent(new Event(), Core::EVENT_COPY);
					break;
				case ID_EDIT_PASTE:
					core->dispatchEvent(new Event(), Core::EVENT_PASTE);
					break;
				case ID_EDIT_SELECT_ALL:
					core->dispatchEvent(new Event(), Core::EVENT_SELECT_ALL);
					break;
				case ID_EDIT_FIND:
					globalApp->findText();
					break;
				case ID_EDIT_PREFERENCES:
					globalApp->showSettings();
				break;


				case ID_VIEW_CREATE_TAB:
					globalApp->createNewTab();
					break;
				case ID_VIEW_SELECT_NEXT_TAB:
					globalApp->showNextTab();
					break;
				case ID_VIEW_SELECT_PREV_TAB:
					globalApp->showPreviousTab();
					break;
				case ID_VIEW_CLOSE_TAB:
					globalApp->closeTab();
					break;
				case ID_VIEW_TOGGLE_CONSOLE:
					globalApp->toggleConsole();
					break;

				case ID_PROJECT_RUN:
					globalApp->runProject();
					break;
				case ID_PROJECT_EXPORT:
					globalApp->exportProject();
					break;
	
				case ID_HELP_ABOUT:
					globalApp->showAbout();
					break;
				case ID_HELP_REFERENCE:
					globalApp->openDocs(); 
					break;
			}
		break;
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
	case WM_TOUCH:
		if(core) {
			if(core->isMultiTouchEnabled()) {
				core->handleTouchEvent(lParam, wParam);
			}
		}
	break;
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
	{
		globalApp->saveConfigFile();
		bool retVal = globalApp->quitApp();
		if (retVal) {
			core->Shutdown();
			useDefault = true;
		}
	}
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


PolycodeWinIDEView::PolycodeWinIDEView(HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle, bool resizable, bool showDebugConsole) : PolycodeViewBase() {

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
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_POLYCODEMENU);
	wcex.lpszClassName	= L"POLYCODEAPPLICATION";
	wcex.hIconSm		= LoadIcon(hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	if(resizable) {
		hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_OVERLAPPEDWINDOW|WS_SYSMENU, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
	} else {
		hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_OVERLAPPED|WS_SYSMENU, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
	}

	windowData = (void*)&hwnd;
	this->resizable = resizable;

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   haccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(POLYCODE_ACCELERATORS));

   if(showDebugConsole) {
		OpenConsole();
   }

}

PolycodeWinIDEView::~PolycodeWinIDEView() {

}