/*
 *  LuaTestApp.cpp
 *  tauTest
 *
 *  Created by Ivan Safrin on 1/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolycodePlayer.h"

extern "C" {	
//	extern int luaopen_Tau(lua_State* L); // declare the wrapped module
		//	loadFileIntoState(L, "Polycode Player.app/Contents/Resources/API/class.lua");
	
	int MyLoader(lua_State* pState)
	{		
		std::string module = lua_tostring(pState, 1);
		module += ".lua";
		
		string defaultPath = "Contents/Resources/API/";
		defaultPath.append(module);
		
		const char* fullPath = module.c_str();		
		printf("Loading custom class: %s\n", module.c_str());
		OSFILE *inFile = OSBasics::open(module, "r");	
		
		if(!inFile) {
			inFile =  OSBasics::open(defaultPath, "r");	
		}
		
		if(inFile) {
			OSBasics::seek(inFile, 0, SEEK_END);	
			long progsize = OSBasics::tell(inFile);
			OSBasics::seek(inFile, 0, SEEK_SET);
			char *buffer = (char*)malloc(progsize+1);
			memset(buffer, 0, progsize+1);
			OSBasics::read(buffer, progsize, 1, inFile);
			luaL_loadbuffer(pState, (const char*)buffer, progsize, fullPath);		
			//free(buffer);
			OSBasics::close(inFile);	
		} else {
			std::string err = "\n\tError - Could could not find ";
			err += module;
			err += ".";			
			lua_pushstring(pState, err.c_str());			
		}
		return 1;
	}
	
	static int debugPrint(lua_State *L)
	{
		const char *msg = lua_tostring(L, 1);
		PolycodeDebugEvent *event = new PolycodeDebugEvent();			
		if(msg)
			event->errorString = string(msg);
		else
			event->errorString = string("<invalid string>");
		
		Logger::log(">> %s\n", event->errorString.c_str());
		PolycodePlayer *player = (PolycodePlayer*)CoreServices::getInstance()->getCore()->getUserPointer();
		player->dispatchEvent(event, PolycodeDebugEvent::EVENT_PRINT);
		return 0;
	}	
	
	int PolycodePlayer::report (lua_State *L, int status) {
		const char *msg;
			
		printf("Error status: %d\n", status);
		if (status) {
			msg = lua_tostring(L, -1);
			if (msg == NULL) msg = "(error with no message)";
			printf("status=%d, %s\n", status, msg);
			lua_pop(L, 1);
			
			vector<String> info = String(msg).split(":");
			
			PolycodeDebugEvent *event = new PolycodeDebugEvent();			
			if(info.size() > 2) {
				event->errorString = info[2];
				event->lineNumber = atoi(info[1].c_str());
			} else {
				event->errorString = string(msg);
				event->lineNumber = 0;
			}
			dispatchEvent(event, PolycodeDebugEvent::EVENT_ERROR);
			
		}
		return status;
	}	
	
	void PolycodePlayer::runFile(String fileName) {
		
		printf("Running %s\n", fileName.c_str());
		
		L=lua_open();
		
		/*
		 luaopen_base(L);	// load basic libs (eg. print)
		 luaopen_math(L);
		 luaopen_table(L);
		 luaopen_package(L);
		 */
		luaL_openlibs(L);
		
		luaopen_Polycode(L);
		//luaopen_Tau(L);	// load the wrappered module
		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "package");	// push "package"
		lua_getfield(L, -1, "loaders");					// push "package.loaders"
		lua_remove(L, -2);								// remove "package"
		
		// Count the number of entries in package.loaders.
		// Table is now at index -2, since 'nil' is right on top of it.
		// lua_next pushes a key and a value onto the stack.
		int numLoaders = 0;
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) 
		{
			lua_pop(L, 1);
			numLoaders++;
		}
		
		lua_pushinteger(L, numLoaders + 1);
		lua_pushcfunction(L, MyLoader);
		lua_rawset(L, -3);
		
		// Table is still on the stack.  Get rid of it now.
		lua_pop(L, 1);		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "class");		
		lua_call(L, 1, 0);

		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "Polycode");		
		lua_call(L, 1, 0);		
		
		lua_getfield(L, LUA_GLOBALSINDEX, "require");
		lua_pushstring(L, "defaults");		
		lua_call(L, 1, 0);
		
		
//		String prepend = "";
		//string prepend = "for k,v in pairs(Tau) do _G[k]=v end for k,v in pairs(math) do _G[k]=v end for k,v in pairs(table) do _G[k]=v end _G[\"count\"]=_G[\"getn\"] RESOURCE_MANAGER = CoreServices_getInstance():getResourceManager() CORE = CoreServices_getInstance():getCore() INPUT = CORE:getInput() RENDERER = CoreServices_getInstance():getRenderer() listener = EventHandler() listener.onEvent = function(e) inputEvent = CoreInput_createEvent(e) if e:getEventCode() == EVENT_MOUSEUP then if onMouseUp ~= nil then onMouseUp(inputEvent.mousePosition.x, inputEvent.mousePosition.y, inputEvent.mouseButton) end end if e:getEventCode() == EVENT_MOUSEDOWN then if onMouseDown ~= nil then onMouseDown(inputEvent.mousePosition.x, inputEvent.mousePosition.y, inputEvent.mouseButton) end end if e:getEventCode() == EVENT_MOUSEMOVE then if onMouseMove ~= nil then onMouseMove(inputEvent.mousePosition.x, inputEvent.mousePosition.y) end end if e:getEventCode() == EVENT_KEYDOWN then if onKeyDown ~= nil then onKeyDown(inputEvent:keyCode()) end end if e:getEventCode() == EVENT_KEYUP then if onKeyUp ~= nil then onKeyUp(inputEvent:keyCode()) end end end INPUT:addEventListener(listener, EVENT_KEYDOWN) INPUT:addEventListener(listener, EVENT_KEYUP) INPUT:addEventListener(listener, EVENT_MOUSEDOWN) INPUT:addEventListener(listener, EVENT_MOUSEMOVE) INPUT:addEventListener(listener, EVENT_MOUSEUP)";
//		String prepend = "for k,v in pairs(math) do _G[k]=v end for k,v in pairs(table) do _G[k]=v end _G[\"count\"]=_G[\"getn\"] RESOURCE_MANAGER = Tau.CoreServices_getInstance():getResourceManager() CORE = Tau.CoreServices_getInstance():getCore() FONT_MANAGER = Tau.CoreServices_getInstance():getFontManager() INPUT = CORE:getInput() RENDERER = Tau.CoreServices_getInstance():getRenderer() listener = Tau.EventHandler() listener.onEvent = function(e) inputEvent = Tau.CoreInput_createEvent(e) if e:getEventCode() == Tau.EVENT_MOUSEUP then if onMouseUp ~= nil then onMouseUp(inputEvent.mousePosition.x, inputEvent.mousePosition.y, inputEvent.mouseButton) end end if e:getEventCode() == Tau.EVENT_MOUSEDOWN then if onMouseDown ~= nil then onMouseDown(inputEvent.mousePosition.x, inputEvent.mousePosition.y, inputEvent.mouseButton) end end if e:getEventCode() == Tau.EVENT_MOUSEMOVE then if onMouseMove ~= nil then onMouseMove(inputEvent.mousePosition.x, inputEvent.mousePosition.y) end end if e:getEventCode() == Tau.EVENT_KEYDOWN then if onKeyDown ~= nil then onKeyDown(inputEvent:keyCode()) end end if e:getEventCode() == Tau.EVENT_KEYUP then if onKeyUp ~= nil then onKeyUp(inputEvent:keyCode()) end end end INPUT:addEventListener(listener, Tau.EVENT_KEYDOWN) INPUT:addEventListener(listener, Tau.EVENT_KEYUP) INPUT:addEventListener(listener, Tau.EVENT_MOUSEDOWN) INPUT:addEventListener(listener, Tau.EVENT_MOUSEMOVE) INPUT:addEventListener(listener, Tau.EVENT_MOUSEUP) ";
		
//		String prepend2 = "  local u = {}  function u.wrongarg(n,expected,got)   return 'arg '..n..' expected to be '..expected..' (got '..tostring(got)..')' end  local wrongarg = u.wrongarg  function u.isname(name)   return type(name)=='string' and string.find(name,'^[_%a][_%w]*$') end  local isname = u.isname  function u.assert(value,errmsg,...)   if value then     return value   else     if type(errmsg)=='nil' then       error('assertion failed!',2)     elseif type(errmsg)=='string' then       error(errmsg,2)     else       error(errmsg(...),2)     end   end end  local assert = u.assert  function u.fwrongarg(...)   return function(...)   return wrongarg(...)   end end  local fwrongarg = u.fwrongarg     local INFO = '__info'   function u.isobject(o)   return type(o)=='table' and rawget(o,INFO) end  local isobject = u.isobject   local METAMETHODS = {   '__tostring',   '__add',   '__sub',   '__mul',   '__div',   '__pow',   '__lt',   '__le',   '__eq',   '__call',   '__unm',   '__concat',   '__newindex', }   local metatable = {}  for _, name in ipairs(METAMETHODS) do   local name = name   metatable[name] = function(...)     local arg={...} local a, b = unpack(arg)     local f     if isobject(a) then       f = a[name]     end     if not f and isobject(b) then       f = b[name]     end     if not f then     local name = name..'__'     if isobject(a) then       f = a[name]     end     if not f and isobject(b) then       f = b[name]     end     end     assert(f, function()                  local class = rawget(a,INFO).__class                  local cname = rawget(class,INFO).__name                  return 'meta-method not found: '..cname..':'..name                end)     return f(...)   end end   local function table2object(t)   assert(type(t)=='table', fwrongarg(1,'table',t))   local info = {}   rawset(t,INFO,info)   setmetatable(t,metatable)    local p = newproxy(true)   local mp = getmetatable(p)   function mp:__gc()     if rawget(t,INFO) == info then       t:finalize()     end   end   rawget(t,INFO).__proxy = p    return t end  local function object2table(o)   assert(isobject(o), fwrongarg(1,'object',o))   setmetatable(o,nil)   rawset(o,INFO,nil)   return o end  local function givename(o,name)   assert(isobject(o), fwrongarg(1,'object',o))   assert(isname(name), fwrongarg(2,'name',name))   rawget(o,INFO).__name = name   getfenv(2)[name] = o end  local function setclass(o,class)   assert(isobject(o), fwrongarg(1,'object',o))   assert(isobject(class), fwrongarg(2,'object',class))   rawget(o,INFO).__class = class end  local function setsuper(class,superclass)   assert(isobject(class), fwrongarg(1,'object',class))   assert(isobject(superclass), fwrongarg(2,'object',superclass))   rawget(class,INFO).__super = superclass end  local function object2class(o,name)   assert(isobject(o), fwrongarg(1,'object',o))   assert(isname(name), fwrongarg(2,'name',name))   givename(o,name)   rawget(o,INFO).__methods = {}   rawget(o,INFO).__isclass = true   rawget(o,INFO).__cmethods = {} end  local function findmethod(class,name,iscmethod)   local storage = iscmethod and '__cmethods' or '__methods'   while class do     local info = rawget(class,INFO)     value = info[storage][name]     if value ~= nil then       return value     end     class = info.__super   end end    function metatable:__index(name)   local value    if rawget(self,INFO).__isclass then     value = findmethod(self,name,true)     if value ~= nil then       return value     end   end    local class = rawget(self,INFO).__class   value = findmethod(class,name)   if value ~= nil then     return value   end    if name ~= '__index' and name ~= '__index__' then     local index = self.__index or self.__index__      if index then       value = index(self,name)       if value ~= nil then         return value       end     end   end end   local _Object = table2object{} object2class(_Object,\"Object\")    local _Class = table2object{} object2class(_Class,\"Class\")   setclass(Object,Class) setclass(Class,Class) setsuper(Class,Object)   local function makesupermethod(self,name,iscmethod)   return function(...)     local method     local classinfo     if iscmethod then       classinfo = rawget(self,INFO)     else       local class = rawget(self,INFO).__class       classinfo = rawget(class,INFO)     end     local super = classinfo.__super     if super then       method = findmethod(super,name,iscmethod)     end     assert(method, \"no super method for \"..classinfo.__name..\":\"..name)     return method(self,...)   end end  local methodsmeta = {}  function methodsmeta:__call(object,...)   local env = getfenv(self.__f)   local metafenv = {     __newindex = env,     __index = env,   }   local fenv = {     super = makesupermethod(object,self.__name,self.__iscmethod),   }   setmetatable(fenv,metafenv)   setfenv(self.__f,fenv)   local result = {self.__f(object,...)}   setfenv(self.__f,env)   return unpack(result) end  local function storemethod(storage,name,iscmethod,method)   if type(method) == 'function' then     local t = {       __name = name,       __f = method,       __iscmethod = iscmethod,     }     setmetatable(t,methodsmeta)     storage[name] = t   else     storage[name] = method   end end  rawget(Class,INFO).__methods.__newindex =   function(self,name,method)	     storemethod(rawget(self,INFO).__methods,name,false,method)   end   function Class:__call__(...)   local instance = self:new(...)   instance:initialize(...)   instance.__cbody = nil   local constructor = instance[rawget(self,INFO).__name]   if constructor ~= nil then   	constructor(instance, ...)   	constructor = nil   end   return instance end  function Class:initialize(name,superclass)   assert(isname(name), fwrongarg(1,'name',name))   object2class(self,name)   superclass = superclass or Object   assert(isobject(superclass), fwrongarg(2,'object',superclass))   setsuper(self,superclass or Object) end  function Class:name()   return rawget(self,INFO).__name end  function Class:super()   return rawget(self,INFO).__super end  function Class:classtable()   local t = {}   local mt = {}   function mt.__newindex(_,name,method)     storemethod(rawget(self,INFO).__cmethods,name,true,method)   end   setmetatable(t,mt)   return t end  function Class:__tostring__()   return self:name() end  function Class:derives(class)   local superclass = self:super()   if superclass then     return superclass == class or superclass:derives(class)   end end  function Class:adopt(t,initialize,...)   assert(type(t)=='table', wrongarg(1,'table',t))   local o = table2object(t)   setclass(o,self)   if initialize then     o:initialize(unpack(arg))   end   return o end   local Objectclass = Object:classtable()  function Objectclass:new()   local o = table2object{}   setclass(o,self)   return o end   function Object:initialize() end  function Object:finalize() end  function Object:class()   return rawget(self,INFO).__class end  function Object:__eq__(other)   return rawequal(self,other) end  function Object:__newindex__(name,value)   if self.__set_callback(self,name,value) == true then   	return   end   rawset(self,name,value) end  function Object:instanceof(class)   return self:class() == class end  function Object:__set_callback(name,value) 	return false end  function Object:inherits(class)   local _class = self:class()   return _class == class or _class:derives(class) end  function Object:__tostring__()   return 'instance of '..self:class():name() end  function Object:__concat__(other)   if isobject(self) then     self = tostring(self)   elseif isobject(other) then     other = tostring(other)   end   return self..other end  function Object:totable(finalize)   if finalize then     self:finalize()   end   setmetatable(self,nil)   local info = rawget(self,INFO)   rawset(self,INFO,nil)   return self, info end   function class(name)   assert(isname(name), fwrongarg(1,'name',name))   local _class = Class(name)   return function(superclass)     assert(isobject(superclass), fwrongarg(1,'object',superclass))     setsuper(_class,superclass)   end end  classu = u ";
			
//		String prepend3 = "  function print(val) 	debugPrint(tostring(val)) end  Polygon = Tau.Polygon Vertex = Tau.Vertex  PI = Tau.PI RADIANS = Tau.RADIANS TODEGREES = Tau.TODEGREES TORADIANS = Tau.TORADIANS  BLEND_MODE_NORMAL = Tau.BLEND_MODE_NORMAL BLEND_MODE_LIGHTEN = Tau.BLEND_MODE_LIGHTEN BLEND_MODE_COLOR = Tau.BLEND_MODE_COLOR  EVENT_MOUSEOVER = Tau.EVENT_MOUSEOVER EVENT_MOUSEOUT = Tau.EVENT_MOUSEOUT EVENT_TRIGGER = Tau.EVENT_TRIGGER  SHAPE_RECT = Tau.SHAPE_RECT SHAPE_CIRCLE = Tau.SHAPE_CIRCLE SHAPE_CIRCLE_OUTLINE = Tau.SHAPE_CIRCLE_OUTLINE SHAPE_CUSTOM = Tau.SHAPE_CUSTOM  POSITION_TOPLEFT = Tau.POSITION_TOPLEFT POSITION_CENTER = Tau.POSITION_CENTER  MOUSE_BUTTON1 = Tau.MOUSE_BUTTON1 MOUSE_BUTTON2 = Tau.MOUSE_BUTTON2 MOUSE_BUTTON3 = Tau.MOUSE_BUTTON3  ENTITY_RECT = Tau.ENTITY_RECT ENTITY_CIRCLE = Tau.ENTITY_CIRCLE ENTITY_STATICRECT = Tau.ENTITY_STATICRECT  TYPE_BOX = Tau.TYPE_BOX TYPE_PLANE = Tau.TYPE_PLANE TYPE_SPHERE = Tau.TYPE_SPHERE  QUAD_MESH = Tau.QUAD_MESH TRI_MESH = Tau.TRI_MESH TRIFAN_MESH = Tau.TRIFAN_MESH TRISTRIP_MESH = Tau.TRISTRIP_MESH LINE_MESH = Tau.LINE_MESH  AREA_LIGHT = Tau.AREA_LIGHT SPOT_LIGHT = Tau.SPOT_LIGHT  CONTINUOUS_EMITTER = Tau.CONTINUOUS_EMITTER TRIGGERED_EMITTER = Tau.TRIGGERED_EMITTER CLOUD_EMITTER = Tau.CLOUD_EMITTER  BILLBOARD_PARTICLE = Tau.BILLBOARD_PARTICLE MESH_PARTICLE = Tau.MESH_PARTICLE  TAUK_BACKSPACE	= Tau.TAUK_BACKSPACE	 TAUK_TAB	= Tau.TAUK_TAB	 TAUK_CLEAR	= Tau.TAUK_CLEAR	 TAUK_RETURN	= Tau.TAUK_RETURN	 TAUK_PAUSE	= Tau.TAUK_PAUSE	 TAUK_ESCAPE	= Tau.TAUK_ESCAPE	 TAUK_SPACE	= Tau.TAUK_SPACE	 TAUK_EXCLAIM	= Tau.TAUK_EXCLAIM	 TAUK_QUOTEDBL	= Tau.TAUK_QUOTEDBL	 TAUK_HASH	= Tau.TAUK_HASH	 TAUK_DOLLAR	= Tau.TAUK_DOLLAR	 TAUK_AMPERSAND	= Tau.TAUK_AMPERSAND	 TAUK_QUOTE	= Tau.TAUK_QUOTE	 TAUK_LEFTPAREN	= Tau.TAUK_LEFTPAREN	 TAUK_RIGHTPAREN	= Tau.TAUK_RIGHTPAREN	 TAUK_ASTERISK	= Tau.TAUK_ASTERISK	 TAUK_PLUS	= Tau.TAUK_PLUS	 TAUK_COMMA	= Tau.TAUK_COMMA	 TAUK_MINUS	= Tau.TAUK_MINUS	 TAUK_PERIOD	= Tau.TAUK_PERIOD	 TAUK_SLASH	= Tau.TAUK_SLASH	 TAUK_0		= Tau.TAUK_0		 TAUK_1		= Tau.TAUK_1		 TAUK_2		= Tau.TAUK_2		 TAUK_3		= Tau.TAUK_3		 TAUK_4		= Tau.TAUK_4		 TAUK_5		= Tau.TAUK_5		 TAUK_6		= Tau.TAUK_6		 TAUK_7		= Tau.TAUK_7		 TAUK_8		= Tau.TAUK_8		 TAUK_9		= Tau.TAUK_9		 TAUK_COLON	= Tau.TAUK_COLON	 TAUK_SEMICOLON	= Tau.TAUK_SEMICOLON	 TAUK_LESS	= Tau.TAUK_LESS	 TAUK_EQUALS	= Tau.TAUK_EQUALS	 TAUK_GREATER	= Tau.TAUK_GREATER	 TAUK_QUESTION	= Tau.TAUK_QUESTION	 TAUK_AT		= Tau.TAUK_AT		  TAUK_LEFTBRACKET= Tau.TAUK_LEFTBRACKET TAUK_BACKSLASH	= Tau.TAUK_BACKSLASH	 TAUK_RIGHTBRACKET= Tau.TAUK_RIGHTBRACKET TAUK_CARET	= Tau.TAUK_CARET	 TAUK_UNDERSCORE	= Tau.TAUK_UNDERSCORE	 TAUK_BACKQUOTE	= Tau.TAUK_BACKQUOTE	 TAUK_a		= Tau.TAUK_a		 TAUK_b		= Tau.TAUK_b		 TAUK_c		= Tau.TAUK_c		 TAUK_d		= Tau.TAUK_d		 TAUK_e		= Tau.TAUK_e		 TAUK_f		= Tau.TAUK_f		 TAUK_g		= Tau.TAUK_g		 TAUK_h		= Tau.TAUK_h		 TAUK_i		= Tau.TAUK_i		 TAUK_j		= Tau.TAUK_j		 TAUK_k		= Tau.TAUK_k		 TAUK_l		= Tau.TAUK_l		 TAUK_m		= Tau.TAUK_m		 TAUK_n		= Tau.TAUK_n		 TAUK_o		= Tau.TAUK_o		 TAUK_p		= Tau.TAUK_p		 TAUK_q		= Tau.TAUK_q		 TAUK_r		= Tau.TAUK_r		 TAUK_s		= Tau.TAUK_s		 TAUK_t		= Tau.TAUK_t		 TAUK_u		= Tau.TAUK_u		 TAUK_v		= Tau.TAUK_v		 TAUK_w		= Tau.TAUK_w		 TAUK_x		= Tau.TAUK_x		 TAUK_y		= Tau.TAUK_y		 TAUK_z		= Tau.TAUK_z		 TAUK_DELETE	= Tau.TAUK_DELETE	 		 TAUK_KP0	= Tau.TAUK_KP0	 TAUK_KP1	= Tau.TAUK_KP1	 TAUK_KP2	= Tau.TAUK_KP2	 TAUK_KP3	= Tau.TAUK_KP3	 TAUK_KP4	= Tau.TAUK_KP4	 TAUK_KP5	= Tau.TAUK_KP5	 TAUK_KP6	= Tau.TAUK_KP6	 TAUK_KP7	= Tau.TAUK_KP7	 TAUK_KP8	= Tau.TAUK_KP8	 TAUK_KP9	= Tau.TAUK_KP9	 TAUK_KP_PERIOD	= Tau.TAUK_KP_PERIOD	 TAUK_KP_DIVIDE	= Tau.TAUK_KP_DIVIDE	 TAUK_KP_MULTIPLY= Tau.TAUK_KP_MULTIPLY TAUK_KP_MINUS	= Tau.TAUK_KP_MINUS	 TAUK_KP_PLUS	= Tau.TAUK_KP_PLUS	 TAUK_KP_ENTER	= Tau.TAUK_KP_ENTER	 TAUK_KP_EQUALS	= Tau.TAUK_KP_EQUALS	 		 TAUK_UP		= Tau.TAUK_UP		 TAUK_DOWN	= Tau.TAUK_DOWN	 TAUK_RIGHT	= Tau.TAUK_RIGHT	 TAUK_LEFT	= Tau.TAUK_LEFT	 TAUK_INSERT	= Tau.TAUK_INSERT	 TAUK_HOME	= Tau.TAUK_HOME	 TAUK_END	= Tau.TAUK_END	 TAUK_PAGEUP	= Tau.TAUK_PAGEUP	 TAUK_PAGEDOWN	= Tau.TAUK_PAGEDOWN	 		 TAUK_F1		= Tau.TAUK_F1		 TAUK_F2		= Tau.TAUK_F2		 TAUK_F3		= Tau.TAUK_F3		 TAUK_F4		= Tau.TAUK_F4		 TAUK_F5		= Tau.TAUK_F5		 TAUK_F6		= Tau.TAUK_F6		 TAUK_F7		= Tau.TAUK_F7		 TAUK_F8		= Tau.TAUK_F8		 TAUK_F9		= Tau.TAUK_F9		 TAUK_F10	= Tau.TAUK_F10	 TAUK_F11	= Tau.TAUK_F11	 TAUK_F12	= Tau.TAUK_F12	 TAUK_F13	= Tau.TAUK_F13	 TAUK_F14	= Tau.TAUK_F14	 TAUK_F15	= Tau.TAUK_F15	 		 TAUK_NUMLOCK	= Tau.TAUK_NUMLOCK	 TAUK_CAPSLOCK	= Tau.TAUK_CAPSLOCK	 TAUK_SCROLLOCK	= Tau.TAUK_SCROLLOCK	 TAUK_RSHIFT	= Tau.TAUK_RSHIFT	 TAUK_LSHIFT	= Tau.TAUK_LSHIFT	 TAUK_RCTRL	= Tau.TAUK_RCTRL	 TAUK_LCTRL	= Tau.TAUK_LCTRL	 TAUK_RALT	= Tau.TAUK_RALT	 TAUK_LALT	= Tau.TAUK_LALT	 TAUK_RMETA	= Tau.TAUK_RMETA	 TAUK_LMETA	= Tau.TAUK_LMETA	 TAUK_LSUPER	= Tau.TAUK_LSUPER TAUK_RSUPER	= Tau.TAUK_RSUPER TAUK_MODE	= Tau.TAUK_MODE TAUK_COMPOSE	= Tau.TAUK_COMPOSE 		 TAUK_HELP	= Tau.TAUK_HELP	 TAUK_PRINT	= Tau.TAUK_PRINT	 TAUK_SYSREQ	= Tau.TAUK_SYSREQ	 TAUK_BREAK	= Tau.TAUK_BREAK	 TAUK_MENU	= Tau.TAUK_MENU	 TAUK_POWER	= Tau.TAUK_POWER TAUK_EURO	= Tau.TAUK_EURO	 TAUK_UNDO	= Tau.TAUK_UNDO	    class \"EventHandler\"  function EventHandler:EventHandler() 	if self.__cbody == nil then 		self.__cbody = Tau.EventHandler() 	end end  function EventHandler:handleEvent(event) 	self.__cbody:handleEvent(event.__cbody) end  class \"EventDispatcher\"  function EventDispatcher:EventDispatcher() 	if self.__cbody == nil then 		self.__cbody = Tau.EventDispatcher() 	end end   function EventDispatcher:addEventListener(eventCode, callback) 	if self.__handlers == nil then 		self.__handlers = {} 		self.__callbacks = {} 		self.__numHandlers = 0 	end  	local handler = Tau.EventHandler() 	self.__callbacks[self.__numHandlers] = callback 	self.__handlers[self.__numHandlers] = handler 	self.__numHandlers = self.__numHandlers + 1  	handler.onEvent = function(event) 		for i=0,count(self.__handlers) do 			if self.__handlers[i] == handler then 				self.__callbacks[i](event) 			end 		end 	end  	self.__cbody:addEventListener(handler, eventCode) end  function EventDispatcher:removeAllListeners() 	self.__handlers = {} 	self.__callbacks = {}	 	self.__numHandlers = 0 	self.__cbody:removeAllHandlers() end   function EventDispatcher:removeEventListener(eventCode, listener) 		for i=0,count(self.__callbacks) do 			if self.__callbacks[i] == listener then 				self.__cbody:removeEventListener(self.__handlers[i], eventCode) 				return 			end 		end end   function EventDispatcher:dispatchEvent(event) 	self.__cbody:dispatchEventNoDelete(event.__cbody, event.__cbody:getEventCode()) end  class \"Event\"   function Event:Event(eventCode) 	self.__cbody = Tau.Event(eventCode) end  function Event:finalize() 	self.__cbody = nil end   class \"Font\"   function Font:Font(path) 	if self.__cbody == nil then 		self.__cbody = Tau.Font(path) 	end end  class \"Timer\" (EventDispatcher)   function Timer:Timer(msecs, triggerMode) 	self.__cbody = Tau.Timer(triggerMode, msecs)	 	self:EventDispatcher() end  function Timer:Pause(val) 	self.__cbody:Pause(val) end   function Timer:getElapsed() 	return self.__cbody:getElapsedf() end  function Timer:Reset() 	return self.__cbody:Reset() end    class \"Screen\" (EventDispatcher)   function Screen:Screen() 	if self.__cbody == nil then 		self.__cbody = Tau.Screen() 	end 	self.__children = {} 	self.rootEntity = ScreenEntity() 	self.rootEntity.__cbody = self.__cbody:getRootEntity() 	self.__numChildren = 0 	self.localShaderBindings = {} 	self:EventDispatcher()	 end   function Screen:getRootEntity() 	return rootEntity end    function Screen:addChild(child) 	self.__children[self.__numChildren] = child 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addChild(child.__cbody) 	return child end   function Screen:removeChild(child) 	self.__cbody:removeChild(child.__cbody) 	for i=0,count(self.__children) do 		if self.__children[i] == child then 			self.__children[i] = nil 		end 	end 	return child end  function Screen:getEntityByCBody(cbody) 	for i=0,count(self.__children) do 		local child = self.__children[i] 		if self.__cbody:Lua_EntitiesEqual(cbody, child.__cbody) == true then 			return self.__children[i] 		end 	end 	return nil	 end   function Screen:getEntityAt(x,y) 	local cbody = self.__cbody:getEntityAt(x,y) 	return self:getEntityByCBody(cbody) end   function Screen:getScreenOffset() 	local offset = self.__cbody:getScreenOffset() 	return Vector2(offset.x, offset.y) end   function Screen:setScreenShader(shaderName) 	self.__cbody:setScreenShader(shaderName) 	local numShaders = self.__cbody:getNumShaderBindings() 	for i=0,numShaders-1 do 		local shaderBinding = ShaderBinding() 		shaderBinding.__cbody = self.__cbody:getShaderBinding(i) 		self.localShaderBindings[i] = shaderBinding 	end end   function Screen:getShaderBinding(index) 	return self.localShaderBindings[index] end   function Screen:getHighestZIndex() 	return self.__cbody:getHighestZIndex() end   function Screen:sortChildren() 	self.__cbody:sortChildren() end   function Screen:hasFilterShader() 	return self.__cbody:hasFilterShader() end  function Screen:__index__(name) 	if name == \"xoffset\" then 		return self.__cbody:getScreenOffset().x 	elseif name == \"yoffset\" then 		return self.__cbody:getScreenOffset().y 	elseif name == \"enabled\" then 		return self.__cbody.enabled 	end end  function Screen:setScreenOffset(x,y) 	self.__cbody:setScreenOffset(x,y) end   function Screen:__set_callback(name,value) 	if name == \"enabled\" then 		self.__cbody.enabled = value 		return true		 	elseif name == \"xoffset\" then 		self.__cbody:setScreenOffset(value, self.__cbody:getScreenOffset().y) 		return true		 	elseif name == \"yoffset\" then 		self.__cbody:setScreenOffset(self.__cbody:getScreenOffset().x, value) 		return true		 	end 	return false end   class \"PhysicsScreen\" (Screen)  function PhysicsScreen:PhysicsScreen() 	if self__cbody == nil then 		self.__cbody = Tau.PhysicsScreen() 	end 	self:Screen() end   function PhysicsScreen:addPhysicsChild(newEntity, entType, friction, density, restitution, isSensor) 	self.__children[self.__numChildren] = newEntity 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addPhysicsChild(newEntity.__cbody, entType, friction, density, restitution, isSensor) end  function PhysicsScreen:removePhysicsChild(entityToRemove) 	self.__cbody:removePhysicsChild(entityToRemove.__cbody) end 	  function PhysicsScreen:addCollisionChild(newEntity, entType) 	self.__children[self.__numChildren] = newEntity 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addCollisionChild(newEntity.__cbody, entType) end 	  function PhysicsScreen:createDistanceJoint(ent1, ent2, collideConnected) 	self.__cbody:createDistanceJoint(ent1.__cbody, ent2.__cbody, collideConnected) end   function PhysicsScreen:createPrismaticJoint(ent1, ent2, collideConnected) 	self.__cbody:createPrismaticJoint(ent1.__cbody, ent2.__cbody, collideConnected) end   function PhysicsScreen:createRevoluteJoint(ent1, ent2, ax, ay, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque) 	self.__cbody:createRevoluteJoint(ent1.__cbody, ent2.__cbody, ax, ay, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque) end   function PhysicsScreen:createMouseJoint(ent1, x, y) 	mp = Vector2(x,y) 	self.mouseJoint = self.__cbody:createMouseJoint(ent1.__cbody, mp.__cbody) end  function PhysicsScreen:destroyMouseJoint() 	self.__cbody:destroyMouseJoint(self.mouseJoint) end   function PhysicsScreen:applyForce(ent, fx, fy) 	self.__cbody:applyForce(ent.__cbody, fx, fy) end   function PhysicsScreen:applyImpulse(ent, fx, fy) 	self.__cbody:applyImpulse(ent.__cbody, fx, fy) end  	 function PhysicsScreen:setVelocity(ent, fx, fy) 	self.__cbody:setVelocity(ent.__cbody, fx, fy) end   function PhysicsScreen:setVelocityX(ent, fx) 	self.__cbody:setVelocityX(ent.__cbody, fx) end   function PhysicsScreen:setVelocityY(ent, fy) 	self.__cbody:setVelocityY(ent.__cbody, fy) end 	  function PhysicsScreen:wakeUp(ent) 	self.__cbody:wakeUp(ent.__cbody) end 	  function PhysicsScreen:areEntitiesColliding(ent1, ent2) 	return 	self.__cbody:areEntitiesColliding(ent1.__cbody, ent2.__cbody) end	   function PhysicsScreen:getEntityCollisionNormal(ent1, ent2) 	ret = self.__cbody:getEntityCollisionNormal(ent1.__cbody, ent2.__cbody) 	return Vector2(ret.x,ret.y) end	    function PhysicsScreen:getEntityAtPosition(x, y) 	local cbody = self.__cbody:getEntityAtPosition(x,y) 	if cbody ~= nil then 		return self:getEntityByCBody(cbody) 	else 		return nil 	end end   function PhysicsScreen:testEntityAtPosition(ent, x, y) 	return self.__cbody:testEntityAtPosition(ent.__cbody, x, y) end   class \"ScreenEntity\" (EventDispatcher)  function ScreenEntity:ScreenEntity() 	self.__children = {} 	self.__numChildren = 0 	if self.__cbody == nil then 		self.__cbody = Tau.ScreenEntity() 	end 	self:EventDispatcher() end  function ScreenEntity:setRotation(rotation) 	self.__cbody:setRotation(rotation) end  function ScreenEntity:getRotation() 	return self.__cbody:getRotation() end  function ScreenEntity:__index__(name) 	if name == \"width\" then 		return self.__cbody:getWidth() 	elseif name == \"height\" then 		return self.__cbody:getHeight() 	elseif name == \"rotation\" then 		return self.__cbody:getRotation() 	elseif name == \"xscale\" then 		return self.__cbody:getScale().x 	elseif name == \"yscale\" then 		return self.__cbody:getScale().y 	elseif name == \"x\" then 		return self.__cbody:getPosition().x 	elseif name == \"y\" then 		return self.__cbody:getPosition().y 	elseif name == \"visible\" then 		return self.__cbody.visible 	elseif name == \"enabled\" then 		return self.__cbody.enabled 	end end    function ScreenEntity:__set_callback(name,value) 	if name == \"x\" then 		self.__cbody:setPosition(value,self.__cbody:getPosition().y) 		return true 	elseif name == \"y\" then 		self.__cbody:setPosition(self.__cbody:getPosition().x, value) 		return true 	elseif name == \"xscale\" then 		self.__cbody:setScale(value, self.__cbody:getScale().y)	 		return true 	elseif name == \"yscale\" then 		self.__cbody:setScale(self.__cbody:getScale().x, value)	 		return true 	elseif name == \"rotation\" then 		self.__cbody:setRotation(value) 		return true 	elseif name == \"enabled\" then 		self.__cbody.enabled = value 		return true 	elseif name == \"visible\" then 		self.__cbody.visible = value 		return true 	elseif name == \"width\" then 		self.__cbody:setWidth(value) 		return true 	elseif name == \"height\" then 		self.__cbody:setHeight(value) 		return true		 	end 	return false end   function ScreenEntity:addChild(child) 	self.__children[self.__numChildren] = child 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addChild(child.__cbody) end   function ScreenEntity:setPosition(x,y) 	self.__cbody:setPosition(x,y) end   function ScreenEntity:startDrag(x,y) 	self.__cbody:startDrag(x,y) end   function ScreenEntity:stopDrag() 	self.__cbody:stopDrag() end  function ScreenEntity:hitTest(x,y) 	return self.__cbody:hitTest(x,y) end   function ScreenEntity:setBlendingMode(mode) 	self.__cbody:setBlendingMode(mode) end   function ScreenEntity:setColor(r,g,b,a) 	self.__cbody.color:setColor(r,g,b,a) end   function ScreenEntity:setPositionMode(mode) 	self.__cbody:setPositionMode(mode) end  class \"ScreenLabel\" (ScreenEntity)   function ScreenLabel:ScreenLabel(fontName, text, size, mode) 	self.__cbody = Tau.ScreenLabel(fontName,text,size,mode) 	self:ScreenEntity() end  function ScreenLabel:setText(text) 	self.__cbody:setText(text) end   class \"ScreenShape\" (ScreenEntity)   function ScreenShape:ScreenShape(type, o1,o2,o3,o4) 	self.__cbody = Tau.ScreenShape(type, o1, o2, o3, o4) 	self:ScreenEntity()	 end    function ScreenShape:setGradient(r1, g1, b1, a1, r2, g2, b2, a2) 	self.__cbody:setGradient(r1, g1, b1, a1, r2, g2, b2, a2) end    function ScreenShape:clearGradient() 	self.__cbody:clearGradient() end    function ScreenShape:__set_callback(name,value) 	if name == \"strokeEnabled\" then 		self.__cbody.strokeEnabled = value 		return true 	elseif name == \"lineSmooth\" then 		self.__cbody.lineSmooth = value 		return true 	elseif name == \"strokeWidth\" then 		self.__cbody:setStrokeWidth(value) 		return true 	end 	return super(name,value) end  class \"ScreenImage\" (ScreenEntity)  function ScreenImage:ScreenImage(filename) 	self.__cbody = Tau.ScreenImage(filename) 	self:ScreenEntity()	 end   function ScreenImage:setImageCoordinates(x,y,w,h) 	self.__cbody:setImageCoordinates(x,y,w,h) end  function ScreenImage:getImageWidth() 	return self.__cbody:getImageWidth() end  function ScreenImage:getImageHeight() 	return self.__cbody:getImageHeight() end   function ScreenImage:setTexture(texture) 	self.__cbody:setTexture(texture.__cbody) end  class \"ScreenLine\" (ScreenEntity)  function ScreenLine:ScreenLine(p1,p2) 	self.__cbody = Tau.ScreenLine(p1.__cbody,p2.__cbody) 	self:ScreenEntity() end   function ScreenLine:setLineWidth(width) 	self.__cbody:setLineWidth(width) end  class \"ScreenSprite\" (ScreenEntity)   function ScreenSprite:ScreenSprite(fileName, spriteWidth, spriteHeight) 	self.__cbody = Tau.ScreenSprite(fileName, spriteWidth, spriteHeight) 	self:ScreenEntity() end   function ScreenSprite:addAnimation(name, frames, speed) 	self.__cbody:addAnimation(name,frames,speed) end   function ScreenSprite:playAnimation(name, startFrame, once) 	self.__cbody:playAnimation(name,startFrame,once) end    class \"Sound\"  function Sound:Sound(fileName) 	self.__cbody = Tau.Sound(fileName) end   function Sound:Play(once) 	self.__cbody:Play(once) end  function Sound:Stop() 	self.__cbody:Stop() end    class \"Scene\" (EventDispatcher)  function Scene:Scene() 	if self.__cbody == nil then 		self.__cbody = Tau.GenericScene() 	end 	self.__children = {} 	self.__numChildren = 0 	self.defaultCamera = Camera(self) 	self.defaultCamera.__cbody = self.__cbody:getDefaultCamera() 	self:EventDispatcher()	 end  function Scene:addLight(light) 	self.__cbody:addLight(light.__cbody) 	self.__children[self.__numChildren] = light 	self.__numChildren = self.__numChildren + 1	 end  function Scene:getDefaultCamera() 	return self.defaultCamera end  function Scene:addEntity(entity) 	self.__children[self.__numChildren] = entity 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addEntity(entity.__cbody)	 	return entity end  function Scene:addChild(child) 	return self:addEntity(child) end  function Scene:removeEntity(child) 	self.__cbody:removeEntity(child.__cbody) 	for i=0,count(self.__children) do 		if self.__children[i] == child then 			self.__children[i] = nil 		end 	end 	return child end  function Scene:addGrid(textureName) 	self.__cbody:addGrid(textureName) end  function Scene:enableFog(val) 	self.__cbody:enableFog(val) end  function Scene:setFogProperties(fogMode, color, density, startDepth,endDepth) 	self.__cbody:setFogProperties(fogMode, color, density, startDepth,endDepth) end   class \"CollisionScene\" (Scene)  function CollisionScene:CollisionScene() 	if self.__cbody == nil then 		self.__cbody = Tau.CollisionScene() 	end 	self:Scene() end   function CollisionScene:addCollisionChild(child, autoCollide,type) 	self.__children[self.__numChildren] = child 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addCollisionChild(child.__cbody, autoCollide,type) end  function CollisionScene:enableGravity(entity) 	self.__cbody:enableGravity(entity.__cbody) end   class \"SceneEntity\" (EventDispatcher)  function SceneEntity:SceneEntity()  	self.__getmap = {} 	self.__setmap = {}  	if self.__cbody == nil then 		self.__cbody = Tau.SceneEntity() 	end 	self.__children = {} 	self.__numChildren = 0 	self:EventDispatcher()	  	self.__getmap[\"pitch\"] = self.__get__pitch 	self.__getmap[\"yaw\"] = self.__get__yaw 	self.__getmap[\"roll\"] = self.__get__roll 	self.__getmap[\"x\"] = self.__get__x 	self.__getmap[\"y\"] = self.__get__y 	self.__getmap[\"z\"] = self.__get__z 	self.__getmap[\"xscale\"] = self.__get__xscale 	self.__getmap[\"yscale\"] = self.__get__yscale 	self.__getmap[\"zscale\"] = self.__get__zscale 	self.__getmap[\"enabled\"] = self.__get__enabled 	self.__getmap[\"visible\"] = self.__get__visible		 	self.__getmap[\"backfaceCulled\"] = self.__get__backfaceCulled 	self.__getmap[\"depthTest\"] = self.__get__depthTest		  	self.__setmap[\"pitch\"] = self.__set__pitch 	self.__setmap[\"yaw\"] = self.__set__yaw 	self.__setmap[\"roll\"] = self.__set__roll 	self.__setmap[\"x\"] = self.__set__x 	self.__setmap[\"y\"] = self.__set__y 	self.__setmap[\"z\"] = self.__set__z 	self.__setmap[\"xscale\"] = self.__set__xscale 	self.__setmap[\"yscale\"] = self.__set__yscale 	self.__setmap[\"zscale\"] = self.__set__zscale 	self.__setmap[\"enabled\"] = self.__set__enabled 	self.__setmap[\"visible\"] = self.__set__visible		 	self.__setmap[\"backfaceCulled\"] = self.__set__backfaceCulled 	self.__setmap[\"depthTest\"] = self.__set__depthTest 		 end   function SceneEntity:addChild(child) 	self.__children[self.__numChildren] = child 	self.__numChildren = self.__numChildren + 1 	self.__cbody:addChild(child.__cbody) end   function SceneEntity:setColor(r,g,b,a) 	self.__cbody.color:setColor(r,g,b,a) end   function SceneEntity:Translate(x,y,z) 	self.__cbody:Translate(x,y,z) end   function SceneEntity:setPosition(x,y,z) 	self.__cbody:setPosition(x,y,z) end   function SceneEntity:getPosition() 	return self.__cbody:getPosition() end  function SceneEntity:setScaleX(x) 	self.__cbody:setScaleX(x) end  function SceneEntity:setScaleY(y) 	self.__cbody:setScaleY(y) end  function SceneEntity:setScaleZ(z) 	self.__cbody:setScaleZ(z) end  function SceneEntity:setPositionX(x) 	self.__cbody:setPositionX(x) end  function SceneEntity:setPositionY(y) 	self.__cbody:setPositionY(y) end  function SceneEntity:setPositionZ(z) 	self.__cbody:setPositionZ(z) end     function SceneEntity:setScale(x,y,z) 	self.__cbody:setScale(x,y,z) end   function SceneEntity:Scale(x,y,z) 	self.__cbody:Scale(x,y,z) end   function SceneEntity:__index__(name) 	local getmap = rawget(self, \"__getmap\") 	if getmap ~= nil then 		local getfunc = rawget(getmap, name) 		if getfunc ~= nil then 			return getfunc(self) 		end	 	end end  function SceneEntity:__get__pitch() 	return self.__cbody:getPitch() end  function SceneEntity:__get__yaw() 	return self.__cbody:getYaw() end  function SceneEntity:__get__roll() 	return self.__cbody:getRoll() end  function SceneEntity:__get__x() 	return self.__cbody:getPosition().x end	  function SceneEntity:__get__y() 	return self.__cbody:getPosition().y end	  function SceneEntity:__get__z() 	return self.__cbody:getPosition().z end 	 function SceneEntity:__get__xscale()	 	return self.__cbody:getScale().x end 	 function SceneEntity:__get__yscale() 	return self.__cbody:getScale().y end  function SceneEntity:__get__zscale() 	return self.__cbody:getScale().z end 	 function SceneEntity:__get__enabled() 	return self.__cbody.enabled end	  function SceneEntity:__get__visible() 	return self.__cbody.visible end  function SceneEntity:__get__backfaceCulled() 	return self.__cbody.backfaceCulled end	  function SceneEntity:__get__depthTest()	 	return self.__cbody.depthTest	 end    function SceneEntity:__set_callback(name,value) 	local setmap = rawget(self, \"__setmap\") 	if setmap ~= nil then 		local setfunc = rawget(setmap, name) 		if setfunc ~= nil then		 			setfunc(self, value) 			return true 		end 	else 		return false 	end end  function SceneEntity:__set__pitch(value) 	self.__cbody:setPitch(value) end  function SceneEntity:__set__yaw(value) 	self.__cbody:setYaw(value) end  function SceneEntity:__set__roll(value) 	self.__cbody:setRoll(value) end  function SceneEntity:__set__x(value) 	self.__cbody:setPositionX(value) end	  function SceneEntity:__set__y(value) 	self.__cbody:setPositionY(value) end	  function SceneEntity:__set__z(value) 	self.__cbody:setPositionZ(value) end 	 function SceneEntity:__set__xscale(value)	 	self.__cbody:setScaleX(value) end 	 function SceneEntity:__set__yscale(value) 	self.__cbody:setScaleY(value) end  function SceneEntity:__set__zscale(value) 	self.__cbody:setScaleZ(value) end 	 function SceneEntity:__set__enabled(value) 	self.__cbody.enabled = value end	  function SceneEntity:__set__visible(value) 	self.__cbody.visible = value end  function SceneEntity:__set__backfaceCulled(value) 	self.__cbody.backfaceCulled = value end	  function SceneEntity:__set__depthTest(value)	 	self.__cbody.depthTest = value end   function SceneEntity:lookAt(vector) 	self.__cbody:lookAt(vector.__cbody) end   class \"Skeleton\" (SceneEntity)  function Skeleton:Skeleton(fileName) 	if self.__cbody == nil then 		self.__cbody = Tau.Skeleton(fileName) 	end 	self:SceneEntity() end   function Skeleton:playAnimation(name) 	self.__cbody:playAnimation(name) end  function isClassOfType(instance, className) 	if type(instance) == \"table\" then 		if instance.class ~= nil then 			if instance:class():name() == className then 				return true 			end 		end 	end 	return false end   class \"Mesh\"     function Mesh:Mesh(arg1) 	if self.__cbody == nil then 		if arg1 == nil then 			self.__cbody = Tau.Mesh(TRI_MESH) 		else 			if type(fileName) == \"string\" or type(fileName) == \"number\" then 				self.__cbody = Tau.Mesh(arg1) 			else 				self.__cbody = Tau.Mesh(TRI_MESH) 			end 		end 	end	 	self.__polygons = {} 	self.__numPolygons = 0; end  function Mesh:addPolygon(polygon) 	self.__polygons[self.__numPolygons] = polygon 	self.__numPolygons = self.__numPolygons + 1 	self.__cbody:addPolygon(polygon) end 				 function Mesh:loadMesh(fileName) 	self.__cbody:loadMesh(fileName)	 end  function Mesh:getPolygonCount() 	return self.__cbody:getPolygonCount()	 end  function Mesh:getPolygon(index) 	return self.__cbody:getPolygon(index) end  function Mesh:createPlane(w,h) 	self.__cbody:createPlane(w,h) end  function Mesh:createBox(w,d, h) 	self.__cbody:createBox(w,d,h) end  function Mesh:createSphere(radius, numRings, numSegments) 	self.__cbody:createSphere(radius, numRings, numSegments) end 		 function Mesh:addVertex(vertex) 	self.__cbody:addVertex(vertex) end  function Mesh:getVertex(index) 	return self.__cbody:getVertex(index) end  function Mesh:getNumVertices() 	return self.__cbody:getNumVertices() end 		 function Mesh:useVertexNormals(val) 	self.__cbody:useVertexNormals(val) end 		 function Mesh:usesFaceUV() 	return self.__cbody:usesFaceUV() end  function Mesh:getRadius() 	return self.__cbody:getRadius() end 			 function Mesh:calculateNormals() 	self.__cbody:calculateNormals() end 			 function Mesh:getMeshType() 	return 	self.__cbody:getMeshType() end  function Mesh:setMeshType(newType) 	self.__cbody:setMeshType(newType) end  function Mesh:calculateBBox() 	self.__cbody:calculateBBox() end 		 function Mesh:hasVertexBuffer() 	return self.__cbody:hasVertexBuffer() end   class \"SceneMesh\" (SceneEntity)   function SceneMesh:SceneMesh(fileName) 	if self.__cbody == nil then 		if fileName == nil then 			self.__cbody = Tau.SceneMesh(TRI_MESH) 		else 			if type(fileName) == \"string\" or type(fileName) == \"number\" then 				self.__cbody = Tau.SceneMesh(fileName) 			elseif isClassOfType(fileName, \"Mesh\") == true then 				self.__cbody = Tau.SceneMesh(fileName.__cbody) 				self.__mesh = fileName 			else 				self.__cbody = Tau.SceneMesh(TRI_MESH) 			end 		end 	end	 	 	self.skeleton = nil 	self:SceneEntity() end  function SceneMesh:EmptySceneMesh() 	if self.__cbody == nil then 		self.__cbody = Tau.SceneMesh() 	end 	self.skeleton = nil	 	self:SceneEntity() end  function SceneMesh:getSkeleton() 	return self.skeleton end   function SceneMesh:loadTexture(fileName) 	self.__cbody:loadTexture(fileName) end   function SceneMesh:loadSkeleton(fileName) 	self.skeleton = Skeleton(fileName) 	self:addChild(self.skeleton) 	self.__cbody:setSkeleton(self.skeleton.__cbody) end   function SceneMesh:setTexture(texture) 	self.__cbody:setTexture(texture.__cbody) end   function SceneMesh:setMaterial(material) 	self.__cbody:setMaterial(material.__cbody) end   function SceneMesh:setMaterialByName(materialName) 	self.__cbody:setMaterial(materialName) end 		  function SceneMesh:cacheToVertexBuffer(cache) 	self.__cbody:cacheToVertexBuffer(cache) end   function SceneMesh:showVertexNormals(val) 	self.__cbody.showVertexNormals = val end  class \"ScenePrimitive\" (SceneMesh)   function ScenePrimitive:ScenePrimitive(stype,v1,v2,v3) 	self.__cbody = Tau.ScenePrimitive(stype,v1,v2,v3) 	self:EmptySceneMesh() end    class \"Camera\" (SceneEntity)   function Camera:Camera(pscene) 	if self.__cbody == nil then 		self.__cbody = Tau.Camera(pscene.__cbody) 	end 	self:SceneEntity() end  function Camera:__index__(name) 	if name == \"fov\" then 		return self.__cbody:getFOV() 	elseif name == \"orthoMode\" then 		return self.__cbody:getOrthoMode() 	elseif name == \"exposureLevel\" then 		return self.__cbody:getExposureLevel() 	end 	return super(name)	 end    function Camera:__set_callback(name,value) 	if name == \"fov\" then 		self.__cbody:setFOV(value) 		return true 	elseif name == \"orthoMode\" then 		self.__cbody:setYaw(value) 		return true 	elseif name == \"exposureLevel\" then 		self.__cbody:setExposureLevel(value) 		return true 	end 	return super(name,value) end  function Camera:canSee(entity) 	return self.__cbody:canSee(entity.__cbody) end  function Camera:setPostFilter(materialName) 	self.__cbody:setPostFilter(materialName) end   class \"ParticleEmitter\" (SceneEntity)   function ParticleEmitter:ParticleEmitter(materialName, particleMesh, emitter, particleParentScene, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation) 	if self.__cbody == nil then 		local meshPtr = nil 		local emitterPtr = nil  		if particleMesh ~= nil then 			meshPtr = particleMesh.__cbody 		end  		if emitter ~= nil then 			emitterPtr = emitter.__cbody 		end 					 		self.__cbody = Tau.ParticleEmitter(materialName, meshPtr, emitterPtr, particleParentScene.__cbody, particleType, emitterType, lifespan, numParticles, direction.__cbody, gravity.__cbody, deviation.__cbody) 	end	 	 	self.colorCurveR = self.__cbody.colorCurveR 	self.colorCurveG = self.__cbody.colorCurveG 	self.colorCurveB = self.__cbody.colorCurveB 	self.colorCurveA = self.__cbody.colorCurveA 	 	self.scaleCurve = self.__cbody.scaleCurve 	 	self:SceneEntity() end  function ParticleEmitter:setRotationSpeed(speed) 	self.__cbody:setRotationSpeed(speed) end  function ParticleEmitter:setBlendingMode(mode) 	self.__cbody:setBlendingMode(mode) end  function ParticleEmitter:setDepthTest(val) 	self.__cbody:setDepthTest(val) end  function ParticleEmitter:setAlphaTest(val) 	self.__cbody:setAlphaTest(val) end 		 function ParticleEmitter:enablePerlin(val) 	self.__cbody:enablePerlin(val) end  function ParticleEmitter:setBillboardMode(mode) 	self.__cbody:setBillboardMode(mode) end  function ParticleEmitter:enableEmitter(val) 	self.__cbody:enableEmitter(val) end  function ParticleEmitter:emitterEnabled() 	return self.__cbody:emitterEnabled() end 			 function ParticleEmitter:setEmitterRadius(rad) 	self.__cbody:setEmitterRadius(rad) end  function ParticleEmitter:setEmitRotationVector(rotVector) 	self.__cbody:setEmitRotationVector(rotVector.__cbody) end  function ParticleEmitter:setEmitRotationDeviance(rotVector) 	self.__cbody:setEmitRotationDeviance(rotVector.__cbody) end  function ParticleEmitter:setAllAtOnce(val) 	self.__cbody:setAllAtOnce(val) end 			 function ParticleEmitter:Trigger() 	self.__cbody:Trigger() end 		 function ParticleEmitter:setPerlinModSize(size) 	self.__cbody:setPerlinModSize(size) end  function ParticleEmitter:setParticleCount(count) 	self.__cbody:setParticleCount(count) end  class \"SceneLight\" (SceneEntity)   function SceneLight:SceneLight(type, intensity, distance, parentScene) 	if self.__cbody == nil then 		self.__cbody = Tau.SceneLight(type, intensity, distance, parentScene.__cbody) 	end 	self:SceneEntity() end   function SceneLight:setLightColor(r,g,b) 	self.__cbody.lightColor:setColor(r,g,b,1) end   function SceneLight:enableShadows(val, res) 	self.__cbody:enableShadows(val,res) end   class \"ShaderBinding\"   function ShaderBinding:ShaderBinding() 	self.__cbody = nil end   function ShaderBinding:setParam(type,name,value) 	if self.__cbody ~= nil then 		self.__cbody:setParam(type,name,value) 	end end   class \"Vector2\"  function Vector2:Vector2(x,y) 	if self.__cbody == nil then 		self.__cbody = Tau.Vector2(x,y) 	end end    class \"Vector3\"  function Vector3:Vector3(x,y,z) 	if self.__cbody == nil then 		self.__cbody = Tau.Vector3(x,y,z) 	end end   class \"Perlin\"  function Perlin:Perlin(octaves, freq, amp, seed) 	self.__cbody = Tau.Perlin(octaves,freq,amp,seed) end  function Perlin:Get(x,y) 	return self.__cbody:Get(x,y) end ";
		//function print(val) 	debugPrint(tostring(val)) end
		String fileData = "";
		/*	
		 std::ifstream in(fileName.c_str());
		 if (!in.is_open()) {
		 printf("Error opening file!\n");
		 return;
		 }
		 
		 char buf[2048];
		 while (in.getline(buf, 2048)) {
		 fileData += buf;
		 fileData += "\n";
		 }
		 
		 in.close();
		 */
		OSFILE *inFile = OSBasics::open(fileName, "r");	
		if(inFile) {
			Logger::log("Opened entrypoint file...");
			OSBasics::seek(inFile, 0, SEEK_END);	
			long progsize = OSBasics::tell(inFile);
			OSBasics::seek(inFile, 0, SEEK_SET);
			char *buffer = (char*)malloc(progsize+1);
			memset(buffer, 0, progsize+1);
			OSBasics::read(buffer, progsize, 1, inFile);
			fileData = buffer;		
			free(buffer);
			OSBasics::close(inFile);	
		} else {
			Logger::log("Error opening entrypoint file (%s)\n", fileName.c_str());
		}
		
		
		String postpend = ""; //" \nif update == nil then\nfunction update(e)\nend\nend\nwhile CORE:Update() do\nupdate(CORE:getElapsed())\nend";
		
		//String fullScript = prepend + prepend2 + prepend3 + fileData;// + postpend;
		String fullScript = fileData;
		//String fullScript = fileData;// + postpend;
		
		doneLoading = true;
		
		//lua_gc(L, LUA_GCSTOP, 0);
		
		lua_register(L, "debugPrint", debugPrint);		
		
/*
		lua_pushliteral(L, "debug");
		lua_gettable(L, LUA_GLOBALSINDEX);
		lua_pushliteral(L, "traceback");  // correct fn name?
		lua_gettable(L, -2);

*/				
		
		CoreServices::getInstance()->getCore()->lockMutex(CoreServices::getRenderMutex());			
		if (report(L, luaL_loadstring(L, fullScript.c_str()) || lua_pcall(L, 0,0,0))) {
			
			CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			printf("CRASH LOADING SCRIPT FILE\n");
//			exit(1);				
		} else  {
			CoreServices::getInstance()->getCore()->unlockMutex(CoreServices::getRenderMutex());			
			if (report(L, luaL_loadstring(L, postpend.c_str()) || lua_pcall(L, 0,0,0))) {	
//				exit(1);
				printf("CRASH IN SCRIPT EXECUTION FILE\n");			
			} else  {

			}
		}

	}
}

PolycodeDebugEvent::PolycodeDebugEvent() : Event() {
	
}

PolycodeDebugEvent::~PolycodeDebugEvent() {
	
}


PolycodePlayer::PolycodePlayer(String fileName, bool knownArchive) : EventDispatcher()  {
	fileToRun = fileName;
	core = NULL;
	doneLoading = false;	
	_knownArchive = knownArchive;
	xRes = 640;
	yRes = 480;
	aaLevel = 6;
	fullScreen = false;	
}

void PolycodePlayer::loadFile(const char *fileName) {
	
	String nameString = fileName;
	String ext = nameString.substr(nameString.length() - 8, nameString.length());
	
	printf("Loading %s\n", fileName);
	
	bool loadingArchive = false;
	
	String configPath;
	
	if(ext == ".polyapp" || _knownArchive) {
		ResourceManager *rman = CoreServices::getInstance()->getResourceManager();
		rman->addArchive(nameString);
		configPath = "runinfo.polyrun";
		loadingArchive = true;
		Logger::log("Reading configuration from POLYAPP file... (%s)\n", nameString.c_str());
	} else {
		ResourceManager *rman = CoreServices::getInstance()->getResourceManager();
		
		String fileDir = "";
		vector<String> bits = String(fileName).split("/");
		for(int i=0; i < bits.size()-1; i++) {
			fileDir += "/"+bits[i];
		}
		
		rman->addArchive(fileDir);
		configPath = fileName;
		Logger::log("Reading configuration from .polycode file directly... (%s)\n", fileName);		
	}
	
	String mainFile = "";
	String basePath = fileName;
	
	Number red = 0.2f;
	Number green = 0.2f;
	Number blue = 0.2f;
	
	frameRate = 60;
	
	Object configFile;
	if(!configFile.loadFromXML(configPath)) {
		Logger::log("Error loading config file\n");
	} else {		
		
		if(configFile.root["entryPoint"]) {
			mainFile = configFile.root["entryPoint"]->stringVal;
		}		
		if(configFile.root["defaultWidth"]) {
			xRes = configFile.root["defaultWidth"]->intVal;
		}		
		if(configFile.root["defaultHeight"]) {
			yRes = configFile.root["defaultHeight"]->intVal;
		}		
		if(configFile.root["frameRate"]) {
			frameRate = configFile.root["frameRate"]->intVal;
		}		
		if(configFile.root["antiAliasingLevel"]) {
			aaLevel = configFile.root["antiAliasingLevel"]->intVal;
		}		
		if(configFile.root["fullScreen"]) {
			fullScreen = configFile.root["fullScreen"]->boolVal;
		}		
		if(configFile.root["backgroundColor"]) {
			ObjectEntry *color = configFile.root["backgroundColor"];
			if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
				red = (*color)["red"]->NumberVal;
				green = (*color)["green"]->NumberVal;
				blue = (*color)["blue"]->NumberVal;
				
			}			
		}		
	}
	
	Logger::log("Mainfile: %s\n", mainFile.c_str());
	
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	event->xRes = xRes;
	event->yRes = yRes;	
	
	createCore();
	
	Logger::log("Core created...\n");
	
	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
	
	
	if(configFile.root["packedItems"]) {
		ObjectEntry *packed = configFile.root["packedItems"];
		if(packed) {
			for(int i=0; i < packed->length; i++) {
				ObjectEntry *entryIsResource = (*(*packed)[i])["isResource"];				
				ObjectEntry *entryPath = (*(*packed)[i])["path"];
				if(entryIsResource && entryPath) {
					if(entryIsResource->boolVal == true) {
						CoreServices::getInstance()->getResourceManager()->addDirResource(entryPath->stringVal, true);
					}
				}
			}
		}
	}
	
	
	core->setUserPointer(this);
	//core->addEventListener(this, Core::EVENT_CORE_RESIZE);
	core->setVideoMode(xRes, yRes, fullScreen, aaLevel);
		
//	dispatchEvent(event, PolycodeDebugEvent::EVENT_RESIZE);		
	
	CoreServices::getInstance()->getRenderer()->setClearColor(red, green, blue);
//	CoreServices::getInstance()->getRenderer()->setClearColor(1,0,0);
	srand(core->getTicks());
	
	String fullPath;
	
	if(loadingArchive) {
		fullPath = mainFile;
	} else {
		int lindex = basePath.find_last_of("/");
		fullPath = basePath.substr(0, lindex);	
		fullPath += mainFile;	
		Logger::log(fullPath.c_str());
	}
	
	runFile(fullPath);
}

void PolycodePlayer::runPlayer() {
	Logger::log("Running player\n");	
	loadFile(fileToRun.c_str());
}

PolycodePlayer::~PolycodePlayer() {
	printf("deleting core...\n");
	delete core;
	PolycodeDebugEvent *event = new PolycodeDebugEvent();			
	dispatchEvent(event, PolycodeDebugEvent::EVENT_REMOVE);	
//	lua_close(L);
}

void PolycodePlayer::handleEvent(Event *event) {	
	if(event->getDispatcher() == core) {
		switch(event->getEventCode()) {
			case Core::EVENT_CORE_RESIZE:
				PolycodeDebugEvent *event = new PolycodeDebugEvent();			
				event->xRes = core->getXRes();
				event->yRes = core->getYRes();				
				dispatchEvent(event, PolycodeDebugEvent::EVENT_RESIZE);								
			break;		
		}
	}
}


bool PolycodePlayer::Update() {
	
	lua_getfield(L, LUA_GLOBALSINDEX, "Update");
	lua_pushnumber(L, core->getElapsed());
	lua_call(L, 1, 0);
	
	return core->Update();
}
