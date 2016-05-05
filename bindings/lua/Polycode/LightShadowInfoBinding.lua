class "LightShadowInfoBinding"


function LightShadowInfoBinding:__getvar(name)
	if name == "shadowMatrix" then
		local retVal = Polycode.LightShadowInfoBinding_get_shadowMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "shadowBuffer" then
		local retVal = Polycode.LightShadowInfoBinding_get_shadowBuffer(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["LocalShaderParam"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function LightShadowInfoBinding:__setvar(name,value)
	if name == "shadowMatrix" then
		Polycode.LightShadowInfoBinding_set_shadowMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "shadowBuffer" then
		Polycode.LightShadowInfoBinding_set_shadowBuffer(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function LightShadowInfoBinding:__delete()
	if self then Polycode.delete_LightShadowInfoBinding(self.__ptr) end
end
