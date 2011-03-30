require "Polycode/Cubemap"

class "OpenGLCubemap" (Cubemap)

function OpenGLCubemap:OpenGLCubemap(t0, t1, t2, t3, t4, t5)
	if self.__ptr == nil then
		self.__ptr = Polycore.OpenGLCubemap(t0, t1, t2, t3, t4, t5)
	end
end

function OpenGLCubemap:getTextureID()
	return Polycore.OpenGLCubemap_getTextureID(self.__ptr)
end

