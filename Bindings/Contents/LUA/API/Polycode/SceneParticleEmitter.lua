require "Polycode/SceneEntity"

class "SceneParticleEmitter" (SceneEntity)







function SceneParticleEmitter:SceneParticleEmitter(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneEntity" then
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
		self.__ptr = Polycore.SceneParticleEmitter(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.SceneParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function SceneParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.SceneParticleEmitter_getBaseMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneParticleEmitter:Update()
	local retVal =  Polycore.SceneParticleEmitter_Update(self.__ptr)
end



function SceneParticleEmitter:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneParticleEmitter(self.__ptr)
end
