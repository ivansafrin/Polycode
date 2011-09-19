#pragma once
#include <Polycode2DPhysics.h>
extern "C" {
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
int _PolyExport luaopen_Physics2D(lua_State *L);
}
