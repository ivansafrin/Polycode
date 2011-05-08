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

function Sound:Play(once)
	local retVal = Polycore.Sound_Play(self.__ptr, once)
end

function Sound:Stop()
	local retVal =  Polycore.Sound_Stop(self.__ptr)
end

function Sound:loadWAV(fileName)
	local retVal = Polycore.Sound_loadWAV(self.__ptr, fileName)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ALuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Sound:loadOGG(fileName)
	local retVal = Polycore.Sound_loadOGG(self.__ptr, fileName)
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
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ALuint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Sound:checkALError(operation)
	local retVal = Polycore.Sound_checkALError(self.__ptr, operation)
end

function Sound:soundError(err)
	local retVal = Polycore.Sound_soundError(self.__ptr, err)
end

function Sound:soundCheck(result, err)
	local retVal = Polycore.Sound_soundCheck(self.__ptr, result, err)
end



function Sound:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Sound(self.__ptr)
end
