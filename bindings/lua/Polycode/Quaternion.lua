class "Quaternion"



function Quaternion:__getvar(name)
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


function Quaternion:__setvar(name,value)
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
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Quaternion(unpack(arg))
	end
end

function Quaternion:setFromMatrix(_mat)
	local retVal = Polycore.Quaternion_setFromMatrix(self.__ptr, _mat.__ptr)
end

function Quaternion.Slerp(fT, rkP, rkQ, shortestPath)
	local retVal = Polycore.Quaternion_Slerp(fT, rkP.__ptr, rkQ.__ptr, shortestPath)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:Dot(rkQ)
	local retVal = Polycore.Quaternion_Dot(self.__ptr, rkQ.__ptr)
	return retVal
end

function Quaternion:Log()
	local retVal =  Polycore.Quaternion_Log(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:Exp()
	local retVal =  Polycore.Quaternion_Exp(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:Norm()
	local retVal =  Polycore.Quaternion_Norm(self.__ptr)
	return retVal
end

function Quaternion:Normalize()
	local retVal =  Polycore.Quaternion_Normalize(self.__ptr)
	return retVal
end

function Quaternion:lookAt(D, upVector)
	local retVal = Polycore.Quaternion_lookAt(self.__ptr, D.__ptr, upVector.__ptr)
end

function Quaternion:createFromMatrix(matrix)
	local retVal = Polycore.Quaternion_createFromMatrix(self.__ptr, matrix.__ptr)
end

function Quaternion.Squad(fT, rkP, rkA, rkB, rkQ, shortestPath)
	local retVal = Polycore.Quaternion_Squad(fT, rkP.__ptr, rkA.__ptr, rkB.__ptr, rkQ.__ptr, shortestPath)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:Inverse()
	local retVal =  Polycore.Quaternion_Inverse(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:set(w, x, y, z)
	local retVal = Polycore.Quaternion_set(self.__ptr, w, x, y, z)
end

function Quaternion:InvSqrt(x)
	local retVal = Polycore.Quaternion_InvSqrt(self.__ptr, x)
	return retVal
end

function Quaternion:fromAxes(az, ay, ax)
	local retVal = Polycore.Quaternion_fromAxes(self.__ptr, az, ay, ax)
end

function Quaternion:fromAngleAxis(rfAngle, rkAxis)
	local retVal = Polycore.Quaternion_fromAngleAxis(self.__ptr, rfAngle, rkAxis.__ptr)
end

function Quaternion:toEulerAngles()
	local retVal =  Polycore.Quaternion_toEulerAngles(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:toAngleAxis(rfAngle, rkAxis)
	local retVal = Polycore.Quaternion_toAngleAxis(self.__ptr, rfAngle, rkAxis.__ptr)
end

function Quaternion:createFromAxisAngle(x, y, z, degrees)
	local retVal = Polycore.Quaternion_createFromAxisAngle(self.__ptr, x, y, z, degrees)
end

function Quaternion:createMatrix()
	local retVal =  Polycore.Quaternion_createMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:applyTo(v)
	local retVal = Polycore.Quaternion_applyTo(self.__ptr, v.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Quaternion:__delete()
	if self then Polycore.delete_Quaternion(self.__ptr) end
end
