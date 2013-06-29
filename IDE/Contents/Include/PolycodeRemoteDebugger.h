/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "Polycode.h"
#include "PolycodeConsole.h"
#include "PolycodeProjectManager.h"

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

class DebuggerClient { 
	public:
		ServerClient *client;
};

class PolycodeRemoteDebugger : EventHandler {
	public:
		PolycodeRemoteDebugger(PolycodeProjectManager *projectManager);
		~PolycodeRemoteDebugger();

		void injectCode(String code);

		void handleEvent(Event *event);

		bool isConnected();

		void Disconnect();

		static const int EVENT_DEBUG_ERROR = 32;
		static const int EVENT_DEBUG_PRINT = 33;
		static const int EVENT_DEBUG_RESIZE = 34;
		static const int EVENT_DEBUG_REMOVE = 35;

		static const int EVENT_INJECT_CODE = 36;

		static const int EVENT_DEBUG_BACKTRACE_INFO = 37;

	protected:

		bool hasErred;

		PolycodeProjectManager *projectManager;

		Server *server;
		std::vector<DebuggerClient*> debuggerClients;

};
