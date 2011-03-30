class "Matrix4"

function Matrix4:Matrix4()
	if self.__ptr == nil then
		self.__ptr = Polycore.Matrix4()
	end
end

function Matrix4:init()
	return Polycore.Matrix4_init(self.__ptr)
end

function Matrix4:identity()
	return Polycore.Matrix4_identity(self.__ptr)
end

function Matrix4:rotateVector(v2)
	return Polycore.Matrix4_rotateVector(self.__ptr, v2.__ptr)
end

function Matrix4:getPosition()
	return Polycore.Matrix4_getPosition(self.__ptr)
end

function Matrix4:setPosition(x, y, z)
	return Polycore.Matrix4_setPosition(self.__ptr, x, y, z)
end

function Matrix4:setScale(scale)
	return Polycore.Matrix4_setScale(self.__ptr, scale.__ptr)
end

function Matrix4:getEulerAngles(ax, ay, az)
	return Polycore.Matrix4_getEulerAngles(self.__ptr, ax.__ptr, ay.__ptr, az.__ptr)
end

function Matrix4:inverse()
	return Polycore.Matrix4_inverse(self.__ptr)
end

function Matrix4:inverseAffine()
	return Polycore.Matrix4_inverseAffine(self.__ptr)
end

