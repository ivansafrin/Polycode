class "LightInfoBinding"


function LightInfoBinding:__getvar(name)
	if name == "position" then
		local retVal = Polycode.LightInfoBinding_get_position(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "direction" then
		local retVal = Polycode.LightInfoBinding_get_direction(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "specular" then
		local retVal = Polycode.LightInfoBinding_get_specular(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "diffuse" then
		local retVal = Polycode.LightInfoBinding_get_diffuse(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "spotExponent" then
		local retVal = Polycode.LightInfoBinding_get_spotExponent(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "spotCosCutoff" then
		local retVal = Polycode.LightInfoBinding_get_spotCosCutoff(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "constantAttenuation" then
		local retVal = Polycode.LightInfoBinding_get_constantAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "linearAttenuation" then
		local retVal = Polycode.LightInfoBinding_get_linearAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "quadraticAttenuation" then
		local retVal = Polycode.LightInfoBinding_get_quadraticAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "shadowEnabled" then
		local retVal = Polycode.LightInfoBinding_get_shadowEnabled(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function LightInfoBinding:__setvar(name,value)
	if name == "position" then
		Polycode.LightInfoBinding_set_position(self.__ptr, value.__ptr)
		return true
	elseif name == "direction" then
		Polycode.LightInfoBinding_set_direction(self.__ptr, value.__ptr)
		return true
	elseif name == "specular" then
		Polycode.LightInfoBinding_set_specular(self.__ptr, value.__ptr)
		return true
	elseif name == "diffuse" then
		Polycode.LightInfoBinding_set_diffuse(self.__ptr, value.__ptr)
		return true
	elseif name == "spotExponent" then
		Polycode.LightInfoBinding_set_spotExponent(self.__ptr, value.__ptr)
		return true
	elseif name == "spotCosCutoff" then
		Polycode.LightInfoBinding_set_spotCosCutoff(self.__ptr, value.__ptr)
		return true
	elseif name == "constantAttenuation" then
		Polycode.LightInfoBinding_set_constantAttenuation(self.__ptr, value.__ptr)
		return true
	elseif name == "linearAttenuation" then
		Polycode.LightInfoBinding_set_linearAttenuation(self.__ptr, value.__ptr)
		return true
	elseif name == "quadraticAttenuation" then
		Polycode.LightInfoBinding_set_quadraticAttenuation(self.__ptr, value.__ptr)
		return true
	elseif name == "shadowEnabled" then
		Polycode.LightInfoBinding_set_shadowEnabled(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function LightInfoBinding:__delete()
	if self then Polycode.delete_LightInfoBinding(self.__ptr) end
end
