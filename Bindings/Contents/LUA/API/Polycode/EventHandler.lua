class "EventHandler"

function EventHandler:EventHandler()
	if self.__ptr == nil then
		self.__ptr = Polycore.EventHandler()
	end
end

function EventHandler:secondaryHandler(event)
	return Polycore.EventHandler_secondaryHandler(self.__ptr, event.__ptr)
end

function EventHandler:handleEvent(event)
	return Polycore.EventHandler_handleEvent(self.__ptr, event.__ptr)
end

