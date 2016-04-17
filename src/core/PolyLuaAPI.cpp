/*
 Copyright (C) 2016 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "polycode/core/PolyLuaAPI.h"

using namespace Polycode;

static int Lua_Entity_Roll(lua_State *L) {
    Entity *entity = (Entity*) lua_topointer(L, 1);
    Number amt = lua_tonumber(L, 2);
    if(!entity) {
        return 0;
    }
    entity->Roll(amt);
    return 0;
}

int luaopen_Polycode(lua_State *L) {
    
    static const luaL_reg entityFunctions[] =
    {
        { "Roll", Lua_Entity_Roll},
        { NULL, NULL }
    };
    
    luaL_register(L, "Entity", entityFunctions);
    return 1;
}