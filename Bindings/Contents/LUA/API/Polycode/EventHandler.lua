class "EventHandler"







function EventHandler:EventHandler(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.EventHandler(unpack(arg))
	end
end

function EventHandler:secondaryHandler(event)
	local retVal = Polycore.EventHandler_secondaryHandler(self.__ptr, event.__ptr)
end

function EventHandler:handleEvent(event)
	local retVal = Polycore.EventHandler_handleEvent(self.__ptr, event.__ptr)
end

