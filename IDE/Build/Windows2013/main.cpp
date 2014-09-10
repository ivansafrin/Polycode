#include <Polycode.h>
#include "PolycodeIDEApp.h"
#include "PolycodeWinIDEView.h"
#include "windows.h"
#include "resource.h"
#include <Shlobj.h>
#include <Shlwapi.h>
#include <shellapi.h>

extern PolycodeIDEApp *globalApp;

using namespace Polycode;

void registerFileType(String extension, String progId, String app, String defaultIcon, String desc) {
	HKEY hkey;

	RegCreateKeyEx(HKEY_CLASSES_ROOT,extension.getWDataWithEncoding(String::ENCODING_UTF8),0,0,0,KEY_ALL_ACCESS,0,&hkey,0);
	RegSetValueEx(hkey,L"",0,REG_SZ,(BYTE*)progId.getWDataWithEncoding(String::ENCODING_UTF8),progId.length() * sizeof(wchar_t));
	RegCloseKey(hkey);

	RegCreateKeyEx(HKEY_CLASSES_ROOT,L".polyproject\\OpenWithProgIds\\",0,0,0,KEY_ALL_ACCESS,0,&hkey,0);
	RegSetValueEx(hkey,progId.getWDataWithEncoding(String::ENCODING_UTF8),0,REG_NONE,0,0);
	RegCloseKey(hkey);

	RegCreateKeyEx(HKEY_CLASSES_ROOT,progId.getWDataWithEncoding(String::ENCODING_UTF8),0,0,0,KEY_ALL_ACCESS,0,&hkey,0);
	RegSetValueEx(hkey,L"",0,REG_SZ,(BYTE*)desc.getWDataWithEncoding(String::ENCODING_UTF8),desc.length() * sizeof(wchar_t));
	RegCloseKey(hkey);

	String path = progId + "\\shell\\open\\command\\";
	RegCreateKeyEx(HKEY_CLASSES_ROOT,path.getWDataWithEncoding(String::ENCODING_UTF8),0,0,0,KEY_ALL_ACCESS,0,&hkey,0);
	RegSetValueEx(hkey,L"",0,REG_SZ,(BYTE*)app.getWDataWithEncoding(String::ENCODING_UTF8),app.length() * sizeof(wchar_t));
	RegCloseKey(hkey);

	path = progId + "\\DefaultIcon\\";
	RegCreateKeyEx(HKEY_CLASSES_ROOT,path.getWDataWithEncoding(String::ENCODING_UTF8),0,0,0,KEY_ALL_ACCESS,0,&hkey,0);
	RegSetValueEx(hkey,L"",0,REG_SZ,(BYTE*)defaultIcon.getWDataWithEncoding(String::ENCODING_UTF8),defaultIcon.length() * sizeof(wchar_t));
	RegCloseKey(hkey);

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST,0,0);

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMessageFilter(WM_COPYDATA,MSGFLT_ADD);

	int nArgs;
	LPWSTR *szArglist =  CommandLineToArgvW(GetCommandLineW(), &nArgs);
	
	String fileName = "";
	if(nArgs > 1) {
		fileName = String(szArglist[1]);
	}

	fileName = fileName.replace("\\", "/");

	// check if an instance of Polycode is running and bring it up and open file if needed
	HWND runningHwnd = FindWindow(L"POLYCODEAPPLICATION", L"Polycode");
	if(runningHwnd) {
		SwitchToThisWindow(runningHwnd, FALSE);
		ShowWindow(runningHwnd,SW_NORMAL);

		if(fileName != "") {
			COPYDATASTRUCT cds;
			cds.cbData = (fileName.length() * sizeof(wchar_t)) + 1;
			cds.lpData = fileName.getWDataWithEncoding(String::ENCODING_UTF8);
			SendMessage(runningHwnd, WM_COPYDATA, 0, (LPARAM)&cds);
		}
		return 1;
	}

	TCHAR FilePath[MAX_PATH] = { 0 };
	GetModuleFileName( 0, FilePath, MAX_PATH );
	PathRemoveFileSpec( FilePath );    
	SetCurrentDirectory( FilePath );

	PolycodeWinIDEView *view = new PolycodeWinIDEView(hInstance, nCmdShow, L"Polycode", true, false);
	PolycodeIDEApp *app = new PolycodeIDEApp(view);

	globalApp = app;

	if(fileName != "") {
		app->openProject(fileName);
	}

	HICON mainIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(view->hwnd, WM_SETICON, ICON_SMALL, (LPARAM) mainIcon );

	registerFileType(".polyproject", "Polycode.ProjectFile.1", CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory()+"\\Polycode.exe \"%1\"", CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory()+"\\Polycode.exe,-103", "Polycode Project");
	registerFileType(".polyapp", "Polycode.Applicaton.1", CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory()+"\\Standalone\\Player\\PolycodePlayer.exe \"%1\"", CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory()+"\\Polycode.exe,-104", "Polycode Application");

	MSG Msg;
	do {
		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {

			if (!TranslateAccelerator(view->hwnd, view->haccel, &Msg)) {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
		if(((Win32Core*)app->core)->hasCopyDataString) {
			app->openProject(((Win32Core*)app->core)->copyDataString);
			((Win32Core*)app->core)->hasCopyDataString = false;
		}
	} while(app->Update());

	app->saveConfigFile();
	return Msg.wParam;
}