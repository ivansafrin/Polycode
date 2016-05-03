class "SkeletonAnimation"







function SkeletonAnimation:SkeletonAnimation(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SkeletonAnimation(unpack(arg))
	end
end

function SkeletonAnimation:addBoneTrack(boneTrack)
	local retVal = Polycore.SkeletonAnimation_addBoneTrack(self.__ptr, boneTrack.__ptr)
end

function SkeletonAnimation:getName()
	local retVal =  Polycore.SkeletonAnimation_getName(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SkeletonAnimation:Play(once)
	local retVal = Polycore.SkeletonAnimation_Play(self.__ptr, once)
end

function SkeletonAnimation:Stop()
	local retVal =  Polycore.SkeletonAnimation_Stop(self.__ptr)
end

function SkeletonAnimation:Reset()
	local retVal =  Polycore.SkeletonAnimation_Reset(self.__ptr)
end

function SkeletonAnimation:Update()
	local retVal =  Polycore.SkeletonAnimation_Update(self.__ptr)
end

function SkeletonAnimation:setSpeed(speed)
	local retVal = Polycore.SkeletonAnimation_setSpeed(self.__ptr, speed)
end

function SkeletonAnimation:setWeight(newWeight)
	local retVal = Polycore.SkeletonAnimation_setWeight(self.__ptr, newWeight)
end

function SkeletonAnimation:getWeight()
	local retVal =  Polycore.SkeletonAnimation_getWeight(self.__ptr)
	return retVal
end

function SkeletonAnimation:isPlaying()
	local retVal =  Polycore.SkeletonAnimation_isPlaying(self.__ptr)
	return retVal
end

function SkeletonAnimation:__delete()
	if self then Polycore.delete_SkeletonAnimation(self.__ptr) end
end
