class "FontManager"







function FontManager:FontManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.FontManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function FontManager:registerFont(fontName, fontPath)
	local retVal = Polycore.FontManager_registerFont(self.__ptr, fontName, fontPath)
end

function FontManager:getFontByName(fontName)
	local retVal = Polycore.FontManager_getFontByName(self.__ptr, fontName)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Font("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

