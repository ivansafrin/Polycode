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

#pragma once

#include <iostream>
#include <fstream>

#include "Polycode.h"
#include "PolycodeLUA.h"
#include "UILUA.h"
#include "Physics2DLUA.h"
#include "Physics3DLUA.h"
#include "PolyGLSLShaderModule.h"
#include "OSBasics.h"

extern "C" {	
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
// #include "lapi.h"	

using namespace Polycode;

typedef struct {
	unsigned int lineNumber;
	char errorMessage[256];	
	char fileName[256];
	unsigned int backTraceSize;	
} RemoteErrorData;

typedef struct {
	unsigned int lineNumber;
	char fileName[256];
} RemoteBacktraceData;

class PolycodeRemoteDebuggerClient : public EventDispatcher {
	public:
		PolycodeRemoteDebuggerClient();
		~PolycodeRemoteDebuggerClient();
		
		void handleEvent(Event *event);
		
		static const int EVENT_DEBUG_ERROR = 32;
		static const int EVENT_DEBUG_PRINT = 33;
		static const int EVENT_DEBUG_RESIZE = 34;
		static const int EVENT_DEBUG_REMOVE = 35;
		
		static const int EVENT_INJECT_CODE = 36;
		
		static const int EVENT_DEBUG_BACKTRACE_INFO = 37;
	
		Client *client;
};

class BackTraceEntry {
	public:
		String fileName;
		unsigned int lineNumber;
};

class PolycodeDebugEvent : public Event {
public:
	PolycodeDebugEvent();
	~PolycodeDebugEvent();	

	int lineNumber;
	String errorString;
	String fileName;
	
	std::vector<BackTraceEntry> backTrace;
		
	int xRes;
	int yRes;
	
	static const int EVENT_ERROR = 0;
	static const int EVENT_PRINT = 1;
	static const int EVENT_RESIZE = 2;
	static const int EVENT_REMOVE = 3;
	static const int EVENT_CLOSE = 4;
};

class PolycodePlayer : public EventDispatcher {
	
public:
	
	PolycodePlayer(String fileName, bool knownArchive, bool useDebugger=false);
	virtual ~PolycodePlayer();
	
	void runPlayer();
	
	void loadFile(const char *fileName);
	void runFile(String fileName);
		
	int report (lua_State *L, int status);
	
	void handleEvent(Event *event);
	bool Update();
	
	virtual void createCore() = 0;
	
	Core *getCore() { return core; }	
	
	int xRes;
	int yRes;
	int aaLevel;
	int anisotropyLevel;
	bool vSync;
	bool fullScreen;	
	
	int frameRate;
	
	void *windowData;	
	bool doneLoading;
	
	Core *core;	
	
	String fullPath;
	
	bool useDebugger;	
	
	bool crashed;
		
protected:

	int errH;

	Timer *debuggerTimer;
	
	PolycodeRemoteDebuggerClient *remoteDebuggerClient;
	
	lua_State *L;		
	
	
	bool doCodeInject;
	String injectCodeString;
	
	std::vector<String> loadedModules;
	
	bool _knownArchive;
	String fileToRun;
	
};
}