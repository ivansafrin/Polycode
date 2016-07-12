class "AudioMixer"


function AudioMixer:__getvar(name)
	if name == "globalVolume" then
		return Polycode.AudioMixer_get_globalVolume(self.__ptr)
	elseif name == "listenerPosition" then
		local retVal = Polycode.AudioMixer_get_listenerPosition(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "listenerOrientation" then
		local retVal = Polycode.AudioMixer_get_listenerOrientation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function AudioMixer:__setvar(name,value)
	if name == "globalVolume" then
		Polycode.AudioMixer_set_globalVolume(self.__ptr, value)
		return true
	elseif name == "listenerPosition" then
		Polycode.AudioMixer_set_listenerPosition(self.__ptr, value.__ptr)
		return true
	elseif name == "listenerOrientation" then
		Polycode.AudioMixer_set_listenerOrientation(self.__ptr, value.__ptr)
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
		self.__ptr = Polycode.AudioMixer(unpack(arg))
	end
end

function AudioMixer:__delete()
	if self then Polycode.delete_AudioMixer(self.__ptr) end
end
