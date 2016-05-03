class "QuatTriple"



function QuatTriple:__getvar(name)
	if name == "q1" then
		local retVal = Polycore.QuatTriple_get_q1(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "q2" then
		local retVal = Polycore.QuatTriple_get_q2(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "q3" then
		local retVal = Polycore.QuatTriple_get_q3(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "time" then
		return Polycore.QuatTriple_get_time(self.__ptr)
	end
end


function QuatTriple:__setvar(name,value)
	if name == "q1" then
		Polycore.QuatTriple_set_q1(self.__ptr, value.__ptr)
		return true
	elseif name == "q2" then
		Polycore.QuatTriple_set_q2(self.__ptr, value.__ptr)
		return true
	elseif name == "q3" then
		Polycore.QuatTriple_set_q3(self.__ptr, value.__ptr)
		return true
	elseif name == "time" then
		Polycore.QuatTriple_set_time(self.__ptr, value)
		return true
	end
	return false
end


function QuatTriple:__delete()
	if self then Polycore.delete_QuatTriple(self.__ptr) end
end
