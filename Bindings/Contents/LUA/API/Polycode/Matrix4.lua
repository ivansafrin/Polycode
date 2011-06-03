class "Matrix4"







function Matrix4:Matrix4(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Matrix4(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Matrix4:identity()
	local retVal =  Polycore.Matrix4_identity(self.__ptr)
end

function Matrix4:rotateVector(v2)
	local retVal = Polycore.Matrix4_rotateVector(self.__ptr, v2.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Matrix4:getPosition()
	local retVal =  Polycore.Matrix4_getPosition(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
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

function Matrix4:inverse()
	local retVal =  Polycore.Matrix4_inverse(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Matrix4:inverseAffine()
	local retVal =  Polycore.Matrix4_inverseAffine(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Matrix4:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Matrix4(self.__ptr)
end
