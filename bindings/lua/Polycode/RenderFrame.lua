class "RenderFrame"



function RenderFrame:__getvar(name)
	if name == "jobQueue" then
		local retVal = Polycore.RenderFrame_get_jobQueue(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["queue<RendererThreadJob>"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function RenderFrame:__setvar(name,value)
	if name == "jobQueue" then
		Polycore.RenderFrame_set_jobQueue(self.__ptr, value.__ptr)
		return true
	end
	return false
end


function RenderFrame:__delete()
	if self then Polycore.delete_RenderFrame(self.__ptr) end
end
