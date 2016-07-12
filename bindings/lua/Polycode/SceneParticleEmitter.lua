require "Polycode/SceneMesh"

class "SceneParticleEmitter" (SceneMesh)

SceneParticleEmitter.PARTICLE_TYPE_POINT = 0
SceneParticleEmitter.PARTICLE_TYPE_QUAD = 1
SceneParticleEmitter.PARTICLE_TYPE_MESH = 2

function SceneParticleEmitter:__getvar(name)
	if name == "useScaleCurve" then
		return Polycode.SceneParticleEmitter_get_useScaleCurve(self.__ptr)
	elseif name == "scaleCurve" then
		local retVal = Polycode.SceneParticleEmitter_get_scaleCurve(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useColorCurves" then
		return Polycode.SceneParticleEmitter_get_useColorCurves(self.__ptr)
	elseif name == "colorCurveR" then
		local retVal = Polycode.SceneParticleEmitter_get_colorCurveR(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveG" then
		local retVal = Polycode.SceneParticleEmitter_get_colorCurveG(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveB" then
		local retVal = Polycode.SceneParticleEmitter_get_colorCurveB(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveA" then
		local retVal = Polycode.SceneParticleEmitter_get_colorCurveA(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorDeviation" then
		local retVal = Polycode.SceneParticleEmitter_get_colorDeviation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if SceneMesh["__getvar"] ~= nil then
		return SceneMesh.__getvar(self, name)
	end
end

function SceneParticleEmitter:__setvar(name,value)
	if name == "useScaleCurve" then
		Polycode.SceneParticleEmitter_set_useScaleCurve(self.__ptr, value)
		return true
	elseif name == "scaleCurve" then
		Polycode.SceneParticleEmitter_set_scaleCurve(self.__ptr, value.__ptr)
		return true
	elseif name == "useColorCurves" then
		Polycode.SceneParticleEmitter_set_useColorCurves(self.__ptr, value)
		return true
	elseif name == "colorCurveR" then
		Polycode.SceneParticleEmitter_set_colorCurveR(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveG" then
		Polycode.SceneParticleEmitter_set_colorCurveG(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveB" then
		Polycode.SceneParticleEmitter_set_colorCurveB(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveA" then
		Polycode.SceneParticleEmitter_set_colorCurveA(self.__ptr, value.__ptr)
		return true
	elseif name == "colorDeviation" then
		Polycode.SceneParticleEmitter_set_colorDeviation(self.__ptr, value.__ptr)
		return true
	end
	if SceneMesh["__setvar"] ~= nil then
		return SceneMesh.__setvar(self, name, value)
	else
		return false
	end
end
function SceneParticleEmitter:SceneParticleEmitter(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "SceneMesh" then
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
		self.__ptr = Polycode.SceneParticleEmitter(unpack(arg))
	end
end

function SceneParticleEmitter:setParticleCount(newParticleCount)
	local retVal = Polycode.SceneParticleEmitter_setParticleCount(self.__ptr, newParticleCount)
end

function SceneParticleEmitter:getParticleCount()
	local retVal =  Polycode.SceneParticleEmitter_getParticleCount(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleLifetime(lifetime)
	local retVal = Polycode.SceneParticleEmitter_setParticleLifetime(self.__ptr, lifetime)
end

function SceneParticleEmitter:getParticleLifetime()
	local retVal =  Polycode.SceneParticleEmitter_getParticleLifetime(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setDirectionDeviation(newDeviation)
	local retVal = Polycode.SceneParticleEmitter_setDirectionDeviation(self.__ptr, newDeviation.__ptr)
end

function SceneParticleEmitter:getDirectionDeviation()
	local retVal =  Polycode.SceneParticleEmitter_getDirectionDeviation(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setEmitterSize(newSize)
	local retVal = Polycode.SceneParticleEmitter_setEmitterSize(self.__ptr, newSize.__ptr)
end

function SceneParticleEmitter:getEmitterSize()
	local retVal =  Polycode.SceneParticleEmitter_getEmitterSize(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setGravity(newGravity)
	local retVal = Polycode.SceneParticleEmitter_setGravity(self.__ptr, newGravity.__ptr)
end

function SceneParticleEmitter:getGravity()
	local retVal =  Polycode.SceneParticleEmitter_getGravity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:fixedUpdate()
	local retVal =  Polycode.SceneParticleEmitter_fixedUpdate(self.__ptr)
end

function SceneParticleEmitter:updateParticles()
	local retVal =  Polycode.SceneParticleEmitter_updateParticles(self.__ptr)
end

function SceneParticleEmitter:triggerParticles(allAtOnce)
	local retVal = Polycode.SceneParticleEmitter_triggerParticles(self.__ptr, allAtOnce)
end

function SceneParticleEmitter:enableParticleSystem(val)
	local retVal = Polycode.SceneParticleEmitter_enableParticleSystem(self.__ptr, val)
end

function SceneParticleEmitter:setUseFloorPlane(val)
	local retVal = Polycode.SceneParticleEmitter_setUseFloorPlane(self.__ptr, val)
end

function SceneParticleEmitter:setFloorPlaneOffset(floorPlaneOffset)
	local retVal = Polycode.SceneParticleEmitter_setFloorPlaneOffset(self.__ptr, floorPlaneOffset)
end

function SceneParticleEmitter:setFloorDamping(floorDamping)
	local retVal = Polycode.SceneParticleEmitter_setFloorDamping(self.__ptr, floorDamping)
end

function SceneParticleEmitter:setParticlesInWorldSpace(val)
	local retVal = Polycode.SceneParticleEmitter_setParticlesInWorldSpace(self.__ptr, val)
end

function SceneParticleEmitter:getParticlesInWorldSpace()
	local retVal =  Polycode.SceneParticleEmitter_getParticlesInWorldSpace(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setPerlinEnabled(val)
	local retVal = Polycode.SceneParticleEmitter_setPerlinEnabled(self.__ptr, val)
end

function SceneParticleEmitter:getPerlinEnabled()
	local retVal =  Polycode.SceneParticleEmitter_getPerlinEnabled(self.__ptr)
	return retVal
end

function SceneParticleEmitter:getParticleSpeed()
	local retVal =  Polycode.SceneParticleEmitter_getParticleSpeed(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleSpeed(speed)
	local retVal = Polycode.SceneParticleEmitter_setParticleSpeed(self.__ptr, speed)
end

function SceneParticleEmitter:setPerlinValue(perlinValue)
	local retVal = Polycode.SceneParticleEmitter_setPerlinValue(self.__ptr, perlinValue.__ptr)
end

function SceneParticleEmitter:getPerlinValue()
	local retVal =  Polycode.SceneParticleEmitter_getPerlinValue(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setParticleType(particleType)
	local retVal = Polycode.SceneParticleEmitter_setParticleType(self.__ptr, particleType)
end

function SceneParticleEmitter:getParticleType()
	local retVal =  Polycode.SceneParticleEmitter_getParticleType(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleSize(particleSize)
	local retVal = Polycode.SceneParticleEmitter_setParticleSize(self.__ptr, particleSize)
end

function SceneParticleEmitter:getParticleSize()
	local retVal =  Polycode.SceneParticleEmitter_getParticleSize(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleRotationSpeed(rotationSpeed)
	local retVal = Polycode.SceneParticleEmitter_setParticleRotationSpeed(self.__ptr, rotationSpeed.__ptr)
end

function SceneParticleEmitter:getParticleRotationSpeed()
	local retVal =  Polycode.SceneParticleEmitter_getParticleRotationSpeed(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setParticleDirection(direction)
	local retVal = Polycode.SceneParticleEmitter_setParticleDirection(self.__ptr, direction.__ptr)
end

function SceneParticleEmitter:getParticleDirection()
	local retVal =  Polycode.SceneParticleEmitter_getParticleDirection(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setLoopParticles(val)
	local retVal = Polycode.SceneParticleEmitter_setLoopParticles(self.__ptr, val)
end

function SceneParticleEmitter:getLoopParticles()
	local retVal =  Polycode.SceneParticleEmitter_getLoopParticles(self.__ptr)
	return retVal
end

function SceneParticleEmitter:getNumSourceMeshes()
	local retVal =  Polycode.SceneParticleEmitter_getNumSourceMeshes(self.__ptr)
	return retVal
end

function SceneParticleEmitter:removeSourceMeshAtIndex(index)
	local retVal = Polycode.SceneParticleEmitter_removeSourceMeshAtIndex(self.__ptr, index)
end

function SceneParticleEmitter:positionParticle(index)
	local retVal = Polycode.SceneParticleEmitter_positionParticle(self.__ptr, index)
end

function SceneParticleEmitter:__delete()
	if self then Polycode.delete_SceneParticleEmitter(self.__ptr) end
end
