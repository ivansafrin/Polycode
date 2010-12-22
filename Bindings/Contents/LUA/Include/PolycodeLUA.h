
#pragma once


#include <Polycode.h>
#include "PolycodeLUA2D.h"

extern "C" {	
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
	
int luaopen_Polycode(lua_State *L);	
	
}
