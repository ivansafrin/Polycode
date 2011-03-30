require "Polycode/Resource"

class "Material" (Resource)

function Material:Material(name)
	if self.__ptr == nil then
		self.__ptr = Polycore.Material(name)
	end
end

function Material:addShader(shader, shaderBinding)
	return Polycore.Material_addShader(self.__ptr, shader.__ptr, shaderBinding.__ptr)
end

function Material:getNumShaders()
	return Polycore.Material_getNumShaders(self.__ptr)
end

function Material:addShaderRenderTarget(newTarget)
	return Polycore.Material_addShaderRenderTarget(self.__ptr, newTarget.__ptr)
end

function Material:getNumShaderRenderTargets()
	return Polycore.Material_getNumShaderRenderTargets(self.__ptr)
end

function Material:getShaderRenderTarget(index)
	return Polycore.Material_getShaderRenderTarget(self.__ptr, index)
end

function Material:getName()
	return Polycore.Material_getName(self.__ptr)
end

function Material:getShader(index)
	return Polycore.Material_getShader(self.__ptr, index)
end

function Material:getShaderBinding(index)
	return Polycore.Material_getShaderBinding(self.__ptr, index)
end

function Material:loadMaterial(fileName)
	return Polycore.Material_loadMaterial(self.__ptr, fileName)
end

