class "RendererThreadJob"


function RendererThreadJob:__getvar(name)
	if name == "jobType" then
		return Polycode.RendererThreadJob_get_jobType(self.__ptr)
	end
end

function RendererThreadJob:__setvar(name,value)
	if name == "jobType" then
		Polycode.RendererThreadJob_set_jobType(self.__ptr, value)
		return true
	end
	return false
end
function RendererThreadJob:__delete()
	if self then Polycode.delete_RendererThreadJob(self.__ptr) end
end
