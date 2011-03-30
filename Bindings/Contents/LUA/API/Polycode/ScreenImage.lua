require "Polycode/ScreenShape"

class "ScreenImage" (ScreenShape)

function ScreenImage:ScreenImage(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenImage(fileName)
	end
end

function ScreenImage:setImageCoordinates(x, y, width, height)
	return Polycore.ScreenImage_setImageCoordinates(self.__ptr, x, y, width, height)
end

function ScreenImage:getImageWidth()
	return Polycore.ScreenImage_getImageWidth(self.__ptr)
end

function ScreenImage:getImageHeight()
	return Polycore.ScreenImage_getImageHeight(self.__ptr)
end

