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

#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>
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
#endif

using namespace Polycode;
using std::vector;

long getThreadID() {
	return (long)pthread_self();
}

void Core::getScreenInfo(int *width, int *height, int *hz) {
	SDL_Init(SDL_INIT_VIDEO); // Or GetVideoInfo will not work
	const SDL_VideoInfo *video = SDL_GetVideoInfo();
	if (width) 
		*width = video->current_w;
	if (height) 
		*height = video->current_h;
	if (hz) 
		*hz = 0;
}

SDLCore::SDLCore(PolycodeView *view, int _xRes, int _yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex) : Core(_xRes, _yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

	this->resizableWindow = view->resizable;

	char *buffer = getcwd(NULL, 0);
	defaultWorkingDirectory = String(buffer);
	free(buffer);

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	userHomeDirectory = String(homedir);

	String *windowTitle = (String*)view->windowData;

	if(resizableWindow) {
		unsetenv("SDL_VIDEO_CENTERED");
	} else {
		setenv("SDL_VIDEO_CENTERED", "1", 1);
	}

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0) {
	}

	eventMutex = createMutex();
	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);

	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
	SDL_WM_SetCaption(windowTitle->c_str(), windowTitle->c_str());

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_JoystickEventState(SDL_ENABLE);

	int numJoysticks = SDL_NumJoysticks();

	for(int i=0; i < numJoysticks; i++) {
		SDL_JoystickOpen(i);
		input->addJoystick(i);
	}

	// Start listening to clipboard events.
	// (Yes on X11 you need to actively listen to
	//  clipboard events and respond to them)
	init_scrap();

	((OpenGLRenderer*)renderer)->initOSSpecific();
	CoreServices::getInstance()->installModule(new GLSLShaderModule());
}

void SDLCore::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel) {
	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	this->aaLevel = aaLevel;

	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,   8);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,  8);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);

	if(aaLevel > 0) {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, aaLevel); //0, 2, 4
	} else {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 0);
	}

	flags = SDL_OPENGL;

	if(fullScreen) {
		flags |= SDL_FULLSCREEN;
	}

	if(resizableWindow) {
		flags |= SDL_RESIZABLE;
	}
/*
	if(vSync) {
		flags |= SDL_DOUBLEBUF;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
	} else {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
	}
*/
	SDL_SetVideoMode(xRes, yRes, 0, flags);

	renderer->Resize(xRes, yRes);
	//CoreServices::getInstance()->getMaterialManager()->reloadProgramsAndTextures();
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);	
}

vector<Polycode::Rectangle> SDLCore::getVideoModes() {
	vector<Polycode::Rectangle> retVector;

	SDL_Rect **modes;
	modes=SDL_ListModes(NULL, SDL_FULLSCREEN);
	for(int i=0;modes[i];++i) {
		Rectangle res;
		res.w = modes[i]->w;
		res.h = modes[i]->h;
		retVector.push_back(res);
	}

	return retVector;
}

SDLCore::~SDLCore() {
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
	SDL_CreateThread(SDLThreadFunc, (void*)target);
}

unsigned int SDLCore::getTicks() {
	return SDL_GetTicks();
}

void SDLCore::enableMouse(bool newval) {
	if(newval) {
		SDL_ShowCursor(1);
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	} else {
		SDL_ShowCursor(0);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}
	Core::enableMouse(newval);
}

void SDLCore::captureMouse(bool newval) {
	if(newval) {
		SDL_WM_GrabInput(SDL_GRAB_ON);
	} else {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
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
	SDL_GL_SwapBuffers();
}

bool SDLCore::Update() {
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
			case SDL_VIDEORESIZE:
				if(resizableWindow) {
					unsetenv("SDL_VIDEO_CENTERED");
				} else {
					setenv("SDL_VIDEO_CENTERED", "1", 1);
				}
				this->xRes = event.resize.w;
				this->yRes = event.resize.h;
				SDL_SetVideoMode(xRes, yRes, 0, flags);
				renderer->Resize(xRes, yRes);	
				dispatchEvent(new Event(), EVENT_CORE_RESIZE);
			break;
			case SDL_ACTIVEEVENT:
				if(event.active.state == SDL_APPINPUTFOCUS) {
					if(event.active.gain == 1) {
						gainFocus();
					} else {
						loseFocus();
					}
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
					input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.unicode, true, getTicks());
				}
			break;
			case SDL_KEYUP:
				input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.unicode, false, getTicks());
			break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_WHEELUP) {
					input->mouseWheelUp(getTicks());
				} else if(event.button.button == SDL_BUTTON_WHEELDOWN) {
					input->mouseWheelDown(getTicks());
				} else {
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
				}
			break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_WHEELUP || event.button.button == SDL_BUTTON_WHEELDOWN) {

				} else {
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

}

void SDLCore::warpCursor(int x, int y) {
	SDL_WarpMouse(x, y);
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
		execl("/bin/cp", "/bin/cp", "-R", itemPath.c_str(), destItemPath.c_str(), (char *)0);
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

void SDLCore::resizeTo(int xRes, int yRes) {
	renderer->Resize(xRes, yRes);
}


#ifdef USE_X11
// SDL_scrap.c
// Credits to Sam Lantinga for making this
// Changes include:
// - All non-X11 stuff was removed
// - Uses the X11 CLIPBOARD atom in addition to PRIMARY
// =======================================


/* Handle clipboard text and data in arbitrary formats */

/* Miscellaneous defines */
#define PUBLIC
#define PRIVATE	static

#define X11_SCRAP

typedef Atom scrap_type;

static Display *SDL_Display;
static Window SDL_Window;
static void (*Lock_Display)(void);
static void (*Unlock_Display)(void);

#define FORMAT_PREFIX	"SDL_scrap_0x"

PRIVATE scrap_type
convert_format(int type)
{
	switch (type) {

		case T('T', 'E', 'X', 'T'):
			return XA_STRING;

		default:
		{
			char format[sizeof(FORMAT_PREFIX)+8+1];

			sprintf(format, "%s%08lx", FORMAT_PREFIX, (unsigned long)type);

			return XInternAtom(SDL_Display, format, False);
		}
	}
}

/* Convert internal data to scrap format */
	PRIVATE int
convert_data(int type, char *dst, const char *src, int srclen)
{
	int dstlen;

	dstlen = 0;
	switch (type)
	{
		case T('T', 'E', 'X', 'T'):
			if ( dst ) {
				while ( --srclen >= 0 ) {
					if ( *src == '\r' ) {
						*dst++ = '\n';
						++dstlen;
					} else {
						*dst++ = *src;
						++dstlen;
					}
					++src;
				}	 
				*dst = '\0';
				++dstlen;
			} else {
				while ( --srclen >= 0 ) {
					if ( *src == '\r' ) {
						++dstlen;
					} else {
						++dstlen;
					}
					++src;
				}
				++dstlen;
			}
		break;

		default:
			if ( dst ) {
				*(int *)dst = srclen;
				dst += sizeof(int);
				memcpy(dst, src, srclen);
			}
			dstlen = sizeof(int)+srclen;
		break;
	}
	return(dstlen);
}

/* Convert scrap data to internal format */
	PRIVATE int
convert_scrap(int type, char *dst, char *src, int srclen)
{
	int dstlen;

	dstlen = 0;
	switch (type)
	{
		case T('T', 'E', 'X', 'T'):
		{
			if ( srclen == 0 )
				srclen = strlen(src);
			if ( dst ) {
				while ( --srclen >= 0 ) {
					if ( *src == '\n' ) {
						*dst++ = '\r';
						++dstlen;
					} else {
						*dst++ = *src;
						++dstlen;
					}
					++src;
				}
				*dst = '\0';
				++dstlen;
			} else {
				while ( --srclen >= 0 ) {
					++dstlen;
					++src;
				}
				++dstlen;
			}
		}
		break;

		default:
			dstlen = *(int *)src;
			if ( dst ) {
				if ( srclen == 0 )
					memcpy(dst, src+sizeof(int), dstlen);
				else
					memcpy(dst, src+sizeof(int), srclen-sizeof(int));
			}
		break;
	}
	return dstlen;
}

/* The system message filter function -- handle clipboard messages */
PRIVATE int clipboard_filter(const SDL_Event *event);

PUBLIC int init_scrap(void)
{
	SDL_SysWMinfo info;
	int retval;

	/* Grab the window manager specific information */
	retval = -1;
	SDL_SetError("SDL is not running on known window manager");

	SDL_VERSION(&info.version);
	if ( SDL_GetWMInfo(&info) ) {
		/* Save the information for later use */
		/* * */
		if ( info.subsystem == SDL_SYSWM_X11 ) {
			SDL_Display = info.info.x11.display;
			SDL_Window = info.info.x11.window;
			Lock_Display = info.info.x11.lock_func;
			Unlock_Display = info.info.x11.unlock_func;

			/* Enable the special window hook events */
			SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
			SDL_SetEventFilter(clipboard_filter);

			retval = 0;
		} else {
			SDL_SetError("SDL is not running on X11");
		}
	}
	return(retval);
}

PUBLIC int lost_scrap(void)
{
	int retval;

	/* * */
	Lock_Display();
	retval = ( XGetSelectionOwner(SDL_Display, XA_PRIMARY) != SDL_Window );
	Unlock_Display();

	return(retval);
}

PUBLIC void put_scrap(int type, int srclen, const char *src)
{
	scrap_type format;
	int dstlen;
	char *dst;

	format = convert_format(type);
	dstlen = convert_data(type, NULL, src, srclen);

	/* * */
	dst = (char *)malloc(dstlen);
	if ( dst != NULL ) {
		Lock_Display();
		convert_data(type, dst, src, srclen);
		XChangeProperty(SDL_Display, DefaultRootWindow(SDL_Display),
				XA_CUT_BUFFER0, format, 8, PropModeReplace, (unsigned char*) dst, dstlen);
		free(dst);
		Atom XA_CLIPBOARD = XInternAtom(SDL_Display, "CLIPBOARD", 0);
		if ( lost_scrap() ) {
			XSetSelectionOwner(SDL_Display, XA_PRIMARY, SDL_Window, CurrentTime);
			XSetSelectionOwner(SDL_Display, XA_CLIPBOARD, SDL_Window, CurrentTime);
		}
		Unlock_Display();
	}

}

PUBLIC void get_scrap(int type, int *dstlen, char **dst)
{
	scrap_type format;

	*dstlen = 0;
	format = convert_format(type);

	/* * */
	{
		Window owner;
		Atom selection;
		Atom seln_type;
		int seln_format;
		unsigned long nbytes;
		unsigned long overflow;
		char *src;

		Lock_Display();
		Atom XA_CLIPBOARD = XInternAtom(SDL_Display, "CLIPBOARD", 0);
		owner = XGetSelectionOwner(SDL_Display, XA_PRIMARY);
		Unlock_Display();
		if ( (owner == None) || (owner == SDL_Window) ) {
			owner = DefaultRootWindow(SDL_Display);
			selection = XA_CUT_BUFFER0;
		} else {
			int selection_response = 0;
			SDL_Event event;

			owner = SDL_Window;
			Lock_Display();
			selection = XInternAtom(SDL_Display, "SDL_SELECTION", False);
			XConvertSelection(SDL_Display, XA_PRIMARY, format,
					selection, owner, CurrentTime);
			XConvertSelection(SDL_Display, XA_CLIPBOARD, format,
					selection, owner, CurrentTime);
			Unlock_Display();
			while ( ! selection_response ) {
				SDL_WaitEvent(&event);
				if ( event.type == SDL_SYSWMEVENT ) {
					XEvent xevent = event.syswm.msg->event.xevent;

					if ( (xevent.type == SelectionNotify) && (xevent.xselection.requestor == owner) )
						selection_response = 1;
				}
			}
		}
		Lock_Display();
		if ( XGetWindowProperty(SDL_Display, owner, selection, 0, INT_MAX/4,
					False, format, &seln_type, &seln_format,
					&nbytes, &overflow, (unsigned char **)&src) == Success ) {
			if ( seln_type == format ) {
				*dstlen = convert_scrap(type, NULL, src, nbytes);
				*dst = (char *)malloc(*dstlen);
				if ( *dst == NULL )
					*dstlen = 0;
				else
					convert_scrap(type, *dst, src, nbytes);
			}
			XFree(src);
		}
	}
	Unlock_Display();
}

PRIVATE int clipboard_filter(const SDL_Event *event)
{
	/* Post all non-window manager specific events */
	if ( event->type != SDL_SYSWMEVENT ) {
		return(1);
	}

	/* Handle window-manager specific clipboard events */
	switch (event->syswm.msg->event.xevent.type) {
		/* Copy the selection from XA_CUT_BUFFER0 to the requested property */
		case SelectionRequest: 
		{
			XSelectionRequestEvent *req;
			XEvent sevent;
			int seln_format;
			unsigned long nbytes;
			unsigned long overflow;
			unsigned char *seln_data;

			req = &event->syswm.msg->event.xevent.xselectionrequest;
			sevent.xselection.type = SelectionNotify;
			sevent.xselection.display = req->display;
			sevent.xselection.selection = req->selection;
			sevent.xselection.target = None;
			sevent.xselection.property = None;
			sevent.xselection.requestor = req->requestor;
			sevent.xselection.time = req->time;
			if ( XGetWindowProperty(SDL_Display, DefaultRootWindow(SDL_Display),
					       XA_CUT_BUFFER0, 0, INT_MAX/4, False, req->target,
					       &sevent.xselection.target, &seln_format,
					       &nbytes, &overflow, &seln_data) == Success ) {
				if ( sevent.xselection.target == req->target ) {
					if ( sevent.xselection.target == XA_STRING &&  seln_data[nbytes-1] == '\0' ) 
						--nbytes;
					XChangeProperty(SDL_Display, req->requestor, req->property,
							sevent.xselection.target, seln_format, PropModeReplace,
							seln_data, nbytes);
					sevent.xselection.property = req->property;
				}
				XFree(seln_data);
			}
			XSendEvent(SDL_Display,req->requestor,False,0,&sevent);
			XSync(SDL_Display, False);
		}
		break;
	}

	/* Post the event for X11 clipboard reading above */
	return(1);
}

#endif // USE_X11
