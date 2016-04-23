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

#include "polycode/core/PolyScript.h"
#include "polycode/core/PolyEntity.h"

using namespace Polycode;

Polycode::Script::Script(const String &path) : Resource(Resource::RESOURCE_SCRIPT) {
    setResourcePath(path);
}

JSScript::JSScript(duk_context *context, const String &path) : Script(path) {
    this->context = context;
}

ScriptInstance *JSScript::callInit(Entity *entity) {
    JSScriptInstance *scriptInstance = new JSScriptInstance();
    scriptInstance->script = this;
    return scriptInstance;
}

void JSScript::callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed) {
    
}

LuaScript::LuaScript(lua_State *state, const String &path) : Script(path) {
    luaL_loadfile(state, path.c_str());
    lua_pcall(state,0,1,0);
    tableRef = luaL_ref(state, LUA_REGISTRYINDEX);
    this->state = state;
}

ScriptInstance *LuaScript::callInit(Entity *entity) {
    lua_getglobal(state, tableName.c_str());
    lua_rawgeti(state, LUA_REGISTRYINDEX, tableRef);
    lua_getfield(state, -1, "init");
    lua_pushlightuserdata(state, entity);
    lua_pcall(state, 1, 1, 0);
    LuaScriptInstance *scriptInstance = new LuaScriptInstance();
    scriptInstance->tableRef = luaL_ref(state, LUA_REGISTRYINDEX);
    scriptInstance->script = this;
    return scriptInstance;
}

void LuaScript::callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed) {
    lua_rawgeti(state, LUA_REGISTRYINDEX, tableRef);
    lua_getfield(state, -1, "update");
    lua_rawgeti(state, LUA_REGISTRYINDEX, ((LuaScriptInstance*)instance)->tableRef);
    lua_pushnumber(state, elapsed);
    lua_pcall(state, 2, 0, 0);
}
