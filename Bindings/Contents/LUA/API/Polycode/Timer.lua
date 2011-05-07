require "Polycode/EventDispatcher"

class "Timer" (EventDispatcher)



EVENT_TRIGGER = 0




function Timer:Timer(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Timer(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Timer:Pause(paused)
	local retVal = Polycore.Timer_Pause(self.__ptr, paused)
end

function Timer:isPaused()
	local retVal =  Polycore.Timer_isPaused(self.__ptr)
	return retVal
end

function Timer:getTicks()
	local retVal =  Polycore.Timer_getTicks(self.__ptr)
	return retVal
end

function Timer:Update(ticks)
	local retVal = Polycore.Timer_Update(self.__ptr, ticks)
end

function Timer:Reset()
	local retVal =  Polycore.Timer_Reset(self.__ptr)
end

function Timer:hasElapsed()
	local retVal =  Polycore.Timer_hasElapsed(self.__ptr)
	return retVal
end

function Timer:getElapsedf()
	local retVal =  Polycore.Timer_getElapsedf(self.__ptr)
	return retVal
end

