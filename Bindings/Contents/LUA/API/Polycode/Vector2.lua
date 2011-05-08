require "Polycode/Vector3"

class "Vector2" (Vector3)







function Vector2:Vector2(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Vector3" then
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
		self.__ptr = Polycore.Vector2(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end



function Vector2:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Vector2(self.__ptr)
end
