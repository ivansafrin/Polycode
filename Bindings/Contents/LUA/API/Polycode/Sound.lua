class "Sound"

function Sound:Sound(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Sound(fileName)
	end
end

function Sound:Play(once)
	return Polycore.Sound_Play(self.__ptr, once)
end

function Sound:Stop()
	return Polycore.Sound_Stop(self.__ptr)
end

function Sound:loadWAV(fileName)
	return Polycore.Sound_loadWAV(self.__ptr, fileName)
end

function Sound:loadOGG(fileName)
	return Polycore.Sound_loadOGG(self.__ptr, fileName)
end

function Sound:GenSource(buffer)
	return Polycore.Sound_GenSource(self.__ptr, buffer.__ptr)
end

function Sound:checkALError(operation)
	return Polycore.Sound_checkALError(self.__ptr, operation)
end

function Sound:soundError(err)
	return Polycore.Sound_soundError(self.__ptr, err)
end

function Sound:soundCheck(result, err)
	return Polycore.Sound_soundCheck(self.__ptr, result, err)
end

