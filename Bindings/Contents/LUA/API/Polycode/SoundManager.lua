class "SoundManager"







function SoundManager:SoundManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SoundManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SoundManager:initAL()
	local retVal =  Polycore.SoundManager_initAL(self.__ptr)
end

