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
		self.__ptr = Polycore.Sound(unpack(arg))
	end
end

function Sound:getSampleAsNumber(offset, channel)
	local retVal = Polycore.Sound_getSampleAsNumber(self.__ptr, offset, channel)
	return retVal
end

function Sound:loadFile(fileName)
	local retVal = Polycore.Sound_loadFile(self.__ptr, fileName)
end

function Sound:Play(loop, restartSound)
	local retVal = Polycore.Sound_Play(self.__ptr, loop, restartSound)
end

function Sound:Stop()
	local retVal =  Polycore.Sound_Stop(self.__ptr)
end

function Sound:setVolume(newVolume)
	local retVal = Polycore.Sound_setVolume(self.__ptr, newVolume)
end

function Sound:getVolume()
	local retVal =  Polycore.Sound_getVolume(self.__ptr)
	return retVal
end

function Sound:setPitch(newPitch)
	local retVal = Polycore.Sound_setPitch(self.__ptr, newPitch)
end

function Sound:getPitch()
	local retVal =  Polycore.Sound_getPitch(self.__ptr)
	return retVal
end

function Sound:isPlaying()
	local retVal =  Polycore.Sound_isPlaying(self.__ptr)
	return retVal
end

function Sound:isLooped()
	local retVal =  Polycore.Sound_isLooped(self.__ptr)
	return retVal
end

function Sound:setIsPositional(isPositional)
	local retVal = Polycore.Sound_setIsPositional(self.__ptr, isPositional)
end

function Sound:setSoundPosition(position)
	local retVal = Polycore.Sound_setSoundPosition(self.__ptr, position.__ptr)
end

function Sound:setSoundVelocity(velocity)
	local retVal = Polycore.Sound_setSoundVelocity(self.__ptr, velocity.__ptr)
end

function Sound:setSoundDirection(direction)
	local retVal = Polycore.Sound_setSoundDirection(self.__ptr, direction.__ptr)
end

function Sound:setOffset(offset)
	local retVal = Polycore.Sound_setOffset(self.__ptr, offset)
end

function Sound:getFileName()
	local retVal =  Polycore.Sound_getFileName(self.__ptr)
	return retVal
end

function Sound:getPlaybackDuration()
	local retVal =  Polycore.Sound_getPlaybackDuration(self.__ptr)
	return retVal
end

function Sound:getPlaybackTime()
	local retVal =  Polycore.Sound_getPlaybackTime(self.__ptr)
	return retVal
end

function Sound:seekTo(time)
	local retVal = Polycore.Sound_seekTo(self.__ptr, time)
end

function Sound:getOffset()
	local retVal =  Polycore.Sound_getOffset(self.__ptr)
	return retVal
end

function Sound:getSampleLength()
	local retVal =  Polycore.Sound_getSampleLength(self.__ptr)
	return retVal
end

function Sound:getFrequency()
	local retVal =  Polycore.Sound_getFrequency(self.__ptr)
	return retVal
end

function Sound:setPositionalProperties(referenceDistance, maxDistance)
	local retVal = Polycore.Sound_setPositionalProperties(self.__ptr, referenceDistance, maxDistance)
end

function Sound:setReferenceDistance(referenceDistance)
	local retVal = Polycore.Sound_setReferenceDistance(self.__ptr, referenceDistance)
end

function Sound:setMaxDistance(maxDistance)
	local retVal = Polycore.Sound_setMaxDistance(self.__ptr, maxDistance)
end

function Sound:getReferenceDistance()
	local retVal =  Polycore.Sound_getReferenceDistance(self.__ptr)
	return retVal
end

function Sound:getMaxDistance()
	local retVal =  Polycore.Sound_getMaxDistance(self.__ptr)
	return retVal
end

function Sound:loadBytes(data, size, channels, freq, format)
	local retVal = Polycore.Sound_loadBytes(self.__ptr, data.__ptr, size, channels, freq, format.__ptr)
	return retVal
end

function Sound:loadWAV(fileName)
	local retVal = Polycore.Sound_loadWAV(self.__ptr, fileName)
	return retVal
end

function Sound:loadOGG(fileName)
	local retVal = Polycore.Sound_loadOGG(self.__ptr, fileName)
	return retVal
end

function Sound:soundCheck(result, err)
	local retVal = Polycore.Sound_soundCheck(self.__ptr, result, err)
end

function Sound:updateStream(streamCount)
	local retVal = Polycore.Sound_updateStream(self.__ptr, streamCount)
end

function Sound:__delete()
	if self then Polycore.delete_Sound(self.__ptr) end
end
