class "SkeletonAnimation"

function SkeletonAnimation:SkeletonAnimation(name, duration)
	if self.__ptr == nil then
		self.__ptr = Polycore.SkeletonAnimation(name, duration)
	end
end

function SkeletonAnimation:addBoneTrack(boneTrack)
	return Polycore.SkeletonAnimation_addBoneTrack(self.__ptr, boneTrack.__ptr)
end

function SkeletonAnimation:getName()
	return Polycore.SkeletonAnimation_getName(self.__ptr)
end

function SkeletonAnimation:Play()
	return Polycore.SkeletonAnimation_Play(self.__ptr)
end

function SkeletonAnimation:Stop()
	return Polycore.SkeletonAnimation_Stop(self.__ptr)
end

function SkeletonAnimation:Update()
	return Polycore.SkeletonAnimation_Update(self.__ptr)
end

function SkeletonAnimation:setSpeed(speed)
	return Polycore.SkeletonAnimation_setSpeed(self.__ptr, speed)
end

