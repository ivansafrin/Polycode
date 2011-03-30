require "Polycode/Tween"

class "QuaternionTween" (Tween)

function QuaternionTween:QuaternionTween(target, wCurve, xCurve, yCurve, zCurve, easeType, time, _repeat)
	if self.__ptr == nil then
		self.__ptr = Polycore.QuaternionTween(target, wCurve, xCurve, yCurve, zCurve, easeType, time, _repeat)
	end
end

function QuaternionTween:updateCustomTween()
	return Polycore.QuaternionTween_updateCustomTween(self.__ptr)
end

