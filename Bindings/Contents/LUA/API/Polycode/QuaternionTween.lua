require "Polycode/Tween"

class "QuaternionTween" (Tween)







function QuaternionTween:QuaternionTween(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.QuaternionTween(unpack(arg))
	end
end

function QuaternionTween:updateCustomTween()
	local retVal =  Polycore.QuaternionTween_updateCustomTween(self.__ptr)
end

