require "Polycode/ShaderBinding"

class "GLSLShaderBinding" (ShaderBinding)







function GLSLShaderBinding:GLSLShaderBinding(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "ShaderBinding" then
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
		self.__ptr = Polycore.GLSLShaderBinding(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function GLSLShaderBinding:addTexture(name, texture)
	local retVal = Polycore.GLSLShaderBinding_addTexture(self.__ptr, name, texture.__ptr)
end

function GLSLShaderBinding:addCubemap(name, cubemap)
	local retVal = Polycore.GLSLShaderBinding_addCubemap(self.__ptr, name, cubemap.__ptr)
end

function GLSLShaderBinding:clearTexture(name)
	local retVal = Polycore.GLSLShaderBinding_clearTexture(self.__ptr, name)
end

function GLSLShaderBinding:addParam(type, name, value)
	local retVal = Polycore.GLSLShaderBinding_addParam(self.__ptr, type, name, value)
end



function GLSLShaderBinding:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_GLSLShaderBinding(self.__ptr)
end
