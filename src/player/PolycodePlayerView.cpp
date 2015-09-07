
#include "PolycodePlayerView.h"
#include "resource.h"
#include <Commdlg.h>

using namespace Polycode;

Win32Core *core = NULL;
HWND consoleHwnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;		
	int nWidth, nHeight;
	bool useDefault = false;

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

	case WM_TOUCH:
		if(core) {
			if(core->isMultiTouchEnabled()) {
				core->handleTouchEvent(lParam, wParam);
			}
		}
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
		useDefault = true;
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
      case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_EXIT:
					if(core)
						core->Shutdown();
                break;
				 case ID_FILE_OPEN:
					 {
					TCHAR szFile[2048];
					 OPENFILENAME ofn;
					 ZeroMemory(&ofn, sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = hWnd;
					ofn.lpstrFile = szFile;
					ofn.lpstrFile[0] = '\0';
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = L"Polycode Application (*.polyapp)\0*.POLYAPP\0";
ofn.nFilterIndex = 0;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


						 if (GetOpenFileName(&ofn)==TRUE) {

							 TCHAR tpath[2049];
							 GetModuleFileName(NULL, (LPWSTR)tpath, 2048);
							 STARTUPINFO si;
							 PROCESS_INFORMATION pi;
							 ZeroMemory(&si, sizeof(si));
							 
							 String fullLine = String(tpath);

							 CreateProcess(fullLine.getWDataWithEncoding(String::ENCODING_UTF8), szFile, NULL, NULL, false, 0, 0, NULL, &si, &pi);
						 }
					 }
                break;
                case ID_SHOW_CONSOLE:
					ShowWindow(consoleHwnd, SW_SHOW);
					UpdateWindow(consoleHwnd);
                break;
            }
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


LRESULT CALLBACK ConsoleWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;		
	int nWidth, nHeight;

	switch (message)
	{
	case WM_CLOSE:
		ShowWindow(consoleHwnd, SW_HIDE);
		UpdateWindow(consoleHwnd);
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void AppendTextToEditCtrl(HWND hWndEdit, LPCTSTR pszText)
{
   int nLength = Edit_GetTextLength(hWndEdit); 
   Edit_SetSel(hWndEdit, nLength, nLength);
   Edit_ReplaceSel(hWndEdit, pszText);
}


void PolycodePlayerView::handleEvent(Event *event){
	PolycodeDebugEvent *debugEvent = (PolycodeDebugEvent*) event;
	switch(event->getEventCode()) {
	case PolycodeDebugEvent::EVENT_ERROR:
		{
		String lineString = String("Error on line ");
		lineString = lineString + String::NumberToString(debugEvent->lineNumber);
		lineString = lineString + " - ";
		AppendTextToEditCtrl(consoleTextArea, lineString.getWDataWithEncoding(String::ENCODING_UTF8));
		AppendTextToEditCtrl(consoleTextArea, debugEvent->errorString.getWDataWithEncoding(String::ENCODING_UTF8));
		ShowWindow(consoleHwnd, SW_SHOW);
		UpdateWindow(consoleHwnd);
		}
	break;
	case PolycodeDebugEvent::EVENT_PRINT:
		AppendTextToEditCtrl(consoleTextArea, debugEvent->errorString.getWDataWithEncoding(String::ENCODING_UTF8));
		ShowWindow(consoleHwnd, SW_SHOW);
		UpdateWindow(consoleHwnd);
	break;

	}
}


PolycodePlayerView::PolycodePlayerView(bool standaloneMode, HINSTANCE hInstance, int nCmdShow, LPCTSTR windowTitle) : PolycodeViewBase(), EventHandler() {

WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	//wcex.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	if(standaloneMode) {
		wcex.lpszMenuName	=  NULL;
	} else {
		wcex.lpszMenuName	=  MAKEINTRESOURCE(IDR_MYMENU);;
	}
	wcex.lpszClassName	= L"POLYCODEAPPLICATION";
	wcex.hIconSm		= LoadIcon(hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

  hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"POLYCODEAPPLICATION", windowTitle, WS_OVERLAPPED|WS_SYSMENU,
      0, 0, 640, 480, NULL, NULL, hInstance, NULL);

  windowData = (void*)&hwnd;

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

	WNDCLASSEX console_wcex;

	console_wcex.cbSize = sizeof(WNDCLASSEX);
	console_wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	console_wcex.lpfnWndProc	= ConsoleWindowProc;
	console_wcex.cbClsExtra		= 0;
	console_wcex.cbWndExtra		= 0;
	console_wcex.hInstance		= hInstance;
	console_wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
	console_wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	console_wcex.hbrBackground	= NULL;
	console_wcex.lpszMenuName	= NULL;
	console_wcex.lpszClassName	= L"CONSOLEWINDOW";
	console_wcex.hIconSm		= LoadIcon(hInstance, IDI_APPLICATION);

	RegisterClassEx(&console_wcex);

	consoleHwnd = CreateWindowEx(WS_EX_TOOLWINDOW, L"CONSOLEWINDOW", L"Debug console.", WS_OVERLAPPED|WS_SYSMENU,
		640, 100, 500, 300, hwnd, NULL, hInstance, NULL);

	//ShowWindow(consoleHwnd, SW_SHOW);
	UpdateWindow(consoleHwnd);

	consoleTextArea = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",  WS_CHILD | WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY,
		0, 0, 500, 275, consoleHwnd, NULL, hInstance, NULL);


	ShowWindow(consoleTextArea, SW_SHOW);
	UpdateWindow(consoleTextArea);

	HFONT defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage (consoleTextArea, WM_SETFONT, WPARAM (defaultFont), TRUE);

}

PolycodePlayerView::~PolycodePlayerView() {

}