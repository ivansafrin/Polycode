class "Vector2"



function Vector2:__index__(name)
	if name == "x" then
		return Polycore.Vector2_get_x(self.__ptr)
	elseif name == "y" then
		return Polycore.Vector2_get_y(self.__ptr)
	end
end


function Vector2:__set_callback(name,value)
	if name == "x" then
		Polycore.Vector2_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycore.Vector2_set_y(self.__ptr, value)
		return true
	end
	return false
end


function Vector2:Vector2(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Vector2(unpack(arg))
	end
end

