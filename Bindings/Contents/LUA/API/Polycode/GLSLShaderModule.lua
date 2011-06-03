class "GLSLShaderModule"







function GLSLShaderModule:GLSLShaderModule(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.GLSLShaderModule(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function GLSLShaderModule:acceptsExtension(extension)
	local retVal = Polycore.GLSLShaderModule_acceptsExtension(self.__ptr, extension)
	return retVal
end

function GLSLShaderModule:createProgramFromFile(extension, fullPath)
	local retVal = Polycore.GLSLShaderModule_createProgramFromFile(self.__ptr, extension, fullPath)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Resource("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function GLSLShaderModule:reloadPrograms()
	local retVal =  Polycore.GLSLShaderModule_reloadPrograms(self.__ptr)
end

function GLSLShaderModule:getShaderType()
	local retVal =  Polycore.GLSLShaderModule_getShaderType(self.__ptr)
	return retVal
end

function GLSLShaderModule:createShader(node)
	local retVal = Polycore.GLSLShaderModule_createShader(self.__ptr, node.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Shader("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function GLSLShaderModule:applyShaderMaterial(r_enderer, material, localOptions, shaderIndex)
	local retVal = Polycore.GLSLShaderModule_applyShaderMaterial(self.__ptr, r_enderer.__ptr, material.__ptr, localOptions.__ptr, shaderIndex)
	return retVal
end

function GLSLShaderModule:clearShader()
	local retVal =  Polycore.GLSLShaderModule_clearShader(self.__ptr)
end



function GLSLShaderModule:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_GLSLShaderModule(self.__ptr)
end
