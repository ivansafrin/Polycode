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
#ifdef _MSC_VER
#include <windows.h>
#endif
#include "PolyLogger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace Polycode;

Logger* Logger::overrideInstance = NULL;

LoggerEvent::LoggerEvent(String message) : Event() {
	this->message = message;
}

LoggerEvent::~LoggerEvent() {

}


Logger::Logger() : EventDispatcher() {
	logToFile = false;
    logFile = NULL;
}

Logger::~Logger() {
    if(logFile) {
        fclose(logFile);
    }
    overrideInstance = NULL;
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
	
	if (Logger::getInstance()->getLogToFile()){
		if (Logger::getInstance()->getLogFile()){
			va_start(args, format);
			vfprintf(Logger::getInstance()->getLogFile(), format, args);
            fflush(Logger::getInstance()->getLogFile());
			va_end(args);
		} else {
			time_t t = time(NULL);
			char mbstr[100];
			if (strftime(mbstr, sizeof(mbstr), "%y_%m_%d.log", localtime(&t))) {
				Logger::getInstance()->setLogFile(fopen((const char*)mbstr, "w"));
			} else {
				Logger::getInstance()->setLogFile(fopen("poly.log", "w"));
			}
		}
	}

#ifdef _MSC_VER
#ifdef _DEBUG

	char buffer[4096];
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	wchar_t wbuf[4096];
	int i = 0;
	while(buffer[i] != '\0') {
		wbuf[i] = (wchar_t)buffer[i];
		++i;
	}
	wbuf[i] = L'\0';
	OutputDebugString(wbuf);
	
#endif
#endif

}

void Logger::setLogToFile(bool val){
	if (!logToFile && val){
		time_t t = time(NULL);
		char mbstr[100];
		if (strftime(mbstr, sizeof(mbstr), "%y_%m_%d.log", localtime(&t))) {
			logFile = fopen((const char*)mbstr, "w");
		} else {
			logFile = fopen("poly.log", "w");
		}
	}

	logToFile = val;
}

void Logger::setLogFile(FILE *f){
	logFile = f;
}

bool Logger::getLogToFile(){
	return logToFile;
}

FILE *Logger::getLogFile(){
	return logFile;
}

Logger *Logger::getInstance(){
	if (overrideInstance) {
		return overrideInstance;
	}

	overrideInstance = new Logger;
	return overrideInstance;
}