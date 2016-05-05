class "RendererThreadJob"


function RendererThreadJob:__getvar(name)
	if name == "jobType" then
		return Polycode.RendererThreadJob_get_jobType(self.__ptr)
	elseif name == "data" then
		local retVal = Polycode.RendererThreadJob_get_data(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "data2" then
		local retVal = Polycode.RendererThreadJob_get_data2(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function RendererThreadJob:__setvar(name,value)
	if name == "jobType" then
		Polycode.RendererThreadJob_set_jobType(self.__ptr, value)
		return true
	elseif name == "data" then
		Polycode.RendererThreadJob_set_data(self.__ptr, value.__ptr)
		return true
	elseif name == "data2" then
		Polycode.RendererThreadJob_set_data2(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function RendererThreadJob:__delete()
	if self then Polycode.delete_RendererThreadJob(self.__ptr) end
end
