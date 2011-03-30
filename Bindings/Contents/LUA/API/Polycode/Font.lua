class "Font"

function Font:Font(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Font(fileName)
	end
end

function Font:getFace()
	return Polycore.Font_getFace(self.__ptr)
end

function Font:isValid()
	return Polycore.Font_isValid(self.__ptr)
end

