class "AudioStreamingSource"







function AudioStreamingSource:AudioStreamingSource(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.AudioStreamingSource(unpack(arg))
	end
end

function AudioStreamingSource:getNumChannels()
	local retVal =  Polycore.AudioStreamingSource_getNumChannels(self.__ptr)
	return retVal
end

function AudioStreamingSource:getFrequency()
	local retVal =  Polycore.AudioStreamingSource_getFrequency(self.__ptr)
	return retVal
end

function AudioStreamingSource:__delete()
	if self then Polycore.delete_AudioStreamingSource(self.__ptr) end
end
