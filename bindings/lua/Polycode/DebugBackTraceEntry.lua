class "DebugBackTraceEntry"


function DebugBackTraceEntry:__getvar(name)
	if name == "fileName" then
		return Polycode.DebugBackTraceEntry_get_fileName(self.__ptr)
	elseif name == "lineNumber" then
		return Polycode.DebugBackTraceEntry_get_lineNumber(self.__ptr)
	end
end

function DebugBackTraceEntry:__setvar(name,value)
	if name == "fileName" then
		Polycode.DebugBackTraceEntry_set_fileName(self.__ptr, value)
		return true
	elseif name == "lineNumber" then
		Polycode.DebugBackTraceEntry_set_lineNumber(self.__ptr, value)
		return true
	end
	return false
end
function DebugBackTraceEntry:__delete()
	if self then Polycode.delete_DebugBackTraceEntry(self.__ptr) end
end
