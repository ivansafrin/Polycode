#pragma once
#include <Polycode.h>
extern "C" {
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
int _PolyExport luaopen_Polycode(lua_State *L);
}
