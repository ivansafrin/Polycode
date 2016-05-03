class "RendererThreadJob"



function RendererThreadJob:__getvar(name)
	if name == "jobType" then
		return Polycore.RendererThreadJob_get_jobType(self.__ptr)
	elseif name == "data" then
		local retVal = Polycore.RendererThreadJob_get_data(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "data2" then
		local retVal = Polycore.RendererThreadJob_get_data2(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function RendererThreadJob:__setvar(name,value)
	if name == "jobType" then
		Polycore.RendererThreadJob_set_jobType(self.__ptr, value)
		return true
	end
	return false
end


function RendererThreadJob:__delete()
	if self then Polycore.delete_RendererThreadJob(self.__ptr) end
end
