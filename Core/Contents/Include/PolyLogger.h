// @package Services

#pragma once

#include "PolyGlobals.h"
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <iostream>

#ifdef MSVC
#include <windows.h>
#endif

using std::wstring;
using std::string;

namespace Polycode {

	class _PolyExport Logger {
		public:
			Logger(){}
			~Logger(){}

			static void log(const char *format, ...);
			static void logw(const char *str);
	};
}
