
#pragma once

#include "stdio.h"
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyObject.h"

#ifdef _WINDOWS
#include <time.h>
#include <io.h>
#endif

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace Polycode;

class BuildArg {
public:
	String name;
	String value;
};
