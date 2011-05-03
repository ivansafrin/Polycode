require "Polycode/EventDispatcher"

class "Tween" (EventDispatcher)



EASE_NONE = 0
EASE_IN_QUAD = 1
EASE_OUT_QUAD = 2
EASE_INOUT_QUAD = 3
EASE_IN_CUBIC = 4
EASE_OUT_CUBIC = 5
EASE_INOUT_CUBIC = 6
EASE_IN_QUART = 7
EASE_OUT_QUART = 8
EASE_INOUT_QUART = 9
EASE_IN_QUINT = 10
EASE_OUT_QUINT = 11
EASE_INOUT_QUINT = 12
EASE_IN_SINE = 13
EASE_OUT_SINE = 14
EASE_INOUT_SINE = 15
EASE_IN_EXPO = 16
EASE_OUT_EXPO = 17
EASE_INOUT_EXPO = 18
EASE_IN_CIRC = 19
EASE_OUT_CIRC = 20
EASE_INOUT_CIRC = 21
EASE_IN_BOUNCE = 22
EASE_OUT_BOUNCE = 23
EASE_INOUT_BOUNCE = 24
function Tween:__index__(name)
	if name == "repeat" then
		return Polycore.Tween_get_repeat(self.__ptr)
	end
end


function Tween:__set_callback(name,value)
	if name == "repeat" then
		Polycore.Tween_set_repeat(self.__ptr, value)
		return true
	end
	return false
end


function Tween:Tween(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Tween(unpack(arg))
	end
end

function Tween:handleEvent(event)
	local retVal = Polycore.Tween_handleEvent(self.__ptr, event.__ptr)
end

function Tween:interpolateTween()
	local retVal =  Polycore.Tween_interpolateTween(self.__ptr)
	return retVal
end

function Tween:updateCustomTween()
	local retVal =  Polycore.Tween_updateCustomTween(self.__ptr)
end

function Tween:doOnComplete()
	local retVal =  Polycore.Tween_doOnComplete(self.__ptr)
end

function Tween:Pause(pauseVal)
	local retVal = Polycore.Tween_Pause(self.__ptr, pauseVal)
end

function Tween:Reset()
	local retVal =  Polycore.Tween_Reset(self.__ptr)
end

function Tween:isComplete()
	local retVal =  Polycore.Tween_isComplete(self.__ptr)
	return retVal
end

function Tween:setSpeed(speed)
	local retVal = Polycore.Tween_setSpeed(self.__ptr, speed)
end

