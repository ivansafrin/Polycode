require "Polycode/Tween"

class "QuaternionTween" (Tween)







function QuaternionTween:QuaternionTween(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Tween" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.QuaternionTween(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function QuaternionTween:updateCustomTween()
	local retVal =  Polycore.QuaternionTween_updateCustomTween(self.__ptr)
end



function QuaternionTween:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_QuaternionTween(self.__ptr)
end
