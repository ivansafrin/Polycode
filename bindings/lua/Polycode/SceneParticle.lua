class "SceneParticle"


function SceneParticle:__getvar(name)
	if name == "lifetime" then
		return Polycode.SceneParticle_get_lifetime(self.__ptr)
	elseif name == "position" then
		local retVal = Polycode.SceneParticle_get_position(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "velocity" then
		local retVal = Polycode.SceneParticle_get_velocity(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "perlinPos" then
		local retVal = Polycode.SceneParticle_get_perlinPos(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "rotation" then
		local retVal = Polycode.SceneParticle_get_rotation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "brightnessDeviation" then
		return Polycode.SceneParticle_get_brightnessDeviation(self.__ptr)
	elseif name == "scale" then
		return Polycode.SceneParticle_get_scale(self.__ptr)
	elseif name == "color" then
		local retVal = Polycode.SceneParticle_get_color(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "varianceIndex" then
		return Polycode.SceneParticle_get_varianceIndex(self.__ptr)
	end
end

function SceneParticle:__setvar(name,value)
	if name == "lifetime" then
		Polycode.SceneParticle_set_lifetime(self.__ptr, value)
		return true
	elseif name == "position" then
		Polycode.SceneParticle_set_position(self.__ptr, value.__ptr)
		return true
	elseif name == "velocity" then
		Polycode.SceneParticle_set_velocity(self.__ptr, value.__ptr)
		return true
	elseif name == "perlinPos" then
		Polycode.SceneParticle_set_perlinPos(self.__ptr, value.__ptr)
		return true
	elseif name == "rotation" then
		Polycode.SceneParticle_set_rotation(self.__ptr, value.__ptr)
		return true
	elseif name == "brightnessDeviation" then
		Polycode.SceneParticle_set_brightnessDeviation(self.__ptr, value)
		return true
	elseif name == "scale" then
		Polycode.SceneParticle_set_scale(self.__ptr, value)
		return true
	elseif name == "color" then
		Polycode.SceneParticle_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "varianceIndex" then
		Polycode.SceneParticle_set_varianceIndex(self.__ptr, value)
		return true
	end
	return false
end
function SceneParticle:__delete()
	if self then Polycode.delete_SceneParticle(self.__ptr) end
end
