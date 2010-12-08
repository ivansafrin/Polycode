/*
 *  PolyLuaEventStuff.h
 *  Poly
 *
 *  Created by Ivan Safrin on 1/27/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#ifdef _COMPILE_LUA

// Poly compilation config

extern "C"
{
#include "lua.h"
#include "lualib.h"

}

typedef struct{
	lua_State* L;
	int ref;
} SWIGLUA_REF;

extern void handlePolyLuaEvent(SWIGLUA_REF *onEvent, void *event);

#endif
