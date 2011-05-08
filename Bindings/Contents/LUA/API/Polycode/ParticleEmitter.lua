class "ParticleEmitter"



CONTINUOUS_EMITTER = 0
TRIGGERED_EMITTER = 1
CLOUD_EMITTER = 2
function ParticleEmitter:__index__(name)
	if name == "particleSpeedMod" then
		return Polycore.ParticleEmitter_get_particleSpeedMod(self.__ptr)
	elseif name == "brightnessDeviation" then
		return Polycore.ParticleEmitter_get_brightnessDeviation(self.__ptr)
	elseif name == "lifespan" then
		return Polycore.ParticleEmitter_get_lifespan(self.__ptr)
	elseif name == "rotationFollowsPath" then
		return Polycore.ParticleEmitter_get_rotationFollowsPath(self.__ptr)
	end
end


function ParticleEmitter:__set_callback(name,value)
	if name == "particleSpeedMod" then
		Polycore.ParticleEmitter_set_particleSpeedMod(self.__ptr, value)
		return true
	elseif name == "brightnessDeviation" then
		Polycore.ParticleEmitter_set_brightnessDeviation(self.__ptr, value)
		return true
	elseif name == "lifespan" then
		Polycore.ParticleEmitter_set_lifespan(self.__ptr, value)
		return true
	elseif name == "rotationFollowsPath" then
		Polycore.ParticleEmitter_set_rotationFollowsPath(self.__ptr, value)
		return true
	end
	return false
end


function ParticleEmitter:createParticles()
	local retVal =  Polycore.ParticleEmitter_createParticles(self.__ptr)
end

function ParticleEmitter:setRotationSpeed(speed)
	local retVal = Polycore.ParticleEmitter_setRotationSpeed(self.__ptr, speed)
end

function ParticleEmitter:setStartingColor(c)
	local retVal = Polycore.ParticleEmitter_setStartingColor(self.__ptr, c.__ptr)
end

function ParticleEmitter:setEndingColor(c)
	local retVal = Polycore.ParticleEmitter_setEndingColor(self.__ptr, c.__ptr)
end

function ParticleEmitter:setParticleBlendingMode(mode)
	local retVal = Polycore.ParticleEmitter_setParticleBlendingMode(self.__ptr, mode)
end

function ParticleEmitter:setDepthWrite(val)
	local retVal = Polycore.ParticleEmitter_setDepthWrite(self.__ptr, val)
end

function ParticleEmitter:setDepthTest(val)
	local retVal = Polycore.ParticleEmitter_setDepthTest(self.__ptr, val)
end

function ParticleEmitter:setAlphaTest(val)
	local retVal = Polycore.ParticleEmitter_setAlphaTest(self.__ptr, val)
end

function ParticleEmitter:enablePerlin(val)
	local retVal = Polycore.ParticleEmitter_enablePerlin(self.__ptr, val)
end

function ParticleEmitter:setBillboardMode(mode)
	local retVal = Polycore.ParticleEmitter_setBillboardMode(self.__ptr, mode)
end

function ParticleEmitter:enableEmitter(val)
	local retVal = Polycore.ParticleEmitter_enableEmitter(self.__ptr, val)
end

function ParticleEmitter:emitterEnabled()
	local retVal =  Polycore.ParticleEmitter_emitterEnabled(self.__ptr)
	return retVal
end

function ParticleEmitter:setEmitterRadius(rad)
	local retVal = Polycore.ParticleEmitter_setEmitterRadius(self.__ptr, rad)
end

function ParticleEmitter:setStartingScaleModifier(mod)
	local retVal = Polycore.ParticleEmitter_setStartingScaleModifier(self.__ptr, mod)
end

function ParticleEmitter:setEndingScaleModifier(mod)
	local retVal = Polycore.ParticleEmitter_setEndingScaleModifier(self.__ptr, mod)
end

function ParticleEmitter:setEmitRotationVector(rotVector)
	local retVal = Polycore.ParticleEmitter_setEmitRotationVector(self.__ptr, rotVector.__ptr)
end

function ParticleEmitter:setEmitRotationDeviance(rotVector)
	local retVal = Polycore.ParticleEmitter_setEmitRotationDeviance(self.__ptr, rotVector.__ptr)
end

function ParticleEmitter:setAllAtOnce(val)
	local retVal = Polycore.ParticleEmitter_setAllAtOnce(self.__ptr, val)
end

function ParticleEmitter:Trigger()
	local retVal =  Polycore.ParticleEmitter_Trigger(self.__ptr)
end

function ParticleEmitter:resetParticle(particle)
	local retVal = Polycore.ParticleEmitter_resetParticle(self.__ptr, particle.__ptr)
end

function ParticleEmitter:setPerlinModSize(size)
	local retVal = Polycore.ParticleEmitter_setPerlinModSize(self.__ptr, size)
end

function ParticleEmitter:setParticleCount(count)
	local retVal = Polycore.ParticleEmitter_setParticleCount(self.__ptr, count)
end

function ParticleEmitter:addParticleBody(particleBody)
	local retVal = Polycore.ParticleEmitter_addParticleBody(self.__ptr, particleBody.__ptr)
end

function ParticleEmitter:getBaseMatrix()
	local retVal =  Polycore.ParticleEmitter_getBaseMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ParticleEmitter:updateEmitter()
	local retVal =  Polycore.ParticleEmitter_updateEmitter(self.__ptr)
end



function ParticleEmitter:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ParticleEmitter(self.__ptr)
end
