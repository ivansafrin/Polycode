class "Vector3"

function Vector3:Vector3()
	if self.__ptr == nil then
		self.__ptr = Polycore.Vector3()
	end
end

function Vector3:set(x, y, z)
	return Polycore.Vector3_set(self.__ptr, x, y, z)
end

function Vector3:distance(rhs)
	return Polycore.Vector3_distance(self.__ptr, rhs.__ptr)
end

function Vector3:length()
	return Polycore.Vector3_length(self.__ptr)
end

function Vector3:dot(u)
	return Polycore.Vector3_dot(self.__ptr, u.__ptr)
end

function Vector3:crossProduct(rkVector)
	return Polycore.Vector3_crossProduct(self.__ptr, rkVector.__ptr)
end

function Vector3:Normalize()
	return Polycore.Vector3_Normalize(self.__ptr)
end

