require "Polycode/SceneEntity"

class "Camera" (SceneEntity)

function Camera:Camera(parentScene)
	if self.__ptr == nil then
		self.__ptr = Polycore.Camera(parentScene)
	end
end

function Camera:buildFrustrumPlanes()
	return Polycore.Camera_buildFrustrumPlanes(self.__ptr)
end

function Camera:isSphereInFrustrum(pos, fRadius)
	return Polycore.Camera_isSphereInFrustrum(self.__ptr, pos.__ptr, fRadius)
end

function Camera:canSee(entity)
	return Polycore.Camera_canSee(self.__ptr, entity.__ptr)
end

function Camera:setOrthoMode(mode)
	return Polycore.Camera_setOrthoMode(self.__ptr, mode)
end

function Camera:getOrthoMode()
	return Polycore.Camera_getOrthoMode(self.__ptr)
end

function Camera:setFOV(fov)
	return Polycore.Camera_setFOV(self.__ptr, fov)
end

function Camera:getFOV()
	return Polycore.Camera_getFOV(self.__ptr)
end

function Camera:doCameraTransform()
	return Polycore.Camera_doCameraTransform(self.__ptr)
end

function Camera:setLightDepthTexture(texture)
	return Polycore.Camera_setLightDepthTexture(self.__ptr, texture.__ptr)
end

function Camera:setParentScene(parentScene)
	return Polycore.Camera_setParentScene(self.__ptr, parentScene.__ptr)
end

function Camera:hasFilterShader()
	return Polycore.Camera_hasFilterShader(self.__ptr)
end

function Camera:drawFilter()
	return Polycore.Camera_drawFilter(self.__ptr)
end

function Camera:setExposureLevel(level)
	return Polycore.Camera_setExposureLevel(self.__ptr, level)
end

function Camera:getExposureLevel()
	return Polycore.Camera_getExposureLevel(self.__ptr)
end

function Camera:createPostFilter(shaderMaterial)
	return Polycore.Camera_createPostFilter(self.__ptr, shaderMaterial.__ptr)
end

function Camera:setPostFilter(shaderName)
	return Polycore.Camera_setPostFilter(self.__ptr, shaderName)
end

