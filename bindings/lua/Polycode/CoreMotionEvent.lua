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
function CoreMotionEvent:CoreMotionEvent(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Event" then
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
		self.__ptr = Polycode.CoreMotionEvent(unpack(arg))
	end
end

function CoreMotionEvent:__delete()
	if self then Polycode.delete_CoreMotionEvent(self.__ptr) end
end
