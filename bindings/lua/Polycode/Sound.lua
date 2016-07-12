class "Sound"


function Sound:Sound(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Sound(unpack(arg))
	end
end

function Sound:getSampleAsNumber(offset, channel, position, orientation)
	local retVal = Polycode.Sound_getSampleAsNumber(self.__ptr, offset, channel, position.__ptr, orientation.__ptr)
	return retVal
end

function Sound:loadFile(fileName)
	local retVal = Polycode.Sound_loadFile(self.__ptr, fileName)
end

function Sound:Play(loop, restartSound)
	local retVal = Polycode.Sound_Play(self.__ptr, loop, restartSound)
end

function Sound:Stop()
	local retVal =  Polycode.Sound_Stop(self.__ptr)
end

function Sound:setVolume(newVolume)
	local retVal = Polycode.Sound_setVolume(self.__ptr, newVolume)
end

function Sound:getVolume()
	local retVal =  Polycode.Sound_getVolume(self.__ptr)
	return retVal
end

function Sound:setPitch(newPitch)
	local retVal = Polycode.Sound_setPitch(self.__ptr, newPitch)
end

function Sound:getPitch()
	local retVal =  Polycode.Sound_getPitch(self.__ptr)
	return retVal
end

function Sound:isPlaying()
	local retVal =  Polycode.Sound_isPlaying(self.__ptr)
	return retVal
end

function Sound:isLooped()
	local retVal =  Polycode.Sound_isLooped(self.__ptr)
	return retVal
end

function Sound:setIsPositional(isPositional)
	local retVal = Polycode.Sound_setIsPositional(self.__ptr, isPositional)
end

function Sound:setSoundPosition(position)
	local retVal = Polycode.Sound_setSoundPosition(self.__ptr, position.__ptr)
end

function Sound:setSoundVelocity(velocity)
	local retVal = Polycode.Sound_setSoundVelocity(self.__ptr, velocity.__ptr)
end

function Sound:setSoundDirection(direction)
	local retVal = Polycode.Sound_setSoundDirection(self.__ptr, direction.__ptr)
end

function Sound:setOffset(offset)
	local retVal = Polycode.Sound_setOffset(self.__ptr, offset)
end

function Sound:getFileName()
	local retVal =  Polycode.Sound_getFileName(self.__ptr)
	return retVal
end

function Sound:getPlaybackDuration()
	local retVal =  Polycode.Sound_getPlaybackDuration(self.__ptr)
	return retVal
end

function Sound:getPlaybackTime()
	local retVal =  Polycode.Sound_getPlaybackTime(self.__ptr)
	return retVal
end

function Sound:seekTo(time)
	local retVal = Polycode.Sound_seekTo(self.__ptr, time)
end

function Sound:getOffset()
	local retVal =  Polycode.Sound_getOffset(self.__ptr)
	return retVal
end

function Sound:getSampleLength()
	local retVal =  Polycode.Sound_getSampleLength(self.__ptr)
	return retVal
end

function Sound:getFrequency()
	local retVal =  Polycode.Sound_getFrequency(self.__ptr)
	return retVal
end

function Sound:setPositionalProperties(referenceDistance, maxDistance)
	local retVal = Polycode.Sound_setPositionalProperties(self.__ptr, referenceDistance, maxDistance)
end

function Sound:setReferenceDistance(referenceDistance)
	local retVal = Polycode.Sound_setReferenceDistance(self.__ptr, referenceDistance)
end

function Sound:setMaxDistance(maxDistance)
	local retVal = Polycode.Sound_setMaxDistance(self.__ptr, maxDistance)
end

function Sound:getReferenceDistance()
	local retVal =  Polycode.Sound_getReferenceDistance(self.__ptr)
	return retVal
end

function Sound:getMaxDistance()
	local retVal =  Polycode.Sound_getMaxDistance(self.__ptr)
	return retVal
end

function Sound:loadWAV(fileName)
	local retVal = Polycode.Sound_loadWAV(self.__ptr, fileName)
	return retVal
end

function Sound:loadOGG(fileName)
	local retVal = Polycode.Sound_loadOGG(self.__ptr, fileName)
	return retVal
end

function Sound:soundCheck(result, err)
	local retVal = Polycode.Sound_soundCheck(self.__ptr, result, err)
end

function Sound:updateStream(streamCount)
	local retVal = Polycode.Sound_updateStream(self.__ptr, streamCount)
end

function Sound:__delete()
	if self then Polycode.delete_Sound(self.__ptr) end
end
