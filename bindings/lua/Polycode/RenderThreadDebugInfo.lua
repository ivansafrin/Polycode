class "RenderThreadDebugInfo"



function RenderThreadDebugInfo:__getvar(name)
	if name == "buffersProcessed" then
		return Polycore.RenderThreadDebugInfo_get_buffersProcessed(self.__ptr)
	elseif name == "drawCallsProcessed" then
		return Polycore.RenderThreadDebugInfo_get_drawCallsProcessed(self.__ptr)
	elseif name == "timeTaken" then
		return Polycore.RenderThreadDebugInfo_get_timeTaken(self.__ptr)
	end
end


function RenderThreadDebugInfo:__setvar(name,value)
	if name == "buffersProcessed" then
		Polycore.RenderThreadDebugInfo_set_buffersProcessed(self.__ptr, value)
		return true
	elseif name == "drawCallsProcessed" then
		Polycore.RenderThreadDebugInfo_set_drawCallsProcessed(self.__ptr, value)
		return true
	elseif name == "timeTaken" then
		Polycore.RenderThreadDebugInfo_set_timeTaken(self.__ptr, value)
		return true
	end
	return false
end


function RenderThreadDebugInfo:__delete()
	if self then Polycore.delete_RenderThreadDebugInfo(self.__ptr) end
end
