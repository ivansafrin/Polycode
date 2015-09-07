
#pragma once

#include "stdio.h"
#include "PolyString.h"
#include "PolyObject.h"
#include "OSBasics.h"

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
