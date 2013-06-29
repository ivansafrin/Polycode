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

#include "PolyLogger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <iostream>

using namespace Polycode;

LoggerEvent::LoggerEvent(String message) : Event() {
	this->message = message;
}

LoggerEvent::~LoggerEvent() {

}


Logger::Logger() : EventDispatcher() {

}

Logger::~Logger() {

}

void Logger::logBroadcast(String message) {
	dispatchEvent(new LoggerEvent(message), Event::NOTIFY_EVENT);
	Logger::log(message.c_str());
}

void Logger::logw(const char *str) {
	std::wcout << str << std::endl;
}

void Logger::log(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

#ifdef MSVC
#ifdef _DEBUG

	char buffer[4096];
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	WCHAR wbuf[4096];
	int i = 0;
	while(buffer[i] != '\0') {
		wbuf[i] = (WCHAR)buffer[i];
		++i;
	}
	wbuf[i] = L'\0';
	OutputDebugString(wbuf);
	
#endif
#endif

}
