require "Polycode/EventDispatcher"

class "Tween" (EventDispatcher)

function Tween:Tween(target, easeType, startVal, _endVal, time, _repeat)
	if self.__ptr == nil then
		self.__ptr = Polycore.Tween(target, easeType, startVal, _endVal, time, _repeat)
	end
end

function Tween:handleEvent(event)
	return Polycore.Tween_handleEvent(self.__ptr, event.__ptr)
end

function Tween:interpolateTween()
	return Polycore.Tween_interpolateTween(self.__ptr)
end

function Tween:updateCustomTween()
	return Polycore.Tween_updateCustomTween(self.__ptr)
end

function Tween:doOnComplete()
	return Polycore.Tween_doOnComplete(self.__ptr)
end

function Tween:Pause(pauseVal)
	return Polycore.Tween_Pause(self.__ptr, pauseVal)
end

function Tween:Reset()
	return Polycore.Tween_Reset(self.__ptr)
end

function Tween:isComplete()
	return Polycore.Tween_isComplete(self.__ptr)
end

function Tween:setSpeed(speed)
	return Polycore.Tween_setSpeed(self.__ptr, speed)
end

