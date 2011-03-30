require "Polycode/EventDispatcher"

class "ScreenManager" (EventDispatcher)

function ScreenManager:ScreenManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenManager()
	end
end

function ScreenManager:removeScreen(screen)
	return Polycore.ScreenManager_removeScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:addScreen(screen)
	return Polycore.ScreenManager_addScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:Update()
	return Polycore.ScreenManager_Update(self.__ptr)
end

function ScreenManager:handleEvent(event)
	return Polycore.ScreenManager_handleEvent(self.__ptr, event.__ptr)
end

