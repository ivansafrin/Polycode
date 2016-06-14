require "Polycode/Resource"

class "Shader" (Resource)


function Shader:__getvar(name)
	if name == "numSpotLights" then
		return Polycode.Shader_get_numSpotLights(self.__ptr)
	elseif name == "numPointLights" then
		return Polycode.Shader_get_numPointLights(self.__ptr)
	elseif name == "screenShader" then
		return Polycode.Shader_get_screenShader(self.__ptr)
	elseif name == "name" then
		return Polycode.Shader_get_name(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end

function Shader:__setvar(name,value)
	if name == "numSpotLights" then
		Polycode.Shader_set_numSpotLights(self.__ptr, value)
		return true
	elseif name == "numPointLights" then
		Polycode.Shader_set_numPointLights(self.__ptr, value)
		return true
	elseif name == "screenShader" then
		Polycode.Shader_set_screenShader(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycode.Shader_set_name(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end
function Shader:getType()
	local retVal =  Polycode.Shader_getType(self.__ptr)
	return retVal
end

function Shader:setName(name)
	local retVal = Polycode.Shader_setName(self.__ptr, name)
end

function Shader:getName()
	local retVal =  Polycode.Shader_getName(self.__ptr)
	return retVal
end

function Shader:getParamPointer(name)
	local retVal = Polycode.Shader_getParamPointer(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ProgramParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:getAttribPointer(name)
	local retVal = Polycode.Shader_getAttribPointer(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ProgramAttribute"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:reload()
	local retVal =  Polycode.Shader_reload(self.__ptr)
end

function Shader:getExpectedParamType(name)
	local retVal = Polycode.Shader_getExpectedParamType(self.__ptr, name)
	return retVal
end

function Shader:__delete()
	if self then Polycode.delete_Shader(self.__ptr) end
end
