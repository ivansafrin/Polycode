class "FixedShaderBinding"

function FixedShaderBinding:FixedShaderBinding(shader)
	if self.__ptr == nil then
		self.__ptr = Polycore.FixedShaderBinding(shader)
	end
end

function FixedShaderBinding:addTexture(name, texture)
	return Polycore.FixedShaderBinding_addTexture(self.__ptr, name, texture.__ptr)
end

function FixedShaderBinding:addCubemap(name, cubemap)
	return Polycore.FixedShaderBinding_addCubemap(self.__ptr, name, cubemap.__ptr)
end

function FixedShaderBinding:addParam(type, name, value)
	return Polycore.FixedShaderBinding_addParam(self.__ptr, type, name, value)
end

function FixedShaderBinding:getDiffuseTexture()
	return Polycore.FixedShaderBinding_getDiffuseTexture(self.__ptr)
end

