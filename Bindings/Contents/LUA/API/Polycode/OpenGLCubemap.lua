require "Polycode/Cubemap"

class "OpenGLCubemap" (Cubemap)







function OpenGLCubemap:OpenGLCubemap(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.OpenGLCubemap(unpack(arg))
	end
end

function OpenGLCubemap:getTextureID()
	local retVal =  Polycore.OpenGLCubemap_getTextureID(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = GLuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

