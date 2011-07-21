require "Polycode/SceneEntity"

class "SceneLight" (SceneEntity)



AREA_LIGHT = 0
SPOT_LIGHT = 1
function SceneLight:__index__(name)
	if name == "specularLightColor" then
		retVal = Polycore.SceneLight_get_specularLightColor(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Color("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "lightColor" then
		retVal = Polycore.SceneLight_get_lightColor(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Color("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function SceneLight:__set_callback(name,value)
	return false
end


function SceneLight:SceneLight(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneEntity" then
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
		Polycore.__ptr_lookup[self.__ptr] = self
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

function SceneLight:Render()
	local retVal =  Polycore.SceneLight_Render(self.__ptr)
end

function SceneLight:getLightViewMatrix()
	local retVal =  Polycore.SceneLight_getLightViewMatrix(self.__ptr)
	if retVal == nil then return nil end
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
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SceneLight:setSpecularLightColor(r, g, b, a)
	local retVal = Polycore.SceneLight_setSpecularLightColor(self.__ptr, r, g, b, a)
end

function SceneLight:setDiffuseLightColor(r, g, b)
	local retVal = Polycore.SceneLight_setDiffuseLightColor(self.__ptr, r, g, b)
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

function SceneLight:areShadowsEnabled()
	local retVal =  Polycore.SceneLight_areShadowsEnabled(self.__ptr)
	return retVal
end

function SceneLight:getLightType()
	local retVal =  Polycore.SceneLight_getLightType(self.__ptr)
	return retVal
end

function SceneLight:enableDebugDraw(val)
	local retVal = Polycore.SceneLight_enableDebugDraw(self.__ptr, val)
end



function SceneLight:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneLight(self.__ptr)
end
