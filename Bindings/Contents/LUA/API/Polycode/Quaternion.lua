class "Quaternion"



function Quaternion:__index__(name)
	if name == "x" then
		return Polycore.Quaternion_get_x(self.__ptr)
	elseif name == "y" then
		return Polycore.Quaternion_get_y(self.__ptr)
	elseif name == "z" then
		return Polycore.Quaternion_get_z(self.__ptr)
	elseif name == "w" then
		return Polycore.Quaternion_get_w(self.__ptr)
	end
end


function Quaternion:__set_callback(name,value)
	if name == "x" then
		Polycore.Quaternion_set_x(self.__ptr, value)
		return true
	elseif name == "y" then
		Polycore.Quaternion_set_y(self.__ptr, value)
		return true
	elseif name == "z" then
		Polycore.Quaternion_set_z(self.__ptr, value)
		return true
	elseif name == "w" then
		Polycore.Quaternion_set_w(self.__ptr, value)
		return true
	end
	return false
end


function Quaternion:Quaternion(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Quaternion(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Quaternion:setFromMatrix(_mat)
	local retVal = Polycore.Quaternion_setFromMatrix(self.__ptr, _mat.__ptr)
end

function Quaternion:Slerp(fT, rkP, rkQ, shortestPath)
	local retVal = Polycore.Quaternion_Slerp(fT, rkP.__ptr, rkQ.__ptr, shortestPath)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:Dot(rkQ)
	local retVal = Polycore.Quaternion_Dot(self.__ptr, rkQ.__ptr)
	return retVal
end

function Quaternion:Log()
	local retVal =  Polycore.Quaternion_Log(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:Exp()
	local retVal =  Polycore.Quaternion_Exp(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:Norm()
	local retVal =  Polycore.Quaternion_Norm(self.__ptr)
	return retVal
end

function Quaternion:normalize()
	local retVal =  Polycore.Quaternion_normalize(self.__ptr)
	return retVal
end

function Quaternion:lookAt(D, upVector)
	local retVal = Polycore.Quaternion_lookAt(self.__ptr, D.__ptr, upVector.__ptr)
end

function Quaternion:createFromMatrix(matrix)
	local retVal = Polycore.Quaternion_createFromMatrix(self.__ptr, matrix.__ptr)
end

function Quaternion:Squad(fT, rkP, rkA, rkB, rkQ, shortestPath)
	local retVal = Polycore.Quaternion_Squad(fT, rkP.__ptr, rkA.__ptr, rkB.__ptr, rkQ.__ptr, shortestPath)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:Inverse()
	local retVal =  Polycore.Quaternion_Inverse(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:set(w, x, y, z)
	local retVal = Polycore.Quaternion_set(self.__ptr, w, x, y, z)
end

function Quaternion:inverse()
	local retVal =  Polycore.Quaternion_inverse(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Quaternion:InvSqrt(x)
	local retVal = Polycore.Quaternion_InvSqrt(self.__ptr, x)
	return retVal
end

function Quaternion:fromAxes(az, ay, ax)
	local retVal = Polycore.Quaternion_fromAxes(self.__ptr, az, ay, ax)
end

function Quaternion:FromAngleAxis(rfAngle, rkAxis)
	local retVal = Polycore.Quaternion_FromAngleAxis(self.__ptr, rfAngle, rkAxis.__ptr)
end

function Quaternion:ToAngleAxis(rfAngle, rkAxis)
	local retVal = Polycore.Quaternion_ToAngleAxis(self.__ptr, rfAngle, rkAxis.__ptr)
end

function Quaternion:createFromAxisAngle(x, y, z, degrees)
	local retVal = Polycore.Quaternion_createFromAxisAngle(self.__ptr, x, y, z, degrees)
end

function Quaternion:createMatrix()
	local retVal =  Polycore.Quaternion_createMatrix(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Quaternion:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Quaternion(self.__ptr)
end
