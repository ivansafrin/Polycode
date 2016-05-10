require "Polycode/ScriptInstance"

class "JSScriptInstance" (ScriptInstance)


function JSScriptInstance:__delete()
	if self then Polycode.delete_JSScriptInstance(self.__ptr) end
end
