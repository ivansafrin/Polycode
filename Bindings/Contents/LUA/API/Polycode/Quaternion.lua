class "Quaternion"

function Quaternion:Quaternion(w, x, y, z)
	if self.__ptr == nil then
		self.__ptr = Polycore.Quaternion(w, x, y, z)
	end
end

function Quaternion:setFromMatrix(kRot)
	return Polycore.Quaternion_setFromMatrix(self.__ptr, kRot.__ptr)
end

function Quaternion:Slerp(fT, rkP, rkQ, shortestPath)
	return Polycore.Quaternion_Slerp(self.__ptr, fT, rkP.__ptr, rkQ.__ptr, shortestPath)
end

function Quaternion:Dot(rkQ)
	return Polycore.Quaternion_Dot(self.__ptr, rkQ.__ptr)
end

function Quaternion:Log()
	return Polycore.Quaternion_Log(self.__ptr)
end

function Quaternion:Exp()
	return Polycore.Quaternion_Exp(self.__ptr)
end

function Quaternion:Norm()
	return Polycore.Quaternion_Norm(self.__ptr)
end

function Quaternion:normalise()
	return Polycore.Quaternion_normalise(self.__ptr)
end

function Quaternion:lookAt(D, upVector)
	return Polycore.Quaternion_lookAt(self.__ptr, D.__ptr, upVector.__ptr)
end

function Quaternion:createFromMatrix(matrix)
	return Polycore.Quaternion_createFromMatrix(self.__ptr, matrix.__ptr)
end

function Quaternion:Squad(fT, rkP, rkA, rkB, rkQ, shortestPath)
	return Polycore.Quaternion_Squad(self.__ptr, fT, rkP.__ptr, rkA.__ptr, rkB.__ptr, rkQ.__ptr, shortestPath)
end

function Quaternion:Inverse()
	return Polycore.Quaternion_Inverse(self.__ptr)
end

function Quaternion:set(w, x, y, z)
	return Polycore.Quaternion_set(self.__ptr, w, x, y, z)
end

function Quaternion:inverse()
	return Polycore.Quaternion_inverse(self.__ptr)
end

function Quaternion:InvSqrt(x)
	return Polycore.Quaternion_InvSqrt(self.__ptr, x)
end

function Quaternion:fromAxes(az, ay, ax)
	return Polycore.Quaternion_fromAxes(self.__ptr, az, ay, ax)
end

function Quaternion:FromAngleAxis(rfAngle, rkAxis)
	return Polycore.Quaternion_FromAngleAxis(self.__ptr, rfAngle.__ptr, rkAxis.__ptr)
end

function Quaternion:ToAngleAxis(rfAngle, rkAxis)
	return Polycore.Quaternion_ToAngleAxis(self.__ptr, rfAngle.__ptr, rkAxis.__ptr)
end

function Quaternion:createFromAxisAngle(x, y, z, degrees)
	return Polycore.Quaternion_createFromAxisAngle(self.__ptr, x, y, z, degrees)
end

function Quaternion:createMatrix()
	return Polycore.Quaternion_createMatrix(self.__ptr)
end

