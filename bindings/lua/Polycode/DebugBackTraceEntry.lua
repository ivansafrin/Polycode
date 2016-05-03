class "DebugBackTraceEntry"



function DebugBackTraceEntry:__getvar(name)
	if name == "fileName" then
		return Polycore.DebugBackTraceEntry_get_fileName(self.__ptr)
	elseif name == "lineNumber" then
		return Polycore.DebugBackTraceEntry_get_lineNumber(self.__ptr)
	end
end


function DebugBackTraceEntry:__setvar(name,value)
	if name == "fileName" then
		Polycore.DebugBackTraceEntry_set_fileName(self.__ptr, value)
		return true
	elseif name == "lineNumber" then
		Polycore.DebugBackTraceEntry_set_lineNumber(self.__ptr, value)
		return true
	end
	return false
end


function DebugBackTraceEntry:__delete()
	if self then Polycore.delete_DebugBackTraceEntry(self.__ptr) end
end
