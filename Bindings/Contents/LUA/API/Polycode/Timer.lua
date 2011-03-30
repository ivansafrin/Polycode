require "Polycode/EventDispatcher"

class "Timer" (EventDispatcher)

function Timer:Timer(triggerMode, msecs)
	if self.__ptr == nil then
		self.__ptr = Polycore.Timer(triggerMode, msecs)
	end
end

function Timer:Pause(paused)
	return Polycore.Timer_Pause(self.__ptr, paused)
end

function Timer:isPaused()
	return Polycore.Timer_isPaused(self.__ptr)
end

function Timer:getTicks()
	return Polycore.Timer_getTicks(self.__ptr)
end

function Timer:Update(ticks)
	return Polycore.Timer_Update(self.__ptr, ticks)
end

function Timer:Reset()
	return Polycore.Timer_Reset(self.__ptr)
end

function Timer:hasElapsed()
	return Polycore.Timer_hasElapsed(self.__ptr)
end

function Timer:getElapsedf()
	return Polycore.Timer_getElapsedf(self.__ptr)
end

