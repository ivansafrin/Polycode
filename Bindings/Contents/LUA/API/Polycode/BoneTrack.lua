class "BoneTrack"

function BoneTrack:BoneTrack(bone, length)
	if self.__ptr == nil then
		self.__ptr = Polycore.BoneTrack(bone, length)
	end
end

function BoneTrack:Play()
	return Polycore.BoneTrack_Play(self.__ptr)
end

function BoneTrack:Stop()
	return Polycore.BoneTrack_Stop(self.__ptr)
end

function BoneTrack:Update()
	return Polycore.BoneTrack_Update(self.__ptr)
end

function BoneTrack:setSpeed(speed)
	return Polycore.BoneTrack_setSpeed(self.__ptr, speed)
end

