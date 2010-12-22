/*
 *  TauTestApp.h
 *  tauTest
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include <iostream>
#include <fstream>

#include "Polycode.h"
#include "PolycodeLUA.h"

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
	
	bool _knownArchive;
	String fileToRun;
	
};
}