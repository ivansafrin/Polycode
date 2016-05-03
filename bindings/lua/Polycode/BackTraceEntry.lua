class "BackTraceEntry"



function BackTraceEntry:__getvar(name)
	if name == "fileName" then
		return Polycore.BackTraceEntry_get_fileName(self.__ptr)
	elseif name == "lineNumber" then
		return Polycore.BackTraceEntry_get_lineNumber(self.__ptr)
	end
end


function BackTraceEntry:__setvar(name,value)
	if name == "fileName" then
		Polycore.BackTraceEntry_set_fileName(self.__ptr, value)
		return true
	elseif name == "lineNumber" then
		Polycore.BackTraceEntry_set_lineNumber(self.__ptr, value)
		return true
	end
	return false
end


function BackTraceEntry:__delete()
	if self then Polycore.delete_BackTraceEntry(self.__ptr) end
end
