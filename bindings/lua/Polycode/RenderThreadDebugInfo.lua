class "RenderThreadDebugInfo"


function RenderThreadDebugInfo:__getvar(name)
	if name == "buffersProcessed" then
		return Polycode.RenderThreadDebugInfo_get_buffersProcessed(self.__ptr)
	elseif name == "drawCallsProcessed" then
		return Polycode.RenderThreadDebugInfo_get_drawCallsProcessed(self.__ptr)
	elseif name == "timeTaken" then
		return Polycode.RenderThreadDebugInfo_get_timeTaken(self.__ptr)
	end
end

function RenderThreadDebugInfo:__setvar(name,value)
	if name == "buffersProcessed" then
		Polycode.RenderThreadDebugInfo_set_buffersProcessed(self.__ptr, value)
		return true
	elseif name == "drawCallsProcessed" then
		Polycode.RenderThreadDebugInfo_set_drawCallsProcessed(self.__ptr, value)
		return true
	elseif name == "timeTaken" then
		Polycode.RenderThreadDebugInfo_set_timeTaken(self.__ptr, value)
		return true
	end
	return false
end
function RenderThreadDebugInfo:__delete()
	if self then Polycode.delete_RenderThreadDebugInfo(self.__ptr) end
end
