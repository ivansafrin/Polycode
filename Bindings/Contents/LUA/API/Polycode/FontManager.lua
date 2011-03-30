class "FontManager"

function FontManager:FontManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.FontManager()
	end
end

function FontManager:registerFont(fontName, fontPath)
	return Polycore.FontManager_registerFont(self.__ptr, fontName, fontPath)
end

function FontManager:getFontByName(fontName)
	return Polycore.FontManager_getFontByName(self.__ptr, fontName)
end

