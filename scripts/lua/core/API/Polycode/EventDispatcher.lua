
class "EventDispatcher"

function EventDispatcher:EventDispatcher()
	self.listenerEntries = {}
end

function EventDispatcher:addEventListener(listener, callback, eventCode)
	if self.listenerEntries == nil then
		self.listenerEntries = {}
	end
	local newEntry = {}
	if self.__ptr ~= nil then
		newEntry.handler = Polycore.EventHandler(newEntry)
		Polycore.EventDispatcher_addEventListener(self.__ptr, newEntry.handler, eventCode)
	end
	newEntry.listener = listener
	newEntry.callback = callback
	newEntry.eventCode = eventCode
	self.listenerEntries[#self.listenerEntries+1] = newEntry
end

function EventDispatcher:removeAllHandlers()
	if self.listenerEntries == nil then
		self.listenerEntries = {}
	end	
	if self.__ptr ~= nil then
		Polycore.EventDispatcher_removeAllHandlers(self.__ptr)
	end
	self.listenerEntries = {}
end

function EventDispatcher:removeAllHandlersForListener(listener)
	if self.listenerEntries == nil then
		self.listenerEntries = {}
	end	
	local i=1
	while i <= #self.listenerEntries do
		if self.listenerEntries[i].listener == listener then
			if self.__ptr ~= nil and self.listenerEntries[i].handler ~= nil then
				Polycore.EventDispatcher_removeAllHandlersForListener(self.__ptr, self.listenerEntries[i].handler)
				Polycore.delete_EventHandler(self.listenerEntries[i].handler)
			end
			table.remove(self.listenerEntries, i)
		else
			i = i + 1
		end
	end
end

function EventDispatcher:removeEventListener(listener, eventCode)
	if self.listenerEntries == nil then
		self.listenerEntries = {}
	end	
	local i=1
	while i <= #self.listenerEntries do
		if self.listenerEntries[i].listener == listener and self.listenerEntries[i].eventCode == eventCode then
			if self.__ptr ~= nil and self.listenerEntries[i].handler ~= nil then
				Polycore.EventDispatcher_removeAllHandlersForListener(self.__ptr, self.listenerEntries[i].handler)
				Polycore.delete_EventHandler(self.listenerEntries[i].handler)
			end
			table.remove(self.listenerEntries, i)
		else
			i = i + 1
		end
	end
end

function EventDispatcher:dispatchEvent(event, eventCode)
	if self.listenerEntries == nil then
		self.listenerEntries = {}
	end	
	for i=1,#self.listenerEntries do
		if self.listenerEntries[i].eventCode == eventCode then
			self.listenerEntries[i].callback(self.listenerEntries[i].listener, event)
		end
	end
end