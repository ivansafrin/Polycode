class "SoundManager"

function SoundManager:SoundManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.SoundManager()
	end
end

function SoundManager:initAL()
	return Polycore.SoundManager_initAL(self.__ptr)
end

