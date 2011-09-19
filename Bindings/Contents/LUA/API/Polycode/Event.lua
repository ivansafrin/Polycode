class "Event"



COMPLETE_EVENT = 0
CHANGE_EVENT = 1




function Event:Event(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Event(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Event:getEventCode()
	local retVal =  Polycore.Event_getEventCode(self.__ptr)
	return retVal
end

function Event:getDispatcher()
	local retVal =  Polycore.Event_getDispatcher(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = EventDispatcher("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Event:setEventCode(eventCode)
	local retVal = Polycore.Event_setEventCode(self.__ptr, eventCode)
end

function Event:setDispatcher(dispatcher)
	local retVal = Polycore.Event_setDispatcher(self.__ptr, dispatcher.__ptr)
end

function Event:getEventType()
	local retVal =  Polycore.Event_getEventType(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Event:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Event(self.__ptr)
end
