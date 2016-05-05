class "Vector2"


function Vector2:__getvar(name)
	if name == "x" then
		return Polycode.Vector2_get_x(self.__ptr)
	elseif name == "y" then
		return Polycode.Vector2_get_y(self.__ptr)
	end
end

function Vector2:__setvar(name,value)
	if name == "x" then
		Polycode.Vector2_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycode.Vector2_set_y(self.__ptr, value)
		return true
	end
	return false
end
function Vector2:Vector2(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Vector2(unpack(arg))
	end
end

function Vector2:set(x, y)
	local retVal = Polycode.Vector2_set(self.__ptr, x, y)
end

function Vector2:distance(vec2)
	local retVal = Polycode.Vector2_distance(self.__ptr, vec2.__ptr)
	return retVal
end

function Vector2:length()
	local retVal =  Polycode.Vector2_length(self.__ptr)
	return retVal
end

function Vector2:dot(u)
	local retVal = Polycode.Vector2_dot(self.__ptr, u.__ptr)
	return retVal
end

function Vector2:crossProduct(vec2)
	local retVal = Polycode.Vector2_crossProduct(self.__ptr, vec2.__ptr)
	return retVal
end

function Vector2:angle(vec2)
	local retVal = Polycode.Vector2_angle(self.__ptr, vec2.__ptr)
	return retVal
end

function Vector2:Normalize()
	local retVal =  Polycode.Vector2_Normalize(self.__ptr)
end

function Vector2:__delete()
	if self then Polycode.delete_Vector2(self.__ptr) end
end
