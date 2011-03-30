require "Polycode/SceneEntity"

class "SceneParticleEmitter" (SceneEntity)

function SceneParticleEmitter:SceneParticleEmitter(imageFile, particleMesh, emitter, particleParentScene, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneParticleEmitter(imageFile, particleMesh, emitter, particleParentScene, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation)
	end
end

function SceneParticleEmitter:addParticleBody(particleBody)
	return Polycore.SceneParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function SceneParticleEmitter:getBaseMatrix()
	return Polycore.SceneParticleEmitter_getBaseMatrix(self.__ptr)
end

function SceneParticleEmitter:Update()
	return Polycore.SceneParticleEmitter_Update(self.__ptr)
end

