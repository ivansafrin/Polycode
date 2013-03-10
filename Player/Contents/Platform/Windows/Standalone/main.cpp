
#include "PolycodeWindowsPlayer.h"
#include <Polycode.h>
#include "PolycodePlayerView.h"
#include "windows.h"
#include "resource.h"
#include <io.h>
#include <fcntl.h>

using namespace Polycode;

extern Win32Core *core;

void wtoc(char* Dest, TCHAR* Source, int SourceSize)
{
for(int i = 0; i < SourceSize; ++i)
Dest[i] = (char)Source[i];
}

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
	
	SetCurrentDirectory(installPath.getWDataWithEncoding(String::ENCODING_UTF8));


	PolycodePlayerView *view = new PolycodePlayerView(true, hInstance, nCmdShow, L"");
	PolycodeWindowsPlayer *player = new PolycodeWindowsPlayer(view, "main.polyapp", false);

	player->addEventListener(view, PolycodeDebugEvent::EVENT_ERROR);
	player->addEventListener(view, PolycodeDebugEvent::EVENT_PRINT);

	OpenConsole();

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
