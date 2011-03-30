require "Polycode/EventHandler"

class "EventDispatcher" (EventHandler)

function EventDispatcher:EventDispatcher()
	if self.__ptr == nil then
		self.__ptr = Polycore.EventDispatcher()
	end
end

function EventDispatcher:removeAllHandlers()
	return Polycore.EventDispatcher_removeAllHandlers(self.__ptr)
end

function EventDispatcher:removeAllHandlersForListener(listener)
	return Polycore.EventDispatcher_removeAllHandlersForListener(self.__ptr, listener.__ptr)
end

function EventDispatcher:addEventListener(handler, eventCode)
	return Polycore.EventDispatcher_addEventListener(self.__ptr, handler.__ptr, eventCode)
end

function EventDispatcher:removeEventListener(handler, eventCode)
	return Polycore.EventDispatcher_removeEventListener(self.__ptr, handler.__ptr, eventCode)
end

function EventDispatcher:__dispatchEvent(event, eventCode)
	return Polycore.EventDispatcher___dispatchEvent(self.__ptr, event.__ptr, eventCode)
end

function EventDispatcher:dispatchEvent(event, eventCode)
	return Polycore.EventDispatcher_dispatchEvent(self.__ptr, event.__ptr, eventCode)
end

function EventDispatcher:dispatchEventNoDelete(event, eventCode)
	return Polycore.EventDispatcher_dispatchEventNoDelete(self.__ptr, event.__ptr, eventCode)
end

