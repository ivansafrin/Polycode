class "ShaderPlatformData"


function ShaderPlatformData:__getvar(name)
	if name == "shaderID" then
		local retVal = Polycode.ShaderPlatformData_get_shaderID(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["GLuint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "vertexProgramID" then
		local retVal = Polycode.ShaderPlatformData_get_vertexProgramID(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["GLuint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "fragmentProgramID" then
		local retVal = Polycode.ShaderPlatformData_get_fragmentProgramID(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["GLuint"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function ShaderPlatformData:__setvar(name,value)
	if name == "shaderID" then
		Polycode.ShaderPlatformData_set_shaderID(self.__ptr, value.__ptr)
		return true
	elseif name == "vertexProgramID" then
		Polycode.ShaderPlatformData_set_vertexProgramID(self.__ptr, value.__ptr)
		return true
	elseif name == "fragmentProgramID" then
		Polycode.ShaderPlatformData_set_fragmentProgramID(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function ShaderPlatformData:__delete()
	if self then Polycode.delete_ShaderPlatformData(self.__ptr) end
end
