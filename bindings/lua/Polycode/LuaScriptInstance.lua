require "Polycode/ScriptInstance"

class "LuaScriptInstance" (ScriptInstance)



function LuaScriptInstance:__getvar(name)
	if name == "tableRef" then
		return Polycore.LuaScriptInstance_get_tableRef(self.__ptr)
	end
	if ScriptInstance["__getvar"] ~= nil then
		return ScriptInstance.__getvar(self, name)
	end
end


function LuaScriptInstance:__setvar(name,value)
	if name == "tableRef" then
		Polycore.LuaScriptInstance_set_tableRef(self.__ptr, value)
		return true
	end
	if ScriptInstance["__setvar"] ~= nil then
		return ScriptInstance.__setvar(self, name, value)
	else
		return false
	end
end


function LuaScriptInstance:__delete()
	if self then Polycore.delete_LuaScriptInstance(self.__ptr) end
end
