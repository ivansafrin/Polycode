class "AABB"



function AABB:__getvar(name)
	if name == "min" then
		local retVal = Polycore.AABB_get_min(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "max" then
		local retVal = Polycore.AABB_get_max(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function AABB:__setvar(name,value)
	if name == "min" then
		Polycore.AABB_set_min(self.__ptr, value.__ptr)
		return true
	elseif name == "max" then
		Polycore.AABB_set_max(self.__ptr, value.__ptr)
		return true
	end
	return false
end


function AABB:__delete()
	if self then Polycore.delete_AABB(self.__ptr) end
end
