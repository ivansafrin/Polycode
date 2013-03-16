
#include "PolycodeWindowsPlayer.h"
#include <Polycode.h>
#include "PolycodePlayerView.h"
#include "windows.h"
#include "resource.h"

#define STANDALONE_MODE

using namespace Polycode;


extern Win32Core *core;

void wtoc(char* Dest, TCHAR* Source, int SourceSize)
{
for(int i = 0; i < SourceSize; ++i)
Dest[i] = (char)Source[i];
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	String args = String(GetCommandLineW());
	String fileName;
	for(int i=0; i < args.length(); i++) {
		if(args[i] != '\"')
			fileName += args.substr(i, 1);
		if(args[i] == '\"' && i != args.length()-1)
			fileName = "";
	}

	if(fileName == " ")
		fileName = "";

	if(fileName.length() > 1)  {
		fileName = fileName.replace(":", "");
		fileName = fileName.replace("\\", "/");
		fileName = fileName.substr(1, fileName.length() - 1);

	}

	char path[2049];
	TCHAR tpath[2049];
	GetModuleFileName(NULL, (LPWSTR)tpath, 2048);
	wtoc(path, tpath, 2048);
	
	String basePath = path;
	vector<String> cpts = basePath.split("\\");
	String installPath = "";
	for(int i=0; i < cpts.size() - 1; i++) {
		installPath = installPath + cpts[i];
		installPath += String("\\");
	}
	
	SetCurrentDirectory(installPath.wc_str());

//	fileName = "[" + fileName + "]";
//	MessageBox(NULL, fileName.wc_str(), L"", MB_OK);
//	fileName = L"/Documents and Settings/Administrator/Desktop/Workshop/HelloPolycodeLUA/ExampleProject.polyapp";

#ifdef STANDALONE_MODE
	PolycodePlayerView *view = new PolycodePlayerView(true, hInstance, nCmdShow, L"");
	PolycodeWindowsPlayer *player = new PolycodeWindowsPlayer(view, "main.polyapp", false);
#else
	PolycodePlayerView *view = new PolycodePlayerView(false, hInstance, nCmdShow, L"Polycode Player");
	PolycodeWindowsPlayer *player = new PolycodeWindowsPlayer(view, fileName.c_str(), false, true);
#endif
	player->addEventListener(view, PolycodeDebugEvent::EVENT_ERROR);
	player->addEventListener(view, PolycodeDebugEvent::EVENT_PRINT);


	player->runPlayer();

	core = (Win32Core*)player->getCore();

	MSG Msg;

		do {
			if(PeekMessage(&Msg, NULL, 0,0,PM_REMOVE)) {
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		} while(player->Update());
	
	return Msg.wParam;
}
