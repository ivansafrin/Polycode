class "Event"

function Event:Event()
	if self.__ptr == nil then
		self.__ptr = Polycore.Event()
	end
end

function Event:getEventCode()
	return Polycore.Event_getEventCode(self.__ptr)
end

function Event:setEventCode(eventCode)
	return Polycore.Event_setEventCode(self.__ptr, eventCode)
end

function Event:getDispatcher()
	return Polycore.Event_getDispatcher(self.__ptr)
end

function Event:setDispatcher(dispatcher)
	return Polycore.Event_setDispatcher(self.__ptr, dispatcher.__ptr)
end

function Event:getEventType()
	return Polycore.Event_getEventType(self.__ptr)
end

