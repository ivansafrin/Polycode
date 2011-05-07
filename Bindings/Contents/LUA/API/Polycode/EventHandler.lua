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
		self.__ptr = Polycore.EventHandler(self)
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function EventHandler:__handleEvent(event)
	evt = Event("__skip_ptr__")
	evt.__ptr = event
	self:handleEvent(evt)
end
