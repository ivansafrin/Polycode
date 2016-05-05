class "Vector3"


function Vector3:__getvar(name)
	if name == "x" then
		return Polycode.Vector3_get_x(self.__ptr)
	elseif name == "y" then
		return Polycode.Vector3_get_y(self.__ptr)
	elseif name == "z" then
		return Polycode.Vector3_get_z(self.__ptr)
	end
end

function Vector3:__setvar(name,value)
	if name == "x" then
		Polycode.Vector3_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycode.Vector3_set_y(self.__ptr, value)
		return true
	elseif name == "z" then
		Polycode.Vector3_set_z(self.__ptr, value)
		return true
	end
	return false
end
function Vector3:Vector3(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Vector3(unpack(arg))
	end
end

function Vector3:set(x, y, z)
	local retVal = Polycode.Vector3_set(self.__ptr, x, y, z)
end

function Vector3:distance(vec2)
	local retVal = Polycode.Vector3_distance(self.__ptr, vec2.__ptr)
	return retVal
end

function Vector3:angleBetween(dest)
	local retVal = Polycode.Vector3_angleBetween(self.__ptr, dest.__ptr)
	return retVal
end

function Vector3:length()
	local retVal =  Polycode.Vector3_length(self.__ptr)
	return retVal
end

function Vector3:lengthSquared()
	local retVal =  Polycode.Vector3_lengthSquared(self.__ptr)
	return retVal
end

function Vector3:setLength(newLength)
	local retVal = Polycode.Vector3_setLength(self.__ptr, newLength)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Vector3:dot(u)
	local retVal = Polycode.Vector3_dot(self.__ptr, u.__ptr)
	return retVal
end

function Vector3:crossProduct(vec2)
	local retVal = Polycode.Vector3_crossProduct(self.__ptr, vec2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Vector3:Normalize()
	local retVal =  Polycode.Vector3_Normalize(self.__ptr)
end

function Vector3:__delete()
	if self then Polycode.delete_Vector3(self.__ptr) end
end
