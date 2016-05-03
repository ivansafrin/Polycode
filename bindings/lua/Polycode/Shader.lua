require "Polycode/Resource"

class "Shader" (Resource)



function Shader:__getvar(name)
	if name == "numSpotLights" then
		return Polycore.Shader_get_numSpotLights(self.__ptr)
	elseif name == "numPointLights" then
		return Polycore.Shader_get_numPointLights(self.__ptr)
	elseif name == "screenShader" then
		return Polycore.Shader_get_screenShader(self.__ptr)
	elseif name == "vertexProgram" then
		local retVal = Polycore.Shader_get_vertexProgram(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderProgram"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fragmentProgram" then
		local retVal = Polycore.Shader_get_fragmentProgram(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderProgram"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "name" then
		return Polycore.Shader_get_name(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Shader:__setvar(name,value)
	if name == "numSpotLights" then
		Polycore.Shader_set_numSpotLights(self.__ptr, value)
		return true
	elseif name == "numPointLights" then
		Polycore.Shader_set_numPointLights(self.__ptr, value)
		return true
	elseif name == "screenShader" then
		Polycore.Shader_set_screenShader(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycore.Shader_set_name(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function Shader:getType()
	local retVal =  Polycore.Shader_getType(self.__ptr)
	return retVal
end

function Shader:setName(name)
	local retVal = Polycore.Shader_setName(self.__ptr, name)
end

function Shader:getName()
	local retVal =  Polycore.Shader_getName(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:getParamPointer(name)
	local retVal = Polycore.Shader_getParamPointer(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ProgramParam"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:getAttribPointer(name)
	local retVal = Polycore.Shader_getAttribPointer(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ProgramAttribute"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Shader:reload()
	local retVal =  Polycore.Shader_reload(self.__ptr)
end

function Shader:getExpectedParamType(name)
	local retVal = Polycore.Shader_getExpectedParamType(self.__ptr, name)
	return retVal
end

function Shader:setVertexProgram(vp)
	local retVal = Polycore.Shader_setVertexProgram(self.__ptr, vp.__ptr)
end

function Shader:setFragmentProgram(fp)
	local retVal = Polycore.Shader_setFragmentProgram(self.__ptr, fp.__ptr)
end

function Shader:__delete()
	if self then Polycore.delete_Shader(self.__ptr) end
end
