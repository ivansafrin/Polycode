require "Polycode/EventDispatcher"

class "ScreenManager" (EventDispatcher)







function ScreenManager:ScreenManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ScreenManager(unpack(arg))
	end
end

function ScreenManager:removeScreen(screen)
	local retVal = Polycore.ScreenManager_removeScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:addScreen(screen)
	local retVal = Polycore.ScreenManager_addScreen(self.__ptr, screen.__ptr)
end

function ScreenManager:Update()
	local retVal =  Polycore.ScreenManager_Update(self.__ptr)
end

function ScreenManager:handleEvent(event)
	local retVal = Polycore.ScreenManager_handleEvent(self.__ptr, event.__ptr)
end

