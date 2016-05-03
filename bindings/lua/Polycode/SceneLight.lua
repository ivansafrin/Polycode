require "Polycode/Entity"

class "SceneLight" (Entity)



SceneLight.POINT_LIGHT = 0
SceneLight.SPOT_LIGHT = 1




function SceneLight:SceneLight(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
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
		self.__ptr = Polycore.SceneLight(unpack(arg))
	end
end

function SceneLight:getIntensity()
	local retVal =  Polycore.SceneLight_getIntensity(self.__ptr)
	return retVal
end

function SceneLight:setIntensity(newIntensity)
	local retVal = Polycore.SceneLight_setIntensity(self.__ptr, newIntensity)
end

function SceneLight:setAttenuation(constantAttenuation, linearAttenuation, quadraticAttenuation)
	local retVal = Polycore.SceneLight_setAttenuation(self.__ptr, constantAttenuation, linearAttenuation, quadraticAttenuation)
end

function SceneLight:getConstantAttenuation()
	local retVal =  Polycore.SceneLight_getConstantAttenuation(self.__ptr)
	return retVal
end

function SceneLight:getLinearAttenuation()
	local retVal =  Polycore.SceneLight_getLinearAttenuation(self.__ptr)
	return retVal
end

function SceneLight:getQuadraticAttenuation()
	local retVal =  Polycore.SceneLight_getQuadraticAttenuation(self.__ptr)
	return retVal
end

function SceneLight:getType()
	local retVal =  Polycore.SceneLight_getType(self.__ptr)
	return retVal
end

function SceneLight:renderDepthMap(scene)
	local retVal = Polycore.SceneLight_renderDepthMap(self.__ptr, scene.__ptr)
end

function SceneLight:getZBufferTexture()
	local retVal =  Polycore.SceneLight_getZBufferTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLight:setSpecularLightColor(r, g, b, a)
	local retVal = Polycore.SceneLight_setSpecularLightColor(self.__ptr, r, g, b, a)
end

function SceneLight:setDiffuseLightColor(r, g, b, a)
	local retVal = Polycore.SceneLight_setDiffuseLightColor(self.__ptr, r, g, b, a)
end

function SceneLight:setLightColor(r, g, b, a)
	local retVal = Polycore.SceneLight_setLightColor(self.__ptr, r, g, b, a)
end

function SceneLight:setSpotlightProperties(spotlightCutoff, spotlightExponent)
	local retVal = Polycore.SceneLight_setSpotlightProperties(self.__ptr, spotlightCutoff, spotlightExponent)
end

function SceneLight:getSpotlightCutoff()
	local retVal =  Polycore.SceneLight_getSpotlightCutoff(self.__ptr)
	return retVal
end

function SceneLight:getSpotlightExponent()
	local retVal =  Polycore.SceneLight_getSpotlightExponent(self.__ptr)
	return retVal
end

function SceneLight:enableShadows(val, resolution)
	local retVal = Polycore.SceneLight_enableShadows(self.__ptr, val, resolution)
end

function SceneLight:setShadowMapFOV(fov)
	local retVal = Polycore.SceneLight_setShadowMapFOV(self.__ptr, fov)
end

function SceneLight:getShadowMapFOV()
	local retVal =  Polycore.SceneLight_getShadowMapFOV(self.__ptr)
	return retVal
end

function SceneLight:getShadowMapResolution()
	local retVal =  Polycore.SceneLight_getShadowMapResolution(self.__ptr)
	return retVal
end

function SceneLight:areShadowsEnabled()
	local retVal =  Polycore.SceneLight_areShadowsEnabled(self.__ptr)
	return retVal
end

function SceneLight:getLightType()
	local retVal =  Polycore.SceneLight_getLightType(self.__ptr)
	return retVal
end

function SceneLight:setLightImportance(newImportance)
	local retVal = Polycore.SceneLight_setLightImportance(self.__ptr, newImportance)
end

function SceneLight:getLightImportance()
	local retVal =  Polycore.SceneLight_getLightImportance(self.__ptr)
	return retVal
end

function SceneLight:setLightType(lightType)
	local retVal = Polycore.SceneLight_setLightType(self.__ptr, lightType)
end

function SceneLight:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneLight_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLight:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycore.SceneLight_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneLight:getParentScene()
	local retVal =  Polycore.SceneLight_getParentScene(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Scene"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLight:setParentScene(scene)
	local retVal = Polycore.SceneLight_setParentScene(self.__ptr, scene.__ptr)
end

function SceneLight:getSpotlightCamera()
	local retVal =  Polycore.SceneLight_getSpotlightCamera(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Camera"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLight:getLightInfo()
	local retVal =  Polycore.SceneLight_getLightInfo(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["LightInfo"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneLight:__delete()
	if self then Polycore.delete_SceneLight(self.__ptr) end
end
