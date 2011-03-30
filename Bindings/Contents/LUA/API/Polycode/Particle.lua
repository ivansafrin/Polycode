class "Particle"

function Particle:Particle(particleType, isScreenParticle, material, texture, particleMesh)
	if self.__ptr == nil then
		self.__ptr = Polycore.Particle(particleType, isScreenParticle, material, texture, particleMesh)
	end
end

function Particle:Reset(continuious)
	return Polycore.Particle_Reset(self.__ptr, continuious)
end

function Particle:createSceneParticle(particleType, texture, particleMesh)
	return Polycore.Particle_createSceneParticle(self.__ptr, particleType, texture.__ptr, particleMesh.__ptr)
end

function Particle:createScreenParticle(particleType, texture, particleMesh)
	return Polycore.Particle_createScreenParticle(self.__ptr, particleType, texture.__ptr, particleMesh.__ptr)
end

