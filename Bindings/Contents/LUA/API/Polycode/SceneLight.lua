require "Polycode/SceneEntity"

class "SceneLight" (SceneEntity)

function SceneLight:SceneLight(type, intensity, distance, parentScene)
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneLight(type, intensity, distance, parentScene)
	end
end

function SceneLight:getIntensity()
	return Polycore.SceneLight_getIntensity(self.__ptr)
end

function SceneLight:getDistance()
	return Polycore.SceneLight_getDistance(self.__ptr)
end

function SceneLight:getType()
	return Polycore.SceneLight_getType(self.__ptr)
end

function SceneLight:renderDepthMap(scene)
	return Polycore.SceneLight_renderDepthMap(self.__ptr, scene.__ptr)
end

function SceneLight:Render()
	return Polycore.SceneLight_Render(self.__ptr)
end

function SceneLight:getLightViewMatrix()
	return Polycore.SceneLight_getLightViewMatrix(self.__ptr)
end

function SceneLight:getZBufferTexture()
	return Polycore.SceneLight_getZBufferTexture(self.__ptr)
end

function SceneLight:setLightColor(r, g, b)
	return Polycore.SceneLight_setLightColor(self.__ptr, r, g, b)
end

function SceneLight:enableShadows(val, resolution)
	return Polycore.SceneLight_enableShadows(self.__ptr, val, resolution)
end

function SceneLight:setShadowMapFOV(fov)
	return Polycore.SceneLight_setShadowMapFOV(self.__ptr, fov)
end

function SceneLight:areShadowsEnabled()
	return Polycore.SceneLight_areShadowsEnabled(self.__ptr)
end

function SceneLight:getLightType()
	return Polycore.SceneLight_getLightType(self.__ptr)
end

