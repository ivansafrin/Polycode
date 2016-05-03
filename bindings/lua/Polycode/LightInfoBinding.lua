class "LightInfoBinding"



function LightInfoBinding:__getvar(name)
	if name == "position" then
		local retVal = Polycore.LightInfoBinding_get_position(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "direction" then
		local retVal = Polycore.LightInfoBinding_get_direction(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "specular" then
		local retVal = Polycore.LightInfoBinding_get_specular(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "diffuse" then
		local retVal = Polycore.LightInfoBinding_get_diffuse(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "spotExponent" then
		local retVal = Polycore.LightInfoBinding_get_spotExponent(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "spotCosCutoff" then
		local retVal = Polycore.LightInfoBinding_get_spotCosCutoff(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "constantAttenuation" then
		local retVal = Polycore.LightInfoBinding_get_constantAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "linearAttenuation" then
		local retVal = Polycore.LightInfoBinding_get_linearAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "quadraticAttenuation" then
		local retVal = Polycore.LightInfoBinding_get_quadraticAttenuation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "shadowEnabled" then
		local retVal = Polycore.LightInfoBinding_get_shadowEnabled(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function LightInfoBinding:__setvar(name,value)
	return false
end


function LightInfoBinding:__delete()
	if self then Polycore.delete_LightInfoBinding(self.__ptr) end
end
