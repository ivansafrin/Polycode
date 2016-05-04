#pragma once

extern "C" {
	#include <stdio.h>
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
} 

%HEADERS%

using namespace std;
namespace Polycode {

	class LuaEventHandler : public EventHandler {
	public:
		LuaEventHandler() : EventHandler() {}
		void handleEvent(Event *e) {
			lua_getglobal(L, "__customError");
			int errH = lua_gettop(L);
			lua_getglobal(L, "__handleEvent");
			lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)e;
			lua_pcall(L, 2, 0, errH);
			lua_settop(L, 0);
		}
		int wrapperIndex;
		lua_State *L;
	};

%BODY%

}
