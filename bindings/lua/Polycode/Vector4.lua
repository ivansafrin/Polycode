class "Vector4"



function Vector4:__getvar(name)
	if name == "x" then
		return Polycore.Vector4_get_x(self.__ptr)
	elseif name == "y" then
		return Polycore.Vector4_get_y(self.__ptr)
	elseif name == "z" then
		return Polycore.Vector4_get_z(self.__ptr)
	elseif name == "w" then
		return Polycore.Vector4_get_w(self.__ptr)
	end
end


function Vector4:__setvar(name,value)
	if name == "x" then
		Polycore.Vector4_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycore.Vector4_set_y(self.__ptr, value)
		return true
	elseif name == "z" then
		Polycore.Vector4_set_z(self.__ptr, value)
		return true
	elseif name == "w" then
		Polycore.Vector4_set_w(self.__ptr, value)
		return true
	end
	return false
end


function Vector4:Vector4(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Vector4(unpack(arg))
	end
end

function Vector4:set(x, y, z, w)
	local retVal = Polycore.Vector4_set(self.__ptr, x, y, z, w)
end

function Vector4:dot(u)
	local retVal = Polycore.Vector4_dot(self.__ptr, u.__ptr)
	return retVal
end

function Vector4:__delete()
	if self then Polycore.delete_Vector4(self.__ptr) end
end
