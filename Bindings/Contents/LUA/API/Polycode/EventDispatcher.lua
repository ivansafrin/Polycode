require "Polycode/EventHandler"

class "EventDispatcher" (EventHandler)







function EventDispatcher:EventDispatcher(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.EventDispatcher(unpack(arg))
	end
end

function EventDispatcher:removeAllHandlers()
	local retVal =  Polycore.EventDispatcher_removeAllHandlers(self.__ptr)
end

function EventDispatcher:removeAllHandlersForListener(listener)
	local retVal = Polycore.EventDispatcher_removeAllHandlersForListener(self.__ptr, listener.__ptr)
end

function EventDispatcher:addEventListener(handler, eventCode)
	local retVal = Polycore.EventDispatcher_addEventListener(self.__ptr, handler.__ptr, eventCode)
end

function EventDispatcher:removeEventListener(handler, eventCode)
	local retVal = Polycore.EventDispatcher_removeEventListener(self.__ptr, handler.__ptr, eventCode)
end

function EventDispatcher:__dispatchEvent(event, eventCode)
	local retVal = Polycore.EventDispatcher___dispatchEvent(self.__ptr, event.__ptr, eventCode)
end

function EventDispatcher:dispatchEvent(event, eventCode)
	local retVal = Polycore.EventDispatcher_dispatchEvent(self.__ptr, event.__ptr, eventCode)
end

function EventDispatcher:dispatchEventNoDelete(event, eventCode)
	local retVal = Polycore.EventDispatcher_dispatchEventNoDelete(self.__ptr, event.__ptr, eventCode)
end

