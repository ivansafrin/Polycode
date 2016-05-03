class "AudioMixer"



function AudioMixer:__getvar(name)
	if name == "globalVolume" then
		return Polycore.AudioMixer_get_globalVolume(self.__ptr)
	elseif name == "mixerMutex" then
		local retVal = Polycore.AudioMixer_get_mixerMutex(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["CoreMutex"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function AudioMixer:__setvar(name,value)
	if name == "globalVolume" then
		Polycore.AudioMixer_set_globalVolume(self.__ptr, value)
		return true
	end
	return false
end


function AudioMixer:AudioMixer(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.AudioMixer(unpack(arg))
	end
end

function AudioMixer:mixIntoBuffer(buffer, numSamples)
	local retVal = Polycore.AudioMixer_mixIntoBuffer(self.__ptr, buffer.__ptr, numSamples)
end

function AudioMixer:__delete()
	if self then Polycore.delete_AudioMixer(self.__ptr) end
end
