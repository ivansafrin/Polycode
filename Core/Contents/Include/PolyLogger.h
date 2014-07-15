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
#include "PolyGlobals.h"
#include "PolyEventDispatcher.h"

namespace Polycode {

	class _PolyExport LoggerEvent : public Event {
		public:
			LoggerEvent(String message);
			virtual ~LoggerEvent();
			
			String message;
			
	};
	
	/**
	* Logs information to the console, should only be called through Logger::
	*/
	class _PolyExport Logger : public EventDispatcher {
		public:
			/**
			* Default constructor
			*/
			Logger();
			virtual ~Logger();

			/**
			* Dispatches LoggerEvent and calls Logger::log()
			* @param message String to log
			*/
			void logBroadcast(String message);

			/**
			* Logs information to the console or debug window of VS (only available if compiled as debug)
			* @param format c-strings to log, put the params into the first using the formatting of printf (reference: http://www.cplusplus.com/reference/cstdio/printf/)
			*/
			static void log(const char *format, ...);

			/**
			* Logs information through wcout
			* @param str The c-string to log
			*/
			static void logw(const char *str);

			void setLogToFile(bool val);
			bool getLogToFile();

			/**
			* @return The file that is logged to
			*/
			FILE *getLogFile();

			/**
			* @return The logger instance
			*/
			static Logger *getInstance();

	protected:
		FILE *logFile;
		bool logToFile;

	private:
		static Logger *overrideInstance;
	};
}
