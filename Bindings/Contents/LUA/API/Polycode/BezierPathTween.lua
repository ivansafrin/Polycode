require "Polycode/Tween"

class "BezierPathTween" (Tween)

function BezierPathTween:BezierPathTween(target, curve, easeType, time, _repeat)
	if self.__ptr == nil then
		self.__ptr = Polycore.BezierPathTween(target, curve, easeType, time, _repeat)
	end
end

function BezierPathTween:updateCustomTween()
	return Polycore.BezierPathTween_updateCustomTween(self.__ptr)
end

