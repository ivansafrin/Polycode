class "ShaderPass"



function ShaderPass:__getvar(name)
	if name == "shader" then
		local retVal = Polycore.ShaderPass_get_shader(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Shader"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "wireframe" then
		return Polycore.ShaderPass_get_wireframe(self.__ptr)
	elseif name == "blendingMode" then
		return Polycore.ShaderPass_get_blendingMode(self.__ptr)
	elseif name == "shaderBinding" then
		local retVal = Polycore.ShaderPass_get_shaderBinding(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderBinding"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "materialShaderBinding" then
		local retVal = Polycore.ShaderPass_get_materialShaderBinding(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["ShaderBinding"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function ShaderPass:__setvar(name,value)
	if name == "wireframe" then
		Polycore.ShaderPass_set_wireframe(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycore.ShaderPass_set_blendingMode(self.__ptr, value)
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
		self.__ptr = Polycore.ShaderPass(unpack(arg))
	end
end

function ShaderPass:setAttributeArraysFromMesh(mesh)
	local retVal = Polycore.ShaderPass_setAttributeArraysFromMesh(self.__ptr, mesh.__ptr)
end

function ShaderPass:setExpectedAttributes()
	local retVal =  Polycore.ShaderPass_setExpectedAttributes(self.__ptr)
end

function ShaderPass.arrayToAttributeName(array)
	local retVal = Polycore.ShaderPass_arrayToAttributeName(array.__ptr)
	return retVal
end

function ShaderPass:__delete()
	if self then Polycore.delete_ShaderPass(self.__ptr) end
end
