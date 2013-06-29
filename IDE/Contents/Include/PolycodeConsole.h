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

#include "PolycodeUI.h"
#include "Polycode.h"
#include "PolycodeProject.h"

using namespace Polycode;

class PolycodeRemoteDebugger;

class BackTraceEvent : public Event {
	public:
		BackTraceEvent() : Event() { eventType = "BackTraceEvent"; };
		~BackTraceEvent() {}

		static const int EVENT_BACKTRACE_SELECTED = 0;

		String fileName;
		unsigned int lineNumber;
		PolycodeProject *project;
};

class BackTraceEntry : public UIElement {
	public:
		BackTraceEntry(String fileName, int lineNumber, PolycodeProject *project);
		~BackTraceEntry();

		void Select();
		void Deselect();

		void handleEvent(Event *event);

		void Resize(Number width, Number height);

	protected:

		PolycodeProject *project;

		String fileName;
		unsigned int lineNumber;

		ScreenShape *labelBg;
		ScreenLabel *label;
};

class BackTraceWindow : public UIElement {
	public:
		BackTraceWindow();
		~BackTraceWindow();

		void handleEvent(Event *event);

		void addBackTrace(String fileName, int lineNumber, PolycodeProject *project);

		void clearBackTraces();

		void Resize(Number width, Number height);

		void adjustEntries();

	protected:
		ScreenShape *labelBg;
		std::vector<BackTraceEntry*> entries;

};


class ConsoleWindow : public UIElement {
	public:
		ConsoleWindow();

		void Resize(Number width, Number height);

		UITextInput *debugTextInput;
		UITextInput *consoleTextInput;

		UIImageButton *clearButton;
		UIImageButton *hideConsoleButton;

		ScreenShape *labelBg;
};

class PolycodeConsole : public UIElement {
	public:
		PolycodeConsole();
		~PolycodeConsole();

		void _print(String msg);

		void handleEvent(Event *event);

		void setDebugger(PolycodeRemoteDebugger *debugger);

		static void print(String msg);

		static void addBacktrace(String fileName, int lineNumber, PolycodeProject *project);

		static void clearBacktraces();
		void _clearBacktraces();


		void applyTheme();

		void _addBacktrace(String fileName, int lineNumber, PolycodeProject *project);

		void Resize(Number width, Number height);

		static void setInstance(PolycodeConsole *newInstance);

		BackTraceWindow *backtraceWindow;
		ConsoleWindow  *consoleWindow;

	protected:
		UIHSizer *backtraceSizer;

		PolycodeRemoteDebugger *debugger;
		static PolycodeConsole *instance;

		UITextInput *debugTextInput;
		UITextInput *consoleTextInput;

	private:
		std::vector<String> consoleHistory;
		int consoleHistoryPosition;
		int consoleHistoryMaxSize;

};
