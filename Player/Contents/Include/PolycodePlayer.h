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
#include "PolyGLSLShaderModule.h"
#include "OSBasics.h"

extern "C" {	
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
// #include "lapi.h"
	

using namespace Polycode;

class PolycodeDebugEvent : public Event {
public:
	PolycodeDebugEvent();
	~PolycodeDebugEvent();	

	int lineNumber;
	String errorString;
	
	int xRes;
	int yRes;
	
	static const int EVENT_ERROR = 0;
	static const int EVENT_PRINT = 1;
	static const int EVENT_RESIZE = 2;
	static const int EVENT_REMOVE = 3;
};

class PolycodePlayer : public EventDispatcher {
	
public:
	
	PolycodePlayer(String fileName, bool knownArchive);
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
	bool fullScreen;	
	
	int frameRate;
	
	void *windowData;	
	bool doneLoading;
	
	Core *core;	
	
protected:
	
	lua_State *L;		
	
	std::vector<String> loadedModules;
	
	bool _knownArchive;
	String fileToRun;
	
};
}