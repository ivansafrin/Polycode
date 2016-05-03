require "Polycode/SceneMesh"

class "SceneParticleEmitter" (SceneMesh)



SceneParticleEmitter.PARTICLE_TYPE_POINT = 0
SceneParticleEmitter.PARTICLE_TYPE_QUAD = 1
SceneParticleEmitter.PARTICLE_TYPE_MESH = 2
function SceneParticleEmitter:__getvar(name)
	if name == "useScaleCurve" then
		return Polycore.SceneParticleEmitter_get_useScaleCurve(self.__ptr)
	elseif name == "scaleCurve" then
		local retVal = Polycore.SceneParticleEmitter_get_scaleCurve(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "useColorCurves" then
		return Polycore.SceneParticleEmitter_get_useColorCurves(self.__ptr)
	elseif name == "colorCurveR" then
		local retVal = Polycore.SceneParticleEmitter_get_colorCurveR(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveG" then
		local retVal = Polycore.SceneParticleEmitter_get_colorCurveG(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveB" then
		local retVal = Polycore.SceneParticleEmitter_get_colorCurveB(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorCurveA" then
		local retVal = Polycore.SceneParticleEmitter_get_colorCurveA(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["BezierCurve"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "colorDeviation" then
		local retVal = Polycore.SceneParticleEmitter_get_colorDeviation(self.__ptr)
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
		Polycore.SceneParticleEmitter_set_useScaleCurve(self.__ptr, value)
		return true
	elseif name == "scaleCurve" then
		Polycore.SceneParticleEmitter_set_scaleCurve(self.__ptr, value.__ptr)
		return true
	elseif name == "useColorCurves" then
		Polycore.SceneParticleEmitter_set_useColorCurves(self.__ptr, value)
		return true
	elseif name == "colorCurveR" then
		Polycore.SceneParticleEmitter_set_colorCurveR(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveG" then
		Polycore.SceneParticleEmitter_set_colorCurveG(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveB" then
		Polycore.SceneParticleEmitter_set_colorCurveB(self.__ptr, value.__ptr)
		return true
	elseif name == "colorCurveA" then
		Polycore.SceneParticleEmitter_set_colorCurveA(self.__ptr, value.__ptr)
		return true
	elseif name == "colorDeviation" then
		Polycore.SceneParticleEmitter_set_colorDeviation(self.__ptr, value.__ptr)
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
		self.__ptr = Polycore.SceneParticleEmitter(unpack(arg))
	end
end

function SceneParticleEmitter:setParticleCount(newParticleCount)
	local retVal = Polycore.SceneParticleEmitter_setParticleCount(self.__ptr, newParticleCount)
end

function SceneParticleEmitter:getParticleCount()
	local retVal =  Polycore.SceneParticleEmitter_getParticleCount(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleLifetime(lifetime)
	local retVal = Polycore.SceneParticleEmitter_setParticleLifetime(self.__ptr, lifetime)
end

function SceneParticleEmitter:getParticleLifetime()
	local retVal =  Polycore.SceneParticleEmitter_getParticleLifetime(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setDirectionDeviation(newDeviation)
	local retVal = Polycore.SceneParticleEmitter_setDirectionDeviation(self.__ptr, newDeviation.__ptr)
end

function SceneParticleEmitter:getDirectionDeviation()
	local retVal =  Polycore.SceneParticleEmitter_getDirectionDeviation(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setEmitterSize(newSize)
	local retVal = Polycore.SceneParticleEmitter_setEmitterSize(self.__ptr, newSize.__ptr)
end

function SceneParticleEmitter:getEmitterSize()
	local retVal =  Polycore.SceneParticleEmitter_getEmitterSize(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setGravity(newGravity)
	local retVal = Polycore.SceneParticleEmitter_setGravity(self.__ptr, newGravity.__ptr)
end

function SceneParticleEmitter:getGravity()
	local retVal =  Polycore.SceneParticleEmitter_getGravity(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:fixedUpdate()
	local retVal =  Polycore.SceneParticleEmitter_fixedUpdate(self.__ptr)
end

function SceneParticleEmitter:Render(buffer)
	local retVal = Polycore.SceneParticleEmitter_Render(self.__ptr, buffer.__ptr)
end

function SceneParticleEmitter:updateParticles()
	local retVal =  Polycore.SceneParticleEmitter_updateParticles(self.__ptr)
end

function SceneParticleEmitter:rebuildParticles(buffer)
	local retVal = Polycore.SceneParticleEmitter_rebuildParticles(self.__ptr, buffer.__ptr)
end

function SceneParticleEmitter:triggerParticles(allAtOnce)
	local retVal = Polycore.SceneParticleEmitter_triggerParticles(self.__ptr, allAtOnce)
end

function SceneParticleEmitter:enableParticleSystem(val)
	local retVal = Polycore.SceneParticleEmitter_enableParticleSystem(self.__ptr, val)
end

function SceneParticleEmitter:setUseFloorPlane(val)
	local retVal = Polycore.SceneParticleEmitter_setUseFloorPlane(self.__ptr, val)
end

function SceneParticleEmitter:setFloorPlaneOffset(floorPlaneOffset)
	local retVal = Polycore.SceneParticleEmitter_setFloorPlaneOffset(self.__ptr, floorPlaneOffset)
end

function SceneParticleEmitter:setFloorDamping(floorDamping)
	local retVal = Polycore.SceneParticleEmitter_setFloorDamping(self.__ptr, floorDamping)
end

function SceneParticleEmitter:setParticlesInWorldSpace(val)
	local retVal = Polycore.SceneParticleEmitter_setParticlesInWorldSpace(self.__ptr, val)
end

function SceneParticleEmitter:getParticlesInWorldSpace()
	local retVal =  Polycore.SceneParticleEmitter_getParticlesInWorldSpace(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setPerlinEnabled(val)
	local retVal = Polycore.SceneParticleEmitter_setPerlinEnabled(self.__ptr, val)
end

function SceneParticleEmitter:getPerlinEnabled()
	local retVal =  Polycore.SceneParticleEmitter_getPerlinEnabled(self.__ptr)
	return retVal
end

function SceneParticleEmitter:getParticleSpeed()
	local retVal =  Polycore.SceneParticleEmitter_getParticleSpeed(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleSpeed(speed)
	local retVal = Polycore.SceneParticleEmitter_setParticleSpeed(self.__ptr, speed)
end

function SceneParticleEmitter:setPerlinValue(perlinValue)
	local retVal = Polycore.SceneParticleEmitter_setPerlinValue(self.__ptr, perlinValue.__ptr)
end

function SceneParticleEmitter:getPerlinValue()
	local retVal =  Polycore.SceneParticleEmitter_getPerlinValue(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setParticleType(particleType)
	local retVal = Polycore.SceneParticleEmitter_setParticleType(self.__ptr, particleType)
end

function SceneParticleEmitter:getParticleType()
	local retVal =  Polycore.SceneParticleEmitter_getParticleType(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleSize(particleSize)
	local retVal = Polycore.SceneParticleEmitter_setParticleSize(self.__ptr, particleSize)
end

function SceneParticleEmitter:getParticleSize()
	local retVal =  Polycore.SceneParticleEmitter_getParticleSize(self.__ptr)
	return retVal
end

function SceneParticleEmitter:setParticleRotationSpeed(rotationSpeed)
	local retVal = Polycore.SceneParticleEmitter_setParticleRotationSpeed(self.__ptr, rotationSpeed.__ptr)
end

function SceneParticleEmitter:getParticleRotationSpeed()
	local retVal =  Polycore.SceneParticleEmitter_getParticleRotationSpeed(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setParticleDirection(direction)
	local retVal = Polycore.SceneParticleEmitter_setParticleDirection(self.__ptr, direction.__ptr)
end

function SceneParticleEmitter:getParticleDirection()
	local retVal =  Polycore.SceneParticleEmitter_getParticleDirection(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:setLoopParticles(val)
	local retVal = Polycore.SceneParticleEmitter_setLoopParticles(self.__ptr, val)
end

function SceneParticleEmitter:getLoopParticles()
	local retVal =  Polycore.SceneParticleEmitter_getLoopParticles(self.__ptr)
	return retVal
end

function SceneParticleEmitter:addSourceMesh(mesh)
	local retVal = Polycore.SceneParticleEmitter_addSourceMesh(self.__ptr, mesh.__ptr)
end

function SceneParticleEmitter:getNumSourceMeshes()
	local retVal =  Polycore.SceneParticleEmitter_getNumSourceMeshes(self.__ptr)
	return retVal
end

function SceneParticleEmitter:getSourcesMeshAtIndex(index)
	local retVal = Polycore.SceneParticleEmitter_getSourcesMeshAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Mesh"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:removeSourceMeshAtIndex(index)
	local retVal = Polycore.SceneParticleEmitter_removeSourceMeshAtIndex(self.__ptr, index)
end

function SceneParticleEmitter:positionParticle(index)
	local retVal = Polycore.SceneParticleEmitter_positionParticle(self.__ptr, index)
end

function SceneParticleEmitter:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneParticleEmitter_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneParticleEmitter:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneParticleEmitter_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneParticleEmitter:__delete()
	if self then Polycore.delete_SceneParticleEmitter(self.__ptr) end
end
