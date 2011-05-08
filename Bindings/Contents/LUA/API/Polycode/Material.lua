require "Polycode/Resource"

class "Material" (Resource)







function Material:Material(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Resource" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Material(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Material:addShader(shader, shaderBinding)
	local retVal = Polycore.Material_addShader(self.__ptr, shader.__ptr, shaderBinding.__ptr)
end

function Material:getNumShaders()
	local retVal =  Polycore.Material_getNumShaders(self.__ptr)
	return retVal
end

function Material:addShaderRenderTarget(newTarget)
	local retVal = Polycore.Material_addShaderRenderTarget(self.__ptr, newTarget.__ptr)
end

function Material:getNumShaderRenderTargets()
	local retVal =  Polycore.Material_getNumShaderRenderTargets(self.__ptr)
	return retVal
end

function Material:getShaderRenderTarget(index)
	local retVal = Polycore.Material_getShaderRenderTarget(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ShaderRenderTarget("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Material:getName()
	local retVal =  Polycore.Material_getName(self.__ptr)
	return retVal
end

function Material:getShader(index)
	local retVal = Polycore.Material_getShader(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Shader("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Material:getShaderBinding(index)
	local retVal = Polycore.Material_getShaderBinding(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ShaderBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Material:loadMaterial(fileName)
	local retVal = Polycore.Material_loadMaterial(self.__ptr, fileName)
end



function Material:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Material(self.__ptr)
end
