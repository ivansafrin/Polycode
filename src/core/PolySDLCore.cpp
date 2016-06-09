/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/		

#include "polycode/core/PolySDLCore.h"
#include "polycode/view/linux/PolycodeView.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCoreInput.h"
#include "polycode/core/PolyMaterialManager.h"
#include "polycode/core/PolyThreaded.h"
#include "polycode/core/PolyLogger.h"

#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolyBasicFileProvider.h"
#include "polycode/core/PolyPhysFSFileProvider.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

#ifdef USE_X11
// X11 cursor
#include <X11/cursorfont.h>

namespace {
	Display* XDisplay = nullptr;
	Window XWindow;
	
	void set_cursor(int cursorType);
	void free_cursors();
} // namespace
// end X11 cursor

#endif

using namespace Polycode;
using std::vector;

void SDLCoreMutex::lock()
{
	SDL_mutexP(pMutex);
}

void SDLCoreMutex::unlock() {
	SDL_mutexV(pMutex);
}


long getThreadID() {
	return (long)pthread_self();
}

void Core::getScreenInfo(int *width, int *height, int *hz) {
	SDL_DisplayMode current;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GetCurrentDisplayMode(0, &current);

	if (width) *width = current.w;
	if (height) *height = current.h;
	if (hz) *hz = current.refresh_rate;
}

SDLCore::SDLCore(PolycodeView *view, int _xRes, int _yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) : Core(_xRes, _yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {
 
	this->resizableWindow = view->resizable;

	fileProviders.push_back(new BasicFileProvider());
	fileProviders.push_back(new PhysFSFileProvider());
	
	char *buffer = getcwd(NULL, 0);
	defaultWorkingDirectory = String(buffer);
	free(buffer);

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	userHomeDirectory = String(homedir);

	initKeymap();
	
	windowTitle = (String*)view->windowData;
	
	if(resizableWindow) {
		unsetenv("SDL_VIDEO_CENTERED");
	} else {
		setenv("SDL_VIDEO_CENTERED", "1", 1);
	}
		
	int sdlerror = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
	if(sdlerror < 0) {
	  Logger::log("SDL_Init failed! Code: %d, %s\n", sdlerror, SDL_GetError());
	}
	
	eventMutex = createMutex();
	
	renderer = new Renderer();
	OpenGLGraphicsInterface *renderInterface = new OpenGLGraphicsInterface();
	renderInterface->lineSmooth = true;
	renderer->setGraphicsInterface(this, renderInterface);
	services->setRenderer(renderer);
	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
	
	SDL_JoystickEventState(SDL_ENABLE);
	
	int numJoysticks = SDL_NumJoysticks();
	
	for(int i=0; i < numJoysticks; i++) {
		SDL_JoystickOpen(i);
		input->addJoystick(i);
	}
	
	services->getSoundManager()->setAudioInterface(new PAAudioInterface());
	
	lastMouseX = 0;
	lastMouseY = 0;

}


void SDLCore::handleVideoModeChange(VideoModeChangeInfo* modeInfo){

	this->xRes = modeInfo->xRes;
	this->yRes = modeInfo->yRes;
	this->fullScreen = modeInfo->fullScreen;
	this->aaLevel = modeInfo->aaLevel;
	this->anisotropyLevel = modeInfo->anisotropyLevel;
	this->vSync = modeInfo->vSync;
	
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
	
	if(aaLevel > 0) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, aaLevel); //0, 2, 4
	} else {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	}
	
	flags = SDL_WINDOW_OPENGL;

	if(fullScreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if(resizableWindow) {
		flags |= SDL_WINDOW_RESIZABLE;
	}
	
	if(modeInfo->retinaSupport) {
		flags |= SDL_WINDOW_ALLOW_HIGHDPI;
	}
	
	if(vSync){
		if(SDL_GL_SetSwapInterval(-1) == -1){
			SDL_GL_SetSwapInterval(1);
		}
	} else {
		SDL_GL_SetSwapInterval(0);
	}
	
	if(!sdlWindow){
		sdlWindow = SDL_CreateWindow(windowTitle->c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xRes, yRes, flags);
		sdlContext = SDL_GL_CreateContext(sdlWindow);
		SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
		if(icon){
			SDL_SetWindowIcon(sdlWindow, icon);
		}
	} else {
		SDL_SetWindowSize(sdlWindow, xRes, yRes);
	}

	int x, y;
	SDL_GL_GetDrawableSize(sdlWindow, &x, &y);
	if(x >= xRes){
		backingX = x;
	}else{
		backingX = xRes;
	}
	if(y >= yRes){
		backingY = y;
	}else{
		backingY = yRes;
	}
	
	int glewcode = glewInit();
	if (glewcode != GLEW_OK){
	  Logger::log("glewInit failed! code: %d, %s\n", glewcode, glewGetErrorString(glewcode));
	}
	
	renderer->setAnisotropyAmount(modeInfo->anisotropyLevel);

#ifdef USE_X11
	if(!XWindow){
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		
		if ( SDL_GetWindowWMInfo(sdlWindow, &info) == SDL_TRUE ){
			if ( info.subsystem == SDL_SYSWM_X11 ){
				XDisplay = info.info.x11.display;
				XWindow = info.info.x11.window;
			}
		}
	}
#endif
}

vector<Polycode::Rectangle> SDLCore::getVideoModes() {
	vector<Polycode::Rectangle> retVector;
	
	SDL_DisplayMode modes;
	for(int i=0;i<SDL_GetNumDisplayModes(0);++i) {
		SDL_GetDisplayMode(0, i, &modes);
		Rectangle res;
		res.w = modes.w;
		res.h = modes.h;
		retVector.push_back(res);
	}	
	
	return retVector;
}

SDLCore::~SDLCore() {
	SDL_GL_DeleteContext(sdlContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void SDLCore::openURL(String url) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
	execl("/usr/bin/xdg-open", "/usr/bin/xdg-open", url.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, WNOHANG);
	}
}

String SDLCore::executeExternalCommand(String command, String args, String inDirectory) {
	String finalCommand = command + " " + args;

	if(inDirectory != "") {
		finalCommand = "cd " + inDirectory + " && " + finalCommand;
	}

	FILE *fp = popen(finalCommand.c_str(), "r");
	if(!fp) {
		return "Unable to execute command";
	}	

	int fd = fileno(fp);

	char path[2048];
	String retString;

	while (fgets(path, sizeof(path), fp) != NULL) {
		retString = retString + String(path);
	}

	pclose(fp);
	return retString;
}

int SDLThreadFunc(void *data) {
	Threaded *target = (Threaded*)data;
	target->runThread();
	return 1;
}

void SDLCore::createThread(Threaded *target) {
	SDL_CreateThread(SDLThreadFunc, "PolycodeThread", (void*)target);
}

unsigned int SDLCore::getTicks() {
	return SDL_GetTicks();
}

void SDLCore::enableMouse(bool newval) {
	if(newval) {
		SDL_ShowCursor(1);
	} else {
		SDL_ShowCursor(0);
	}
	Core::enableMouse(newval);
}

void SDLCore::captureMouse(bool newval) {
	if(newval) {
 		SDL_SetWindowGrab(sdlWindow, SDL_TRUE);
	} else {
		SDL_SetWindowGrab(sdlWindow, SDL_FALSE);
	}
	Core::captureMouse(newval);
}

void SDLCore::initKeymap(){
	
	for (int i=0; i<512; ++i )
		keyMap[i] = KEY_UNKNOWN;

	keyMap[SDL_SCANCODE_BACKSPACE] = KEY_BACKSPACE;
	keyMap[SDL_SCANCODE_TAB] = KEY_TAB;
	keyMap[SDL_SCANCODE_CLEAR] = KEY_CLEAR;
	keyMap[SDL_SCANCODE_RETURN] = KEY_RETURN;
	keyMap[SDL_SCANCODE_PAUSE] = KEY_PAUSE;
	keyMap[SDL_SCANCODE_ESCAPE] = KEY_ESCAPE;
	keyMap[SDL_SCANCODE_SPACE] = KEY_SPACE;
	keyMap[SDL_SCANCODE_APOSTROPHE] = KEY_QUOTE;
	keyMap[SDL_SCANCODE_COMMA] = KEY_COMMA;
	keyMap[SDL_SCANCODE_MINUS] = KEY_MINUS;
	keyMap[SDL_SCANCODE_PERIOD] = KEY_PERIOD;
	keyMap[SDL_SCANCODE_SLASH] = KEY_SLASH;
	keyMap[SDL_SCANCODE_0] = KEY_0;
	keyMap[SDL_SCANCODE_1] = KEY_1;
	keyMap[SDL_SCANCODE_2] = KEY_2;
	keyMap[SDL_SCANCODE_3] = KEY_3;
	keyMap[SDL_SCANCODE_4] = KEY_4;
	keyMap[SDL_SCANCODE_5] = KEY_5;
	keyMap[SDL_SCANCODE_6] = KEY_6;
	keyMap[SDL_SCANCODE_7] = KEY_7;
	keyMap[SDL_SCANCODE_8] = KEY_8;
	keyMap[SDL_SCANCODE_9] = KEY_9;
	keyMap[SDL_SCANCODE_SEMICOLON] = KEY_SEMICOLON;
	keyMap[SDL_SCANCODE_EQUALS] = KEY_EQUALS;
	keyMap[SDL_SCANCODE_RIGHTBRACKET] = KEY_LEFTBRACKET;
	keyMap[SDL_SCANCODE_BACKSLASH] = KEY_BACKSLASH;
	keyMap[SDL_SCANCODE_NONUSBACKSLASH] = KEY_LESS;
	keyMap[SDL_SCANCODE_RIGHTBRACKET] = KEY_RIGHTBRACKET;
	keyMap[SDL_SCANCODE_GRAVE] = KEY_BACKQUOTE;
// 	keyMap[SDL_SCANCODE_BACKTICK] = KEY_BACKQUOTE;
	keyMap[SDL_SCANCODE_A] = KEY_a;
	keyMap[SDL_SCANCODE_B] = KEY_b;
	keyMap[SDL_SCANCODE_C] = KEY_c;
	keyMap[SDL_SCANCODE_D] = KEY_d;
	keyMap[SDL_SCANCODE_E] = KEY_e;
	keyMap[SDL_SCANCODE_F] = KEY_f;
	keyMap[SDL_SCANCODE_G] = KEY_g;
	keyMap[SDL_SCANCODE_H] = KEY_h;
	keyMap[SDL_SCANCODE_I] = KEY_i;
	keyMap[SDL_SCANCODE_J] = KEY_j;
	keyMap[SDL_SCANCODE_K] = KEY_k;
	keyMap[SDL_SCANCODE_L] = KEY_l;
	keyMap[SDL_SCANCODE_M] = KEY_m;
	keyMap[SDL_SCANCODE_N] = KEY_n;
	keyMap[SDL_SCANCODE_O] = KEY_o;
	keyMap[SDL_SCANCODE_P] = KEY_p;
	keyMap[SDL_SCANCODE_Q] = KEY_q;
	keyMap[SDL_SCANCODE_R] = KEY_r;
	keyMap[SDL_SCANCODE_S] = KEY_s;
	keyMap[SDL_SCANCODE_T] = KEY_t;
	keyMap[SDL_SCANCODE_U] = KEY_u;
	keyMap[SDL_SCANCODE_V] = KEY_v;
	keyMap[SDL_SCANCODE_W] = KEY_w;
	keyMap[SDL_SCANCODE_X] = KEY_x;
	keyMap[SDL_SCANCODE_Y] = KEY_y;
	keyMap[SDL_SCANCODE_Z] = KEY_z;
	keyMap[SDL_SCANCODE_DELETE] = KEY_DELETE;

	keyMap[SDL_SCANCODE_KP_0] = KEY_KP0;
	keyMap[SDL_SCANCODE_KP_1] = KEY_KP1;
	keyMap[SDL_SCANCODE_KP_2] = KEY_KP2;
	keyMap[SDL_SCANCODE_KP_3] = KEY_KP3;
	keyMap[SDL_SCANCODE_KP_4] = KEY_KP4;
	keyMap[SDL_SCANCODE_KP_5] = KEY_KP5;
	keyMap[SDL_SCANCODE_KP_6] = KEY_KP6;
	keyMap[SDL_SCANCODE_KP_7] = KEY_KP7;
	keyMap[SDL_SCANCODE_KP_8] = KEY_KP8;
	keyMap[SDL_SCANCODE_KP_9] = KEY_KP9;
	keyMap[SDL_SCANCODE_KP_DECIMAL] = KEY_KP_PERIOD;
	keyMap[SDL_SCANCODE_KP_DIVIDE] = KEY_KP_DIVIDE;
	keyMap[SDL_SCANCODE_KP_MULTIPLY] = KEY_KP_MULTIPLY;
	keyMap[SDL_SCANCODE_KP_MINUS] = KEY_KP_MINUS;
	keyMap[SDL_SCANCODE_KP_PLUS] = KEY_KP_PLUS;

	keyMap[SDL_SCANCODE_UP] = KEY_UP;
	keyMap[SDL_SCANCODE_DOWN] = KEY_DOWN;
	keyMap[SDL_SCANCODE_RIGHT] = KEY_RIGHT;
	keyMap[SDL_SCANCODE_LEFT] = KEY_LEFT;
	keyMap[SDL_SCANCODE_INSERT] = KEY_INSERT;
	keyMap[SDL_SCANCODE_HOME] = KEY_HOME;
	keyMap[SDL_SCANCODE_END] = KEY_END;
	keyMap[SDL_SCANCODE_PAGEUP] = KEY_PAGEUP;
	keyMap[SDL_SCANCODE_PAGEDOWN] = KEY_PAGEDOWN;

	keyMap[SDL_SCANCODE_F1] = KEY_F1;
	keyMap[SDL_SCANCODE_F2] = KEY_F2;
	keyMap[SDL_SCANCODE_F3] = KEY_F3;
	keyMap[SDL_SCANCODE_F4] = KEY_F4;
	keyMap[SDL_SCANCODE_F5] = KEY_F5;
	keyMap[SDL_SCANCODE_F6] = KEY_F6;
	keyMap[SDL_SCANCODE_F7] = KEY_F7;
	keyMap[SDL_SCANCODE_F8] = KEY_F8;
	keyMap[SDL_SCANCODE_F9] = KEY_F9;
	keyMap[SDL_SCANCODE_F10] = KEY_F10;
	keyMap[SDL_SCANCODE_F11] = KEY_F11;
	keyMap[SDL_SCANCODE_F12] = KEY_F12;
	keyMap[SDL_SCANCODE_F13] = KEY_F13;
	keyMap[SDL_SCANCODE_F14] = KEY_F14;
	keyMap[SDL_SCANCODE_F15] = KEY_F15;

	keyMap[131] = KEY_NUMLOCK;
	keyMap[130] = KEY_CAPSLOCK;
	keyMap[132] = KEY_SCROLLOCK;
	keyMap[SDL_SCANCODE_RSHIFT] = KEY_RSHIFT;
	keyMap[SDL_SCANCODE_LSHIFT] = KEY_LSHIFT;
	keyMap[SDL_SCANCODE_RCTRL] = KEY_RCTRL;
	keyMap[SDL_SCANCODE_LCTRL] = KEY_LCTRL;
	keyMap[SDL_SCANCODE_RALT] = KEY_RALT;
	keyMap[SDL_SCANCODE_LALT] = KEY_LALT;
	keyMap[SDL_SCANCODE_RGUI] = KEY_RSUPER;
	keyMap[SDL_SCANCODE_LGUI] = KEY_LSUPER;

	keyMap[SDL_SCANCODE_HELP] = KEY_HELP;
	keyMap[SDL_SCANCODE_PRINTSCREEN] = KEY_PRINT;
	keyMap[SDL_SCANCODE_CANCEL] = KEY_BREAK;
	keyMap[SDL_SCANCODE_MENU] = KEY_MENU;
}


PolyKEY SDLCore::mapKey(SDL_Scancode key){
	return keyMap[key];
}


bool SDLCore::checkSpecialKeyEvents(PolyKEY key) {
	
	if(key == KEY_a && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_SELECT_ALL);
		return true;
	}
	
	if(key == KEY_c && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_COPY);
		return true;
	}
	
	if(key == KEY_x && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_CUT);
		return true;
	}
	
	
	if(key == KEY_z	 && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL)) && (input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT))) {
		dispatchEvent(new Event(), Core::EVENT_REDO);
		return true;
	}
		
	if(key == KEY_z	 && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_UNDO);
		return true;
	}
	
	if(key == KEY_v && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_PASTE);
		return true;
	}
	return false;
}

void SDLCore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, getBackingXRes(), getBackingYRes()));
	renderer->endFrame();
}

void SDLCore::flushRenderContext(){
	SDL_GL_SwapWindow(sdlWindow);
}

bool SDLCore::systemUpdate() {
	if(!running)
		return false;
	doSleep();	
	
	updateCore();
	
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
				break;
				case SDL_WINDOWEVENT:
					switch(event.window.event){
						case SDL_WINDOWEVENT_RESIZED:
							if(resizableWindow) {
								unsetenv("SDL_VIDEO_CENTERED");
							} else {
								setenv("SDL_VIDEO_CENTERED", "1", 1);
							}
							this->xRes = event.window.data1;
							this->yRes = event.window.data2;
							
							SDL_SetWindowSize(sdlWindow, xRes, yRes);
							
							int x, y;
							SDL_GL_GetDrawableSize(sdlWindow, &x, &y);
							if(x >= xRes){
								backingX = x;
							}else{
								backingX = xRes;
							}
							if(y >= yRes){
								backingY = y;
							}else{
								backingY = yRes;
							}
							
							dispatchEvent(new Event(), EVENT_CORE_RESIZE);	
						break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							gainFocus();
						break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
							loseFocus();
						break;
					}
				case SDL_JOYAXISMOTION:
					input->joystickAxisMoved(event.jaxis.axis, ((Number)event.jaxis.value)/32767.0, event.jaxis.which);
				break;
				case SDL_JOYBUTTONDOWN:
					input->joystickButtonDown(event.jbutton.button, event.jbutton.which);
				break;
				case SDL_JOYBUTTONUP:
					input->joystickButtonUp(event.jbutton.button, event.jbutton.which);
				break;
				case SDL_KEYDOWN:
					if(!checkSpecialKeyEvents(mapKey(event.key.keysym.scancode))) {
						input->setKeyState(mapKey(event.key.keysym.scancode), event.key.keysym.sym, true, getTicks());
					}
				break;
				case SDL_KEYUP:
					input->setKeyState(mapKey(event.key.keysym.scancode), event.key.keysym.sym, false, getTicks());
				break;
				case SDL_MOUSEWHEEL:
					if(event.wheel.y > 0) {
						input->mouseWheelUp(getTicks());
					} else if(event.wheel.y < 0) {
						input->mouseWheelDown(getTicks());
					}
				break;
				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button) {
						case SDL_BUTTON_LEFT:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON1, true, getTicks());
						break;
						case SDL_BUTTON_RIGHT:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON2, true, getTicks());
						break;
						case SDL_BUTTON_MIDDLE:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON3, true, getTicks());
						break;
					}
				break;
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button) {
						case SDL_BUTTON_LEFT:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON1, false, getTicks());
						break;
						case SDL_BUTTON_RIGHT:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON2, false, getTicks());
						break;
						case SDL_BUTTON_MIDDLE:
							input->setMouseButtonState(CoreInput::MOUSE_BUTTON3, false, getTicks());
						break;
					}
				break;
				case SDL_MOUSEMOTION:
					input->setDeltaPosition(lastMouseX - event.motion.x, lastMouseY - event.motion.y);					
					input->setMousePosition(event.motion.x, event.motion.y, getTicks());
					lastMouseY = event.motion.y;
					lastMouseX = event.motion.x;
				break;
				default:
					break;
			}
		}
	return running;
}

void SDLCore::setCursor(int cursorType) {
#ifdef USE_X11
	set_cursor(cursorType);
#endif // USE_X11
}

void SDLCore::warpCursor(int x, int y) {
	SDL_WarpMouseInWindow(sdlWindow, x, y);
	lastMouseX = x;
	lastMouseY = y;
}

CoreMutex *SDLCore::createMutex() {
	SDLCoreMutex *mutex = new SDLCoreMutex();
	mutex->pMutex = SDL_CreateMutex();
	return mutex;	
}

void SDLCore::copyStringToClipboard(const String& str) {
	SDL_SetClipboardText(str.c_str());
}

String SDLCore::getClipboardString() {
	String rval;
	if(SDL_HasClipboardText() ==SDL_TRUE){
		rval=SDL_GetClipboardText();
	} else {
		rval="";
	}
	return rval;
}

void SDLCore::createFolder(const String& folderPath) {
	mkdir(folderPath.c_str(), 0700);
}

void SDLCore::copyDiskItem(const String& itemPath, const String& destItemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/cp", "/bin/cp", "-RT", itemPath.c_str(), destItemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

void SDLCore::moveDiskItem(const String& itemPath, const String& destItemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/mv", "/bin/mv", itemPath.c_str(), destItemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

void SDLCore::removeDiskItem(const String& itemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/rm", "/bin/rm", "-rf", itemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

String SDLCore::openFolderPicker() {
	String r = "";
	return r;
}

vector<String> SDLCore::openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) {
	vector<String> r;
	return r;
}

String SDLCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
		String r = "";
		return r;
}

void SDLCore::resizeTo(int xRes, int yRes) {
	this->xRes = xRes;
	this->yRes = yRes;
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);
}

bool SDLCore::systemParseFolder(const String& pathString, bool showHidden, vector< OSFileEntry >& targetVector) {
	DIR			  *d;
	struct dirent *dir;
	
	d = opendir(pathString.c_str());
	if(d) {
		while ((dir = readdir(d)) != NULL) {
			if(dir->d_name[0] != '.' || (dir->d_name[0] == '.'	&& showHidden)) {
				if(dir->d_type == DT_DIR) {
					targetVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FOLDER));
				} else {
					targetVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FILE));
				}
			}
		}
		closedir(d);
	}
	return true;
}

Number SDLCore::getBackingXRes() {
	return backingX;
}

Number SDLCore::getBackingYRes() {
	return backingY;
}

#ifdef USE_X11
// X11 cursor

namespace {

const int CURSOR_COUNT = 7;
Cursor defined_cursors[CURSOR_COUNT] = {0};

void set_cursor(int cursorType) {
	Cursor cursor = 0;
	
	if(cursorType >= 0 && cursorType < CURSOR_COUNT) {
		cursor = defined_cursors[cursorType];
		if(!cursor) {
			switch(cursorType) {
				case Polycode::Core::CURSOR_TEXT:
					cursor = XCreateFontCursor (XDisplay, XC_xterm);
				break;
				case Polycode::Core::CURSOR_POINTER:
					cursor = XCreateFontCursor (XDisplay, XC_hand1);
				break;
				case Polycode::Core::CURSOR_CROSSHAIR:
					cursor = XCreateFontCursor (XDisplay, XC_crosshair);
				break;
				case Polycode::Core::CURSOR_RESIZE_LEFT_RIGHT:
					cursor = XCreateFontCursor (XDisplay, XC_sb_h_double_arrow);
				break;
				case Polycode::Core::CURSOR_RESIZE_UP_DOWN:
					cursor = XCreateFontCursor (XDisplay, XC_sb_v_double_arrow);
				break;
				case Polycode::Core::CURSOR_OPEN_HAND:
					cursor = XCreateFontCursor (XDisplay, XC_fleur);
				break;
				case Polycode::Core::CURSOR_ARROW:
					cursor = 0;
				break;
			}

			defined_cursors[cursorType] = cursor;
		}
	}

	if(!cursor) {
		// Restore the normal cursor.
		XUndefineCursor(XDisplay, XWindow);
	} else {
		XDefineCursor(XDisplay, XWindow, cursor);
	}
	
	XFlush(XDisplay);
}

void free_cursors() {
	XUndefineCursor(XDisplay, XWindow);
	for(int i = 0; i < CURSOR_COUNT; i++) {
		if(defined_cursors[i]) {
			XFreeCursor(XDisplay, defined_cursors[i]);
			defined_cursors[i] = 0;
		}
	}
}
} // namespace
// end X11 cursor

#endif // USE_X11