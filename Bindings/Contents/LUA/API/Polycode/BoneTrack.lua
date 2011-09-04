class "BoneTrack"



function BoneTrack:__index__(name)
	if name == "LocXVec" then
		retVal = Polycore.BoneTrack_get_LocXVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "LocYVec" then
		retVal = Polycore.BoneTrack_get_LocYVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "LocZVec" then
		retVal = Polycore.BoneTrack_get_LocZVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "ScaleXVec" then
		retVal = Polycore.BoneTrack_get_ScaleXVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "ScaleYVec" then
		retVal = Polycore.BoneTrack_get_ScaleYVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "ScaleZVec" then
		retVal = Polycore.BoneTrack_get_ScaleZVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "boneQuat" then
		retVal = Polycore.BoneTrack_get_boneQuat(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "QuatWVec" then
		retVal = Polycore.BoneTrack_get_QuatWVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "QuatXVec" then
		retVal = Polycore.BoneTrack_get_QuatXVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "QuatYVec" then
		retVal = Polycore.BoneTrack_get_QuatYVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "QuatZVec" then
		retVal = Polycore.BoneTrack_get_QuatZVec(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function BoneTrack:__set_callback(name,value)
	return false
end


function BoneTrack:BoneTrack(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.BoneTrack(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function BoneTrack:Play(once)
	local retVal = Polycore.BoneTrack_Play(self.__ptr, once)
end

function BoneTrack:Stop()
	local retVal =  Polycore.BoneTrack_Stop(self.__ptr)
end

function BoneTrack:Update()
	local retVal =  Polycore.BoneTrack_Update(self.__ptr)
end

function BoneTrack:setSpeed(speed)
	local retVal = Polycore.BoneTrack_setSpeed(self.__ptr, speed)
end



function BoneTrack:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_BoneTrack(self.__ptr)
end
