class "Color"

function Color:Color()
	if self.__ptr == nil then
		self.__ptr = Polycore.Color()
	end
end

function Color:setColorHex(hex)
	return Polycore.Color_setColorHex(self.__ptr, hex)
end

function Color:setColorHexRGB(hex)
	return Polycore.Color_setColorHexRGB(self.__ptr, hex)
end

function Color:setColorHSV(h, s, v)
	return Polycore.Color_setColorHSV(self.__ptr, h, s, v)
end

function Color:setColorRGBA(r, g, b, a)
	return Polycore.Color_setColorRGBA(self.__ptr, r, g, b, a)
end

function Color:setColorRGB(r, g, b)
	return Polycore.Color_setColorRGB(self.__ptr, r, g, b)
end

function Color:setColor(r, g, b, a)
	return Polycore.Color_setColor(self.__ptr, r, g, b, a)
end

function Color:Random()
	return Polycore.Color_Random(self.__ptr)
end

function Color:getBrightness()
	return Polycore.Color_getBrightness(self.__ptr)
end

function Color:getUint()
	return Polycore.Color_getUint(self.__ptr)
end

