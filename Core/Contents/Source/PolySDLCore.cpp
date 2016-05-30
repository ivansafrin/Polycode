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

#include "PolySDLCore.h"
#include "PolycodeView.h"
#include "PolyCoreServices.h"
#include "PolyCoreInput.h"
#include "PolyMaterialManager.h"
#include "PolyThreaded.h"

#include "PolyGLRenderer.h"
#include "PolyGLSLShaderModule.h"
#include "PolyRectangle.h"

#include <stdio.h>
#include <limits.h>

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

#ifdef USE_X11
	// SDL scrap
	#define T(A, B, C, D)	(int)((A<<24)|(B<<16)|(C<<8)|(D<<0))

	int init_scrap(void);
	int lost_scrap(void);
	void put_scrap(int type, int srclen, const char *src);
	void get_scrap(int type, int *dstlen, char **dst);
	// end SDL scrap

// X11 cursor
#include <X11/cursorfont.h>

namespace {
	void set_cursor(int cursorType);
	void free_cursors();
} // namespace
// end X11 cursor

#endif

using namespace Polycode;
using std::vector;

long getThreadID() {
	return (long)pthread_self();
}

void Core::getScreenInfo(int *width, int *height, int *hz) {
	SDL_DisplayMode current;

	SDL_GetCurrentDisplayMode(0, &current);

	if (width) *width = current.w;
	if (height) *height = current.h;
	if (hz) *hz = current.refresh_rate;
}

SDLCore::SDLCore(PolycodeView *view, int _xRes, int _yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) : Core(_xRes, _yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

	this->resizableWindow = view->resizable;

	char *buffer = getcwd(NULL, 0);
	defaultWorkingDirectory = String(buffer);
	free(buffer);

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	userHomeDirectory = String(homedir);

	String *windowTitle = (String*)view->windowData;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0) {
		// Should something be done if it can't initialize?
	}
	
	eventMutex = createMutex();
	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);

	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
	SDL_SetWindowTitle(sdlWindow, windowTitle->c_str());
	
	SDL_JoystickEventState(SDL_ENABLE);
	
	int numJoysticks = SDL_NumJoysticks();
	
	for(int i=0; i < numJoysticks; i++) {
		SDL_JoystickOpen(i);
		input->addJoystick(i);
	}



#ifdef USE_X11
	// Start listening to clipboard events.
	// (Yes on X11 you need to actively listen to
	//  clipboard events and respond to them)
	init_scrap();
#endif // USE_X11

	((OpenGLRenderer*)renderer)->Init();
	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
}

void SDLCore::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, bool retinaSupport) {
	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	this->aaLevel = aaLevel;

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
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

	if(retinaSupport) {
		flags |= SDL_WINDOW_ALLOW_HIGHDPI;
	}

	if(vSync) {
		if(SDL_GL_SetSwapInterval(-1) == -1){
			SDL_GL_SetSwapInterval(1);
		}
	} else {
		SDL_GL_SetSwapInterval(0);
	}

	if(!sdlWindow) {
		sdlWindow = SDL_CreateWindow("Polycode", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xRes, yRes, flags);
		sdlContext = SDL_GL_CreateContext(sdlWindow);
	} else {
		SDL_SetWindowSize(sdlWindow, xRes, yRes);
	}
	
	renderer->Resize(xRes, yRes);
	//CoreServices::getInstance()->getMaterialManager()->reloadProgramsAndTextures();
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);	
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
#ifdef USE_X11
	free_cursors();
#endif // USE_X11
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
		SDL_SetRelativeMouseMode(SDL_FALSE);
	} else {
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	Core::enableMouse(newval);
}

void SDLCore::captureMouse(bool newval) {
	if(newval) {
		//SDL_CaptureMouse(SDL_TRUE); SDL 2.0.4
		SDL_SetWindowGrab(sdlWindow, SDL_TRUE);
	} else {
		//SDL_CaptureMouse(SDL_FALSE);  SDL 2.0.4
		SDL_SetWindowGrab(sdlWindow, SDL_TRUE);
	}
	Core::captureMouse(newval);
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
	
	
	if(key == KEY_z  && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL)) && (input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT))) {
		dispatchEvent(new Event(), Core::EVENT_REDO);
		return true;
	}
		
	if(key == KEY_z  && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
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
	renderer->BeginRender();
	services->Render();
	renderer->EndRender();
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
				case SDL_WINDOWEVENT_RESIZED:
					if(resizableWindow) {
						unsetenv("SDL_VIDEO_CENTERED");
					} else {
						setenv("SDL_VIDEO_CENTERED", "1", 1);
					}
					this->xRes = event.window.data1;
					this->yRes = event.window.data2;
					SDL_SetWindowSize(sdlWindow, xRes, yRes);
					renderer->Resize(xRes, yRes);	
					dispatchEvent(new Event(), EVENT_CORE_RESIZE);	
				break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
							gainFocus();
				break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
							loseFocus();
				break;
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
					if(!checkSpecialKeyEvents((PolyKEY)(event.key.keysym.sym))) {
						input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.sym, true, getTicks());
					}
				break;
				case SDL_KEYUP:
					input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.sym, false, getTicks());
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
					input->setDeltaPosition(event.motion.xrel, event.motion.yrel);					
					input->setMousePosition(event.motion.x, event.motion.y, getTicks());
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
}

void SDLCore::lockMutex(CoreMutex *mutex) {
	SDLCoreMutex *smutex = (SDLCoreMutex*)mutex;
	SDL_mutexP(smutex->pMutex);

}

void SDLCore::unlockMutex(CoreMutex *mutex) {
	SDLCoreMutex *smutex = (SDLCoreMutex*)mutex;
	SDL_mutexV(smutex->pMutex);
}

CoreMutex *SDLCore::createMutex() {
	SDLCoreMutex *mutex = new SDLCoreMutex();
	mutex->pMutex = SDL_CreateMutex();
	return mutex;	
}

void SDLCore::copyStringToClipboard(const String& str) {
#ifdef USE_X11
	put_scrap(T('T', 'E', 'X', 'T'), str.size(), str.c_str());
#endif
}

String SDLCore::getClipboardString() {
#ifdef USE_X11
	int dstlen;
	char* buffer;
	get_scrap(T('T', 'E', 'X', 'T'), &dstlen, &buffer);
	
	String rval(buffer, dstlen);
	free(buffer);
	return rval;
#endif
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
	renderer->Resize(xRes, yRes);
}
