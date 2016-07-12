class "Event"

Event.EVENTBASE_EVENT = 0x100
Event.COMPLETE_EVENT = Event.EVENTBASE_EVENT + 0
Event.CHANGE_EVENT = Event.EVENTBASE_EVENT + 1
Event.CANCEL_EVENT = Event.EVENTBASE_EVENT + 2
Event.NOTIFY_EVENT = Event.EVENTBASE_EVENT + 3
Event.FIRE_EVENT = Event.EVENTBASE_EVENT + 4
Event.RESOURCE_RELOAD_EVENT = Event.EVENTBASE_EVENT + 5
Event.SELECT_EVENT = Event.EVENTBASE_EVENT + 6
Event.REMOVE_EVENT = Event.EVENTBASE_EVENT + 7
Event.RESOURCE_CHANGE_EVENT = Event.EVENTBASE_EVENT + 8
Event.EVENTBASE_NONPOLYCODE = 0x10000

function Event:__getvar(name)
	if name == "deleteOnDispatch" then
		return Polycode.Event_get_deleteOnDispatch(self.__ptr)
	elseif name == "cancelEventFlag" then
		return Polycode.Event_get_cancelEventFlag(self.__ptr)
	end
end

function Event:__setvar(name,value)
	if name == "deleteOnDispatch" then
		Polycode.Event_set_deleteOnDispatch(self.__ptr, value)
		return true
	elseif name == "cancelEventFlag" then
		Polycode.Event_set_cancelEventFlag(self.__ptr, value)
		return true
	end
	return false
end
function Event:Event(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Event(unpack(arg))
	end
end

function Event:getEventCode()
	local retVal =  Polycode.Event_getEventCode(self.__ptr)
	return retVal
end

function Event:setEventCode(eventCode)
	local retVal = Polycode.Event_setEventCode(self.__ptr, eventCode)
end

function Event:getEventType()
	local retVal =  Polycode.Event_getEventType(self.__ptr)
	return retVal
end

function Event:cancelEvent()
	local retVal =  Polycode.Event_cancelEvent(self.__ptr)
end

function Event:__delete()
	if self then Polycode.delete_Event(self.__ptr) end
end
