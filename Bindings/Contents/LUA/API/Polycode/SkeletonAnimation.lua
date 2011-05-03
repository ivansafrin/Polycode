class "SkeletonAnimation"







function SkeletonAnimation:SkeletonAnimation(...)
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
	return retVal
end

function SkeletonAnimation:Play()
	local retVal =  Polycore.SkeletonAnimation_Play(self.__ptr)
end

function SkeletonAnimation:Stop()
	local retVal =  Polycore.SkeletonAnimation_Stop(self.__ptr)
end

function SkeletonAnimation:Update()
	local retVal =  Polycore.SkeletonAnimation_Update(self.__ptr)
end

function SkeletonAnimation:setSpeed(speed)
	local retVal = Polycore.SkeletonAnimation_setSpeed(self.__ptr, speed)
end

