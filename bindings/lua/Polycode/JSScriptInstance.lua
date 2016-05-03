require "Polycode/ScriptInstance"

class "JSScriptInstance" (ScriptInstance)



function JSScriptInstance:__getvar(name)
	if name == "objectRef" then
		local retVal = Polycore.JSScriptInstance_get_objectRef(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if ScriptInstance["__getvar"] ~= nil then
		return ScriptInstance.__getvar(self, name)
	end
end


function JSScriptInstance:__setvar(name,value)
	if ScriptInstance["__setvar"] ~= nil then
		return ScriptInstance.__setvar(self, name, value)
	else
		return false
	end
end


function JSScriptInstance:__delete()
	if self then Polycore.delete_JSScriptInstance(self.__ptr) end
end
