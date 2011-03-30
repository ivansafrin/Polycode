require "Polycode/Image"

class "Label" (Image)

function Label:Label(font, text, size, antiAliasMode)
	if self.__ptr == nil then
		self.__ptr = Polycore.Label(font, text, size, antiAliasMode)
	end
end

function Label:setText(text)
	return Polycore.Label_setText(self.__ptr, text)
end

function Label:getText()
	return Polycore.Label_getText(self.__ptr)
end

function Label:getTextWidth(font, text, size)
	return Polycore.Label_getTextWidth(self.__ptr, font.__ptr, text, size)
end

function Label:getTextHeight(font, text, size)
	return Polycore.Label_getTextHeight(self.__ptr, font.__ptr, text, size)
end

function Label:getFont()
	return Polycore.Label_getFont(self.__ptr)
end

