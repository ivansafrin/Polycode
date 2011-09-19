#pragma once
#include <Polycode3DPhysics.h>
extern "C" {
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
int _PolyExport luaopen_Physics3D(lua_State *L);
}
