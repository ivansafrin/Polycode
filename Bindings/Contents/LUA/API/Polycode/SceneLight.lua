require "Polycode/SceneEntity"

class "SceneLight" (SceneEntity)



AREA_LIGHT = 0
SPOT_LIGHT = 1




function SceneLight:SceneLight(...)
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

function SceneLight:getDistance()
	local retVal =  Polycore.SceneLight_getDistance(self.__ptr)
	return retVal
end

function SceneLight:getType()
	local retVal =  Polycore.SceneLight_getType(self.__ptr)
	return retVal
end

function SceneLight:renderDepthMap(scene)
	local retVal = Polycore.SceneLight_renderDepthMap(self.__ptr, scene.__ptr)
end

function SceneLight:Render()
	local retVal =  Polycore.SceneLight_Render(self.__ptr)
end

function SceneLight:getLightViewMatrix()
	local retVal =  Polycore.SceneLight_getLightViewMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneLight:getZBufferTexture()
	local retVal =  Polycore.SceneLight_getZBufferTexture(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneLight:setLightColor(r, g, b)
	local retVal = Polycore.SceneLight_setLightColor(self.__ptr, r, g, b)
end

function SceneLight:enableShadows(val, resolution)
	local retVal = Polycore.SceneLight_enableShadows(self.__ptr, val, resolution)
end

function SceneLight:setShadowMapFOV(fov)
	local retVal = Polycore.SceneLight_setShadowMapFOV(self.__ptr, fov)
end

function SceneLight:areShadowsEnabled()
	local retVal =  Polycore.SceneLight_areShadowsEnabled(self.__ptr)
	return retVal
end

function SceneLight:getLightType()
	local retVal =  Polycore.SceneLight_getLightType(self.__ptr)
	return retVal
end

