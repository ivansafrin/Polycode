require "Polycode/SceneEntity"

class "Camera" (SceneEntity)







function Camera:Camera(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Camera(unpack(arg))
	end
end

function Camera:buildFrustrumPlanes()
	local retVal =  Polycore.Camera_buildFrustrumPlanes(self.__ptr)
end

function Camera:isSphereInFrustrum(pos, fRadius)
	local retVal = Polycore.Camera_isSphereInFrustrum(self.__ptr, pos.__ptr, fRadius)
	return retVal
end

function Camera:canSee(entity)
	local retVal = Polycore.Camera_canSee(self.__ptr, entity.__ptr)
	return retVal
end

function Camera:setOrthoMode(mode)
	local retVal = Polycore.Camera_setOrthoMode(self.__ptr, mode)
end

function Camera:getOrthoMode()
	local retVal =  Polycore.Camera_getOrthoMode(self.__ptr)
	return retVal
end

function Camera:setFOV(fov)
	local retVal = Polycore.Camera_setFOV(self.__ptr, fov)
end

function Camera:getFOV()
	local retVal =  Polycore.Camera_getFOV(self.__ptr)
	return retVal
end

function Camera:setParentScene(parentScene)
	local retVal = Polycore.Camera_setParentScene(self.__ptr, parentScene.__ptr)
end

function Camera:doCameraTransform()
	local retVal =  Polycore.Camera_doCameraTransform(self.__ptr)
end

function Camera:setLightDepthTexture(texture)
	local retVal = Polycore.Camera_setLightDepthTexture(self.__ptr, texture.__ptr)
end

function Camera:hasFilterShader()
	local retVal =  Polycore.Camera_hasFilterShader(self.__ptr)
	return retVal
end

function Camera:drawFilter()
	local retVal =  Polycore.Camera_drawFilter(self.__ptr)
end

function Camera:setExposureLevel(level)
	local retVal = Polycore.Camera_setExposureLevel(self.__ptr, level)
end

function Camera:getExposureLevel()
	local retVal =  Polycore.Camera_getExposureLevel(self.__ptr)
	return retVal
end

function Camera:createPostFilter(shaderMaterial)
	local retVal = Polycore.Camera_createPostFilter(self.__ptr, shaderMaterial.__ptr)
end

function Camera:setPostFilter(shaderName)
	local retVal = Polycore.Camera_setPostFilter(self.__ptr, shaderName)
end

