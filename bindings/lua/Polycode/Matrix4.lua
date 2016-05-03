class "Matrix4"



function Matrix4:__getvar(name)
end


function Matrix4:__setvar(name,value)
	return false
end


function Matrix4:Matrix4(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Matrix4(unpack(arg))
	end
end

function Matrix4:identity()
	local retVal =  Polycore.Matrix4_identity(self.__ptr)
end

function Matrix4:rotateVector(v2)
	local retVal = Polycore.Matrix4_rotateVector(self.__ptr, v2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:getPosition()
	local retVal =  Polycore.Matrix4_getPosition(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:multiplyWithPerspective(v2)
	local retVal = Polycore.Matrix4_multiplyWithPerspective(self.__ptr, v2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:multVector3(v2)
	local retVal = Polycore.Matrix4_multVector3(self.__ptr, v2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:multVector4(v2)
	local retVal = Polycore.Matrix4_multVector4(self.__ptr, v2.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:Translate(x, y, z)
	local retVal = Polycore.Matrix4_Translate(self.__ptr, x, y, z)
end

function Matrix4:setPosition(x, y, z)
	local retVal = Polycore.Matrix4_setPosition(self.__ptr, x, y, z)
end

function Matrix4:setScale(scale)
	local retVal = Polycore.Matrix4_setScale(self.__ptr, scale.__ptr)
end

function Matrix4:getEulerAngles(ax, ay, az)
	local retVal = Polycore.Matrix4_getEulerAngles(self.__ptr, ax.__ptr, ay.__ptr, az.__ptr)
end

function Matrix4:transpose()
	local retVal =  Polycore.Matrix4_transpose(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:Inverse()
	local retVal =  Polycore.Matrix4_Inverse(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:inverseAffine()
	local retVal =  Polycore.Matrix4_inverseAffine(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:determinant()
	local retVal =  Polycore.Matrix4_determinant(self.__ptr)
	return retVal
end

function Matrix4.generalDeterminant(a, n)
	local retVal = Polycore.Matrix4_generalDeterminant(a.__ptr, n)
	if retVal == nil then return nil end
	local __c = _G["Number"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Matrix4:setOrthoProjection(left, right, bottom, top, zNear, zFar)
	local retVal = Polycore.Matrix4_setOrthoProjection(self.__ptr, left, right, bottom, top, zNear, zFar)
end

function Matrix4:setProjectionFrustum(left, right, bottom, top, zNear, zFar)
	local retVal = Polycore.Matrix4_setProjectionFrustum(self.__ptr, left, right, bottom, top, zNear, zFar)
end

function Matrix4:setProjection(fov, aspect, zNear, zFar)
	local retVal = Polycore.Matrix4_setProjection(self.__ptr, fov, aspect, zNear, zFar)
end

function Matrix4:__delete()
	if self then Polycore.delete_Matrix4(self.__ptr) end
end
