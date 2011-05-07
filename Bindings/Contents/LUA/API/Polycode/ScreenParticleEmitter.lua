require "Polycode/ScreenEntity"

class "ScreenParticleEmitter" (ScreenEntity)







function ScreenParticleEmitter:ScreenParticleEmitter(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenParticleEmitter(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ScreenParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.ScreenParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function ScreenParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.ScreenParticleEmitter_getBaseMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ScreenParticleEmitter:Update()
	local retVal =  Polycore.ScreenParticleEmitter_Update(self.__ptr)
end

