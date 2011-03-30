require "Polycode/ScreenEntity"

class "ScreenParticleEmitter" (ScreenEntity)

function ScreenParticleEmitter:ScreenParticleEmitter(imageFile, particleMesh, emitter, particleParentScreen, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenParticleEmitter(imageFile, particleMesh, emitter, particleParentScreen, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation)
	end
end

function ScreenParticleEmitter:addParticleBody(particleBody)
	return Polycore.ScreenParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function ScreenParticleEmitter:getBaseMatrix()
	return Polycore.ScreenParticleEmitter_getBaseMatrix(self.__ptr)
end

function ScreenParticleEmitter:Update()
	return Polycore.ScreenParticleEmitter_Update(self.__ptr)
end

