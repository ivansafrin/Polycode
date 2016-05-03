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
#include "polycode/core/PolyLogger.h"

using namespace Polycode;

Polycode::Script::Script(const String &path) : Resource(Resource::RESOURCE_SCRIPT) {
    setResourcePath(path);
}

JSScript::JSScript(duk_context *context, const String &path) : Script(path) {
    this->context = context;
}

ScriptInstance *JSScript::callInit(Entity *entity) {
    JSScriptInstance *scriptInstance = new JSScriptInstance();
    
    if(duk_peval_file(context, getResourcePath().c_str()) != 0) {
        Logger::log("JAVASCRIPT ERROR: [%s]\n", duk_safe_to_string(context, -1));
    }
    
    duk_new(context, 0);
    
    scriptInstance->objectRef = duk_get_heapptr(context, -1);
    scriptInstance->script = this;
    
    duk_push_heapptr(context, scriptInstance->objectRef);
    duk_get_prop_string(context, -1, "init");
    duk_push_heapptr(context, scriptInstance->objectRef);
    duk_push_pointer(context, entity);
    if(duk_pcall_method(context, 1) != 0) {
        Logger::log("JAVASCRIPT ERROR: [%s]\n", duk_safe_to_string(context, -1));
    }
    duk_pop_2(context);
    return scriptInstance;
}

void JSScript::callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed) {
    duk_push_heapptr(context, ((JSScriptInstance*)instance)->objectRef);
    duk_get_prop_string(context, -1, "update");
    duk_push_heapptr(context, ((JSScriptInstance*)instance)->objectRef);
    duk_push_number(context, elapsed);
    if(duk_pcall_method(context, 1) != 0) {
        Logger::log("JAVASCRIPT ERROR: [%s]\n", duk_safe_to_string(context, -1));
    }
    duk_pop_2(context);
}

LuaScript::LuaScript(lua_State *state, const String &path) : Script(path) {

    lua_getglobal(state, "__customError");
    errH = lua_gettop(state);
    
    luaL_loadfile(state, path.c_str());
    lua_pcall(state,0,1,errH);
    tableRef = luaL_ref(state, LUA_REGISTRYINDEX);
    this->state = state;
}

ScriptInstance *LuaScript::callInit(Entity *entity) {
    LuaScriptInstance *scriptInstance = new LuaScriptInstance();
    if(tableRef != -1) {
        lua_rawgeti(state, LUA_REGISTRYINDEX, tableRef);
        
        // create a Lua entity wrapper
        lua_getglobal(state, "Entity");
        lua_pushstring(state, "__skip_ptr__");
        lua_pcall(state, 1, 1, errH);
        
        lua_pushstring(state, "__ptr");

        PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(state, sizeof(PolyBase*));
        *userdataPtr = (PolyBase*)entity;
        
        lua_settable(state, -3);
        
        lua_pcall(state, 1, 1, errH);
        scriptInstance->tableRef = luaL_ref(state, LUA_REGISTRYINDEX);
    } else {
        scriptInstance->tableRef = -1;
    }
        scriptInstance->script = this;
    return scriptInstance;
}

void LuaScript::callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed) {
    if(((LuaScriptInstance*)instance)->tableRef != -1 && tableRef != -1) {
        lua_rawgeti(state, LUA_REGISTRYINDEX, tableRef);
        lua_getfield(state, -1, "update");
        lua_rawgeti(state, LUA_REGISTRYINDEX, ((LuaScriptInstance*)instance)->tableRef);
        lua_pushnumber(state, elapsed);
        lua_pcall(state, 2, 0, errH);
    }
}
