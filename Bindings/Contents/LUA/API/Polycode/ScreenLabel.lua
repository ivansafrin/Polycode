require "Polycode/ScreenShape"

class "ScreenLabel" (ScreenShape)

function ScreenLabel:ScreenLabel(fontName, text, size, amode)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScreenLabel(fontName, text, size, amode)
	end
end

function ScreenLabel:addDropShadow(color, size, offsetX, offsetY)
	return Polycore.ScreenLabel_addDropShadow(self.__ptr, color.__ptr, size, offsetX, offsetY)
end

function ScreenLabel:setText(newText)
	return Polycore.ScreenLabel_setText(self.__ptr, newText)
end

function ScreenLabel:getText()
	return Polycore.ScreenLabel_getText(self.__ptr)
end

function ScreenLabel:getLabel()
	return Polycore.ScreenLabel_getLabel(self.__ptr)
end

