class "ScriptInstance"


function ScriptInstance:__delete()
	if self then Polycode.delete_ScriptInstance(self.__ptr) end
end
