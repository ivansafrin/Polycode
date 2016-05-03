class "MouseEventResult"



function MouseEventResult:__getvar(name)
	if name == "hit" then
		return Polycore.MouseEventResult_get_hit(self.__ptr)
	elseif name == "blocked" then
		return Polycore.MouseEventResult_get_blocked(self.__ptr)
	end
end


function MouseEventResult:__setvar(name,value)
	if name == "hit" then
		Polycore.MouseEventResult_set_hit(self.__ptr, value)
		return true
	elseif name == "blocked" then
		Polycore.MouseEventResult_set_blocked(self.__ptr, value)
		return true
	end
	return false
end


function MouseEventResult:__delete()
	if self then Polycore.delete_MouseEventResult(self.__ptr) end
end
