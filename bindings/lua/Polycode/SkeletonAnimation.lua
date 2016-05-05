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
		self.__ptr = Polycode.SkeletonAnimation(unpack(arg))
	end
end

function SkeletonAnimation:addBoneTrack(boneTrack)
	local retVal = Polycode.SkeletonAnimation_addBoneTrack(self.__ptr, boneTrack.__ptr)
end

function SkeletonAnimation:getName()
	local retVal =  Polycode.SkeletonAnimation_getName(self.__ptr)
	return retVal
end

function SkeletonAnimation:Play(once)
	local retVal = Polycode.SkeletonAnimation_Play(self.__ptr, once)
end

function SkeletonAnimation:Stop()
	local retVal =  Polycode.SkeletonAnimation_Stop(self.__ptr)
end

function SkeletonAnimation:Reset()
	local retVal =  Polycode.SkeletonAnimation_Reset(self.__ptr)
end

function SkeletonAnimation:Update()
	local retVal =  Polycode.SkeletonAnimation_Update(self.__ptr)
end

function SkeletonAnimation:setSpeed(speed)
	local retVal = Polycode.SkeletonAnimation_setSpeed(self.__ptr, speed)
end

function SkeletonAnimation:setWeight(newWeight)
	local retVal = Polycode.SkeletonAnimation_setWeight(self.__ptr, newWeight)
end

function SkeletonAnimation:getWeight()
	local retVal =  Polycode.SkeletonAnimation_getWeight(self.__ptr)
	return retVal
end

function SkeletonAnimation:isPlaying()
	local retVal =  Polycode.SkeletonAnimation_isPlaying(self.__ptr)
	return retVal
end

function SkeletonAnimation:__delete()
	if self then Polycode.delete_SkeletonAnimation(self.__ptr) end
end
