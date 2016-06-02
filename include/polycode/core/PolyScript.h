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

#pragma once

#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyString.h"

extern "C" {
#ifndef NO_LUA
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
#endif
	#include "duktape.h"
}

namespace Polycode {

	class Entity;
	class Script;
	
	class ScriptInstance {
		public:
			Script *script;
	};
	
	class Script : public Resource {
		public:
			Script(const String &path);
		
			virtual ScriptInstance *callInit(Entity *entity) = 0;
			virtual void callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed) = 0;
	};
	
#ifndef NO_LUA
	class LuaScriptInstance : public ScriptInstance {
		public:
			int tableRef;
	};
	
	class LuaScript : public Script {
		public:
			LuaScript(lua_State *state, const String &path);
		
			ScriptInstance *callInit(Entity *entity);
			void callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed);
		
		private:
			lua_State *state;
			int tableRef;
			int errH;
	};
#endif

	class JSScriptInstance : public ScriptInstance {
	public:
		void *objectRef;
	};
	
	class JSScript : public Script {
	public:
		JSScript(duk_context *context, const String &path);
		
		ScriptInstance *callInit(Entity *entity);
		void callUpdate(ScriptInstance *instance, Entity *entity, Number elapsed);
		
	private:
		void *mainObjectRef;
		duk_context *context;
	};

}
