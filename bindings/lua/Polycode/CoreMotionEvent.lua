require "Polycode/Event"

class "CoreMotionEvent" (Event)


function CoreMotionEvent:__getvar(name)
	if name == "amount" then
		local retVal = Polycode.CoreMotionEvent_get_amount(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if Event["__getvar"] ~= nil then
		return Event.__getvar(self, name)
	end
end

function CoreMotionEvent:__setvar(name,value)
	if name == "amount" then
		Polycode.CoreMotionEvent_set_amount(self.__ptr, value.__ptr)
		return true
	end
	if Event["__setvar"] ~= nil then
		return Event.__setvar(self, name, value)
	else
		return false
	end
end
function CoreMotionEvent:__delete()
	if self then Polycode.delete_CoreMotionEvent(self.__ptr) end
end
