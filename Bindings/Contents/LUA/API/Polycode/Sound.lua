class "Sound"







function Sound:Sound(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Sound(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Sound:Play(loop)
	local retVal = Polycore.Sound_Play(self.__ptr, loop)
end

function Sound:Stop()
	local retVal =  Polycore.Sound_Stop(self.__ptr)
end

function Sound:setVolume(newVolume)
	local retVal = Polycore.Sound_setVolume(self.__ptr, newVolume)
end

function Sound:setPitch(newPitch)
	local retVal = Polycore.Sound_setPitch(self.__ptr, newPitch)
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

function Sound:setPositionalProperties(referenceDistance, maxDistance)
	local retVal = Polycore.Sound_setPositionalProperties(self.__ptr, referenceDistance, maxDistance)
end

function Sound:loadWAV(fileName)
	local retVal = Polycore.Sound_loadWAV(self.__ptr, fileName.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ALuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Sound:loadOGG(fileName)
	local retVal = Polycore.Sound_loadOGG(self.__ptr, fileName.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ALuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Sound:GenSource(buffer)
	local retVal = Polycore.Sound_GenSource(self.__ptr, buffer.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ALuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Sound:checkALError(operation)
	local retVal = Polycore.Sound_checkALError(self.__ptr, operation.__ptr)
end

function Sound:soundError(err)
	local retVal = Polycore.Sound_soundError(self.__ptr, err.__ptr)
end

function Sound:soundCheck(result, err)
	local retVal = Polycore.Sound_soundCheck(self.__ptr, result, err.__ptr)
end



function Sound:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Sound(self.__ptr)
end
