class "ShaderPass"


function ShaderPass:__getvar(name)
	if name == "shader" then
		local retVal = Polycode.ShaderPass_get_shader(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Shader"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "wireframe" then
		return Polycode.ShaderPass_get_wireframe(self.__ptr)
	elseif name == "blendingMode" then
		return Polycode.ShaderPass_get_blendingMode(self.__ptr)
	elseif name == "shaderBinding" then
		local retVal = Polycode.ShaderPass_get_shaderBinding(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderBinding"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "materialShaderBinding" then
		local retVal = Polycode.ShaderPass_get_materialShaderBinding(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderBinding"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function ShaderPass:__setvar(name,value)
	if name == "shader" then
		Polycode.ShaderPass_set_shader(self.__ptr, value.__ptr)
		return true
	elseif name == "wireframe" then
		Polycode.ShaderPass_set_wireframe(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycode.ShaderPass_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "shaderBinding" then
		Polycode.ShaderPass_set_shaderBinding(self.__ptr, value.__ptr)
		return true
	elseif name == "materialShaderBinding" then
		Polycode.ShaderPass_set_materialShaderBinding(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function ShaderPass:ShaderPass(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.ShaderPass(unpack(arg))
	end
end

function ShaderPass:__delete()
	if self then Polycode.delete_ShaderPass(self.__ptr) end
end
