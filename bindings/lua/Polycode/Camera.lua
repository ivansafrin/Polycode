require "Polycode/Entity"

class "Camera" (Entity)

Camera.ORTHO_SIZE_MANUAL = 0
Camera.ORTHO_SIZE_LOCK_HEIGHT = 1
Camera.ORTHO_SIZE_LOCK_WIDTH = 2
Camera.ORTHO_SIZE_VIEWPORT = 3
Camera.PERSPECTIVE_FOV = 4
Camera.PERSPECTIVE_FRUSTUM = 5
Camera.MANUAL_MATRIX = 6

function Camera:__getvar(name)
	if name == "frustumCulling" then
		return Polycode.Camera_get_frustumCulling(self.__ptr)
	elseif name == "topLeftOrtho" then
		return Polycode.Camera_get_topLeftOrtho(self.__ptr)
	elseif name == "cameraShift" then
		local retVal = Polycode.Camera_get_cameraShift(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Entity["__getvar"] ~= nil then
		return Entity.__getvar(self, name)
	end
end

function Camera:__setvar(name,value)
	if name == "frustumCulling" then
		Polycode.Camera_set_frustumCulling(self.__ptr, value)
		return true
	elseif name == "topLeftOrtho" then
		Polycode.Camera_set_topLeftOrtho(self.__ptr, value)
		return true
	elseif name == "cameraShift" then
		Polycode.Camera_set_cameraShift(self.__ptr, value.__ptr)
		return true
	end
	if Entity["__setvar"] ~= nil then
		return Entity.__setvar(self, name, value)
	else
		return false
	end
end
function Camera:Camera(...)
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
		self.__ptr = Polycode.Camera(unpack(arg))
	end
end

function Camera:buildFrustumPlanes()
	local retVal =  Polycode.Camera_buildFrustumPlanes(self.__ptr)
end

function Camera:isSphereInFrustum(pos, fRadius)
	local retVal = Polycode.Camera_isSphereInFrustum(self.__ptr, pos.__ptr, fRadius)
	return retVal
end

function Camera:isAABBInFrustum(aabb)
	local retVal = Polycode.Camera_isAABBInFrustum(self.__ptr, aabb.__ptr)
	return retVal
end

function Camera:setOrthoMode(mode)
	local retVal = Polycode.Camera_setOrthoMode(self.__ptr, mode)
end

function Camera:setOrthoSize(orthoSizeX, orthoSizeY)
	local retVal = Polycode.Camera_setOrthoSize(self.__ptr, orthoSizeX, orthoSizeY)
end

function Camera:setFrustumMode(left, right, bottom, top, front, back)
	local retVal = Polycode.Camera_setFrustumMode(self.__ptr, left, right, bottom, top, front, back)
end

function Camera:getOrthoMode()
	local retVal =  Polycode.Camera_getOrthoMode(self.__ptr)
	return retVal
end

function Camera:getOrthoSizeX()
	local retVal =  Polycode.Camera_getOrthoSizeX(self.__ptr)
	return retVal
end

function Camera:getOrthoSizeY()
	local retVal =  Polycode.Camera_getOrthoSizeY(self.__ptr)
	return retVal
end

function Camera:setFOV(fov)
	local retVal = Polycode.Camera_setFOV(self.__ptr, fov)
end

function Camera:getFOV()
	local retVal =  Polycode.Camera_getFOV(self.__ptr)
	return retVal
end

function Camera:setClippingPlanes(nearClipPlane, farClipPlane)
	local retVal = Polycode.Camera_setClippingPlanes(self.__ptr, nearClipPlane, farClipPlane)
end

function Camera:getNearClippingPlane()
	local retVal =  Polycode.Camera_getNearClippingPlane(self.__ptr)
	return retVal
end

function Camera:getFarClippingPlane()
	local retVal =  Polycode.Camera_getFarClippingPlane(self.__ptr)
	return retVal
end

function Camera:setParentScene(parentScene)
	local retVal = Polycode.Camera_setParentScene(self.__ptr, parentScene.__ptr)
end

function Camera:getParentScene()
	local retVal =  Polycode.Camera_getParentScene(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Scene"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:createProjectionMatrix()
	local retVal =  Polycode.Camera_createProjectionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:hasFilterShader()
	local retVal =  Polycode.Camera_hasFilterShader(self.__ptr)
	return retVal
end

function Camera:drawFilter(targetBuffer)
	local retVal = Polycode.Camera_drawFilter(self.__ptr, targetBuffer.__ptr)
end

function Camera:setPostFilter(material)
	local retVal = Polycode.Camera_setPostFilter(self.__ptr, material.__ptr)
end

function Camera:setPostFilterByName(shaderName)
	local retVal = Polycode.Camera_setPostFilterByName(self.__ptr, shaderName)
end

function Camera:removePostFilter()
	local retVal =  Polycode.Camera_removePostFilter(self.__ptr)
end

function Camera:getScreenShaderMaterial()
	local retVal =  Polycode.Camera_getScreenShaderMaterial(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<Material>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycode.Camera_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycode.Camera_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function Camera:getProjectionMatrix()
	local retVal =  Polycode.Camera_getProjectionMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:setCustomProjectionMatrix(matrix)
	local retVal = Polycode.Camera_setCustomProjectionMatrix(self.__ptr, matrix.__ptr)
end

function Camera:getViewport()
	local retVal =  Polycode.Camera_getViewport(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Rectangle"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:setViewport(viewport)
	local retVal = Polycode.Camera_setViewport(self.__ptr, viewport.__ptr)
end

function Camera:setOrthoSizeMode(orthoSizeMode)
	local retVal = Polycode.Camera_setOrthoSizeMode(self.__ptr, orthoSizeMode)
end

function Camera:getOrthoSizeMode()
	local retVal =  Polycode.Camera_getOrthoSizeMode(self.__ptr)
	return retVal
end

function Camera:setProjectionMode(mode)
	local retVal = Polycode.Camera_setProjectionMode(self.__ptr, mode)
end

function Camera:getProjectionMode()
	local retVal =  Polycode.Camera_getProjectionMode(self.__ptr)
	return retVal
end

function Camera:projectRayFrom2DCoordinate(coordinate, viewport)
	local retVal = Polycode.Camera_projectRayFrom2DCoordinate(self.__ptr, coordinate.__ptr, viewport.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:renderFullScreenQuad(drawBuffer, shaderPass)
	local retVal = Polycode.Camera_renderFullScreenQuad(self.__ptr, drawBuffer.__ptr, shaderPass)
end

function Camera:getShaderPass(index)
	local retVal = Polycode.Camera_getShaderPass(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderPass"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Camera:getNumShaderPasses()
	local retVal =  Polycode.Camera_getNumShaderPasses(self.__ptr)
	return retVal
end

function Camera:__delete()
	if self then Polycode.delete_Camera(self.__ptr) end
end
