class "SoundManager"


function SoundManager:SoundManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.SoundManager(unpack(arg))
	end
end

function SoundManager:setListenerPosition(position)
	local retVal = Polycode.SoundManager_setListenerPosition(self.__ptr, position.__ptr)
end

function SoundManager:setListenerOrientation(orientation)
	local retVal = Polycode.SoundManager_setListenerOrientation(self.__ptr, orientation.__ptr)
end

function SoundManager:recordSound(rate, sampleSize)
	local retVal = Polycode.SoundManager_recordSound(self.__ptr, rate, sampleSize)
	return retVal
end

function SoundManager:Update()
	local retVal =  Polycode.SoundManager_Update(self.__ptr)
end

function SoundManager:setGlobalVolume(globalVolume)
	local retVal = Polycode.SoundManager_setGlobalVolume(self.__ptr, globalVolume)
end

function SoundManager:__delete()
	if self then Polycode.delete_SoundManager(self.__ptr) end
end
