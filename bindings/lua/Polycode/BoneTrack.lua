class "BoneTrack"


function BoneTrack:__getvar(name)
	if name == "position" then
		local retVal = Polycode.BoneTrack_get_position(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "scale" then
		local retVal = Polycode.BoneTrack_get_scale(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "boneQuat" then
		local retVal = Polycode.BoneTrack_get_boneQuat(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "weight" then
		return Polycode.BoneTrack_get_weight(self.__ptr)
	end
end

function BoneTrack:__setvar(name,value)
	if name == "position" then
		Polycode.BoneTrack_set_position(self.__ptr, value.__ptr)
		return true
	elseif name == "scale" then
		Polycode.BoneTrack_set_scale(self.__ptr, value.__ptr)
		return true
	elseif name == "boneQuat" then
		Polycode.BoneTrack_set_boneQuat(self.__ptr, value.__ptr)
		return true
	elseif name == "weight" then
		Polycode.BoneTrack_set_weight(self.__ptr, value)
		return true
	end
	return false
end
function BoneTrack:BoneTrack(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.BoneTrack(unpack(arg))
	end
end

function BoneTrack:Play(once)
	local retVal = Polycode.BoneTrack_Play(self.__ptr, once)
end

function BoneTrack:Stop()
	local retVal =  Polycode.BoneTrack_Stop(self.__ptr)
end

function BoneTrack:Update(elapsed)
	local retVal = Polycode.BoneTrack_Update(self.__ptr, elapsed)
end

function BoneTrack:Reset()
	local retVal =  Polycode.BoneTrack_Reset(self.__ptr)
end

function BoneTrack:setSpeed(speed)
	local retVal = Polycode.BoneTrack_setSpeed(self.__ptr, speed)
end

function BoneTrack:__delete()
	if self then Polycode.delete_BoneTrack(self.__ptr) end
end
