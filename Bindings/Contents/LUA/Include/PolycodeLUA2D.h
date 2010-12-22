#pragma once


#include <Polycode.h>
#include "PolycodeLUA2D.h"


extern "C" {	
#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
	
// Screen
	
	static int Polycore_Screen(lua_State *L) {
		Screen *screen = new Screen();
		lua_pushlightuserdata(L, (void*)screen);
		return 1;
	}
	
	static int Polycore_Screen_addChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		ScreenEntity *child = (ScreenEntity*)lua_topointer(L, 2);
		screen->addChild(child);
		return 0;
	}	

	static int Polycore_Screen_removeChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
		luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		ScreenEntity *child = (ScreenEntity*)lua_topointer(L, 2);
		screen->removeChild(child);
		return 0;
	}
	
	static int Polycore_Screen_setScreenOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Screen *screen = (Screen*)lua_topointer(L, 1);		
		float x = lua_tonumber(L, 2);
		float y = lua_tonumber(L, 3);
		screen->setScreenOffset(x,y);
		return 0;
	}	
	
	static int Polycore_Screen_getScreenOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		Vector2 offset = screen->getScreenOffset();
		lua_pushnumber(L, offset.x);
		lua_pushnumber(L, offset.y);		
		return 2;
	}	

	static int Polycore_Screen_setScreenShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
		luaL_checktype(L, 2, LUA_TSTRING);
		Screen *screen = (Screen*)lua_topointer(L, 1);
		const char *str = lua_tostring(L, 2);
		screen->setScreenShader(str);
		return 0;
	}		

	static int Polycore_Screen_getHighestZIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		lua_pushinteger(L, screen->getHighestZIndex());
		return 1;
	}	

	static int Polycore_Screen_sortChildren(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		screen->sortChildren();
		return 0;
	}				

	static int Polycore_Screen_hasFilterShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		lua_pushboolean(L, screen->hasFilterShader());
		return 1;
	}		
	
	static int Polycore_Screen_getRootEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		lua_pushlightuserdata(L, (void*)screen->getRootEntity());
		return 1;
	}
	
	static int Polycore_Screen_setEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
		luaL_checktype(L, 2, LUA_TBOOLEAN);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		bool enabledVal = lua_toboolean(L, 2);
		screen->enabled = enabledVal;
		return 0;
	}	

	static int Polycore_Screen_getEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);		
		Screen *screen = (Screen*)lua_topointer(L, 1);
		lua_pushboolean(L, screen->enabled);
		return 1;
	}		
		
	
	// Screen IMage
	static int Polycore_ScreenImage(lua_State *L) {
		ScreenImage *screenImage = new ScreenImage(lua_tostring(L, 1));
		lua_pushlightuserdata(L, (void*)screenImage);
		return 1;
	}
	
	static int Polycore_ScreenImage_setRotation(lua_State *L) {
		ScreenEntity *image = (ScreenEntity*)lua_topointer(L, 1);	
		float rotation = lua_tonumber(L, 2);
		image->setRotation(rotation);
		return 1;
	}
	
}