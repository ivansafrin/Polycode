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

#include "polycode/core/PolyEmscriptenCore.h"
#include "polycode/view/linux/PolycodeView.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCoreInput.h"
#include "polycode/core/PolyThreaded.h"
#include "polycode/core/PolyLogger.h"

#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolyBasicFileProvider.h"
#ifndef NO_PHYSFS
	#include "polycode/core/PolyPhysFSFileProvider.h"
#endif

#include <SDL2/SDL.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

using namespace Polycode;
using std::vector;

void EmscriptenCoreMutex::lock()
{
	//pthread_mutex_lock(&pMutex);	  
}

void EmscriptenCoreMutex::unlock() {
//	pthread_mutex_unlock(&pMutex);
}


long getThreadID() {
	return 0;
}

void Core::getScreenInfo(int *width, int *height, int *hz) {
	SDL_DisplayMode current;

	SDL_GetCurrentDisplayMode(0, &current);

	if (width) *width = current.w;
	if (height) *height = current.h;
	if (hz) *hz = current.refresh_rate;
}

EmscriptenCore::EmscriptenCore(PolycodeView *view, int _xRes, int _yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) : Core(_xRes, _yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {
  
	this->resizableWindow = view->resizable;

	fileProviders.push_back(new BasicFileProvider());
#ifndef NO_PHYSFS
	fileProviders.push_back(new PhysFSFileProvider());
#endif
	char *buffer = getcwd(NULL, 0);
	defaultWorkingDirectory = String(buffer);
	free(buffer);

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	userHomeDirectory = String(homedir);

	windowTitle = (String*)view->windowData;
	
	if(resizableWindow) {
		unsetenv("SDL_VIDEO_CENTERED");
	} else {
		setenv("SDL_VIDEO_CENTERED", "1", 1);
	}

	sdlContext = nullptr;
	sdlWindow = nullptr;
	
	int sdlerror = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
	if(sdlerror < 0) {
	  Logger::log("SDL_Init failed! Code: %d, %s\n", sdlerror, SDL_GetError());
	}
	
	eventMutex = createMutex();
	
	renderThread = new RenderThread();
	renderer = new Renderer(renderThread);


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

#ifndef NO_PAUDIO
	services->getSoundManager()->setAudioInterface(new PAAudioInterface());
#else
	services->getSoundManager()->setAudioInterface(new SDLAudioInterface());
#endif

	lastMouseX = 0;
	lastMouseY = 0;
}

void EmscriptenCore::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, bool retinaSupport) {
	Core::setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
}

void EmscriptenCore::handleVideoModeChange(VideoModeChangeInfo* modeInfo){


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

	if(vSync) {
		if(SDL_GL_SetSwapInterval(-1) == -1) {
			SDL_GL_SetSwapInterval(1);
		}
	} else {
		SDL_GL_SetSwapInterval(0);
	}

	if(!sdlWindow) {
		sdlWindow = SDL_CreateWindow(windowTitle->c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xRes, yRes, flags);
		sdlContext = SDL_GL_CreateContext(sdlWindow);
		SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
		if(icon){
			SDL_SetWindowIcon(sdlWindow, icon);
		} else {
			Logger::log("icon error: %s\n",SDL_GetError());
		}
	} else {
		SDL_SetWindowSize(sdlWindow, xRes, yRes);
	}

	int x, y;
	SDL_GL_GetDrawableSize(sdlWindow, &x, &y);
	if(x >= xRes){
		backingX = x;
	} else {
		backingX = xRes;
	}
	if(y >= yRes) {
		backingY = y;
	} else {
		backingY = yRes;
	}

	/*
	int glewcode = glewInit();
	if (glewcode != GLEW_OK){
	  Logger::log("glewInit failed! code: %d, %s\n", glewcode, glewGetErrorString(glewcode));
	}
	*/

	//setVSync(modeInfo->vSync);
	renderer->setAnisotropyAmount(modeInfo->anisotropyLevel);
	renderThread->initGlobals();
}

vector<Polycode::Rectangle> EmscriptenCore::getVideoModes() {
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

EmscriptenCore::~EmscriptenCore() {
	SDL_GL_DeleteContext(sdlContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void EmscriptenCore::openURL(String url) { // TODO
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
	execl("/usr/bin/xdg-open", "/usr/bin/xdg-open", url.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, WNOHANG);
	}
}

String EmscriptenCore::executeExternalCommand(String command, String args, String inDirectory) {
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

void *ManagedThreadFunc(void *data) {
	Threaded *target = (Threaded*)data;
	target->runThread();
	target->scheduledForRemoval = true;
	return NULL;
}

void EmscriptenCore::createThread(Threaded *target) {
	Core::createThread(target);
//	pthread_t thread;
//	pthread_create( &thread, NULL, ManagedThreadFunc, (void*)target);
}

unsigned int EmscriptenCore::getTicks() {
	return SDL_GetTicks();
}

void EmscriptenCore::enableMouse(bool newval) {
	if(newval) {
		SDL_ShowCursor(1);
		//SDL_WM_GrabInput(SDL_GRAB_OFF);
	} else {
		SDL_ShowCursor(0);
		//SDL_WM_GrabInput(SDL_GRAB_ON);
	}
	Core::enableMouse(newval);
}

void EmscriptenCore::captureMouse(bool newval) {
	if(newval) {
		SDL_SetWindowGrab(sdlWindow, SDL_TRUE);
	} else {
		SDL_SetWindowGrab(sdlWindow, SDL_FALSE);
	}
	Core::captureMouse(newval);
}

bool EmscriptenCore::checkSpecialKeyEvents(PolyKEY key) {
	
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

void EmscriptenCore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, getBackingXRes(), getBackingYRes()));
	renderer->endFrame();
	renderThread->updateRenderThread();
}

void EmscriptenCore::flushRenderContext(){
	SDL_GL_SwapWindow(sdlWindow);
}

bool EmscriptenCore::systemUpdate() {
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
					switch (event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							if (resizableWindow) {
								unsetenv("SDL_VIDEO_CENTERED");
							} else {
								setenv("SDL_VIDEO_CENTERED", "1", 1);
							}
							this->xRes = event.window.data1;
							this->yRes = event.window.data2;

							SDL_SetWindowSize(sdlWindow, xRes, yRes);
							int x, y;
							SDL_GL_GetDrawableSize(sdlWindow, &x, &y);
							if (x >= xRes) {
								backingX = x;
							} else {
								backingX = xRes;
							}
							if (y >= yRes) {
								backingY = y;
							} else {
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
						input->setKeyState((PolyKEY)(event.key.keysym.sym), event.key.keysym.sym, true, getTicks()); 					}
				break;
				case SDL_KEYUP:
					input->setKeyState((PolyKEY)(event.key.keysym.sym), event.key.keysym.sym, false, getTicks());
				break;
				case SDL_MOUSEWHEEL:
					if(event.wheel.y > 0) {
						input->mouseWheelUp(getTicks());
					} else if(event.wheel.y < 0) {
						input->mouseWheelDown(getTicks());
					}
				break;
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
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

void EmscriptenCore::setCursor(int cursorType) {
}

void EmscriptenCore::warpCursor(int x, int y) {
	SDL_WarpMouseInWindow(sdlWindow, x, y);
	lastMouseX = x;
	lastMouseY = y;
}

/*void EmscriptenCore::lockMutex(CoreMutex *mutex) {
	EmscriptenCoreMutex *smutex = (EmscriptenCoreMutex*)mutex;
	SDL_mutexP(smutex->pMutex);

}

void EmscriptenCore::unlockMutex(CoreMutex *mutex) {
	EmscriptenCoreMutex *smutex = (EmscriptenCoreMutex*)mutex;
	SDL_mutexV(smutex->pMutex);
}*/

CoreMutex *EmscriptenCore::createMutex() {
	EmscriptenCoreMutex *mutex = new EmscriptenCoreMutex();
	//pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;	
}

void EmscriptenCore::copyStringToClipboard(const String& str) {
	SDL_SetClipboardText(str.c_str());
}

String EmscriptenCore::getClipboardString() {
	String rval;
	if(SDL_HasClipboardText() ==SDL_TRUE){
		rval=SDL_GetClipboardText();
	} else {
		rval="";
	}

	return rval;
}

void EmscriptenCore::createFolder(const String& folderPath) {
	mkdir(folderPath.c_str(), 0700);
}

void EmscriptenCore::copyDiskItem(const String& itemPath, const String& destItemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/cp", "/bin/cp", "-RT", itemPath.c_str(), destItemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

void EmscriptenCore::moveDiskItem(const String& itemPath, const String& destItemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/mv", "/bin/mv", itemPath.c_str(), destItemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

void EmscriptenCore::removeDiskItem(const String& itemPath) {
	int childExitStatus;
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/rm", "/bin/rm", "-rf", itemPath.c_str(), (char *)0);
	} else {
		pid_t ws = waitpid( pid, &childExitStatus, 0);
	}
}

String EmscriptenCore::openFolderPicker() {
	String r = "";
	return r;
}

vector<String> EmscriptenCore::openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) {
	vector<String> r;
	return r;
}

String EmscriptenCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
		String r = "";
		return r;
}

void EmscriptenCore::resizeTo(int xRes, int yRes) {
	this->xRes = xRes;
	this->yRes = yRes;
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);
}

bool EmscriptenCore::systemParseFolder(const String& pathString, bool showHidden, vector< OSFileEntry >& targetVector) {
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

Number EmscriptenCore::getBackingXRes() {
	return backingX;
}

Number EmscriptenCore::getBackingYRes() {
	return backingY;
}
