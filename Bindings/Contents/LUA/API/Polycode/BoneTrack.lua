class "BoneTrack"







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

function BoneTrack:Play()
	local retVal =  Polycore.BoneTrack_Play(self.__ptr)
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

