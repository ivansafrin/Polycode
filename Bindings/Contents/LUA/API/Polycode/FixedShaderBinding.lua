require "Polycode/ShaderBinding"

class "FixedShaderBinding" (ShaderBinding)







function FixedShaderBinding:FixedShaderBinding(...)
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
		self.__ptr = Polycore.FixedShaderBinding(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function FixedShaderBinding:addTexture(name, texture)
	local retVal = Polycore.FixedShaderBinding_addTexture(self.__ptr, name.__ptr, texture.__ptr)
end

function FixedShaderBinding:addCubemap(name, cubemap)
	local retVal = Polycore.FixedShaderBinding_addCubemap(self.__ptr, name.__ptr, cubemap.__ptr)
end

function FixedShaderBinding:addParam(type, name, value)
	local retVal = Polycore.FixedShaderBinding_addParam(self.__ptr, type.__ptr, name.__ptr, value.__ptr)
end

function FixedShaderBinding:getDiffuseTexture()
	local retVal =  Polycore.FixedShaderBinding_getDiffuseTexture(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function FixedShaderBinding:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_FixedShaderBinding(self.__ptr)
end
