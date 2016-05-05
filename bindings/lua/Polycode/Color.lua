class "Color"

Color.BLEND_NORMAL = 0
Color.BLEND_REPLACE_COLOR = 1
Color.BLEND_ADDITIVE = 2

function Color:__getvar(name)
	if name == "r" then
		return Polycode.Color_get_r(self.__ptr)
	elseif name == "g" then
		return Polycode.Color_get_g(self.__ptr)
	elseif name == "b" then
		return Polycode.Color_get_b(self.__ptr)
	elseif name == "a" then
		return Polycode.Color_get_a(self.__ptr)
	end
end

function Color:__setvar(name,value)
	if name == "r" then
		Polycode.Color_set_r(self.__ptr, value)
		return true
	elseif name == "g" then
		Polycode.Color_set_g(self.__ptr, value)
		return true
	elseif name == "b" then
		Polycode.Color_set_b(self.__ptr, value)
		return true
	elseif name == "a" then
		Polycode.Color_set_a(self.__ptr, value)
		return true
	end
	return false
end
function Color:Color(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Color(unpack(arg))
	end
end

function Color:ColorWithInts(r, g, b, a)
	local retVal = Polycode.Color_ColorWithInts(self.__ptr, r, g, b, a)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Color:ColorWithHex(hex)
	local retVal = Polycode.Color_ColorWithHex(self.__ptr, hex)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Color:setColorHex(hex)
	local retVal = Polycode.Color_setColorHex(self.__ptr, hex)
end

function Color:setColorHexRGB(hex)
	local retVal = Polycode.Color_setColorHexRGB(self.__ptr, hex)
end

function Color:setColorHexFromString(hex)
	local retVal = Polycode.Color_setColorHexFromString(self.__ptr, hex)
end

function Color:setColorHexRGBFromString(hex)
	local retVal = Polycode.Color_setColorHexRGBFromString(self.__ptr, hex)
end

function Color:setColorHSV(h, s, v)
	local retVal = Polycode.Color_setColorHSV(self.__ptr, h, s, v)
end

function Color:setColorRGBA(r, g, b, a)
	local retVal = Polycode.Color_setColorRGBA(self.__ptr, r, g, b, a)
end

function Color:setColorRGB(r, g, b)
	local retVal = Polycode.Color_setColorRGB(self.__ptr, r, g, b)
end

function Color:setColor(r, g, b, a)
	local retVal = Polycode.Color_setColor(self.__ptr, r, g, b, a)
end

function Color:blendColor(c2, mode, amount, c3)
	local retVal = Polycode.Color_blendColor(self.__ptr, c2.__ptr, mode, amount, c3.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Color:Random()
	local retVal =  Polycode.Color_Random(self.__ptr)
end

function Color:getBrightness()
	local retVal =  Polycode.Color_getBrightness(self.__ptr)
	return retVal
end

function Color:RGBtoHSV(r, g, b, h, s, v)
	local retVal = Polycode.Color_RGBtoHSV(self.__ptr, r, g, b, h, s, v)
end

function Color:getHue()
	local retVal =  Polycode.Color_getHue(self.__ptr)
	return retVal
end

function Color:getSaturation()
	local retVal =  Polycode.Color_getSaturation(self.__ptr)
	return retVal
end

function Color:getValue()
	local retVal =  Polycode.Color_getValue(self.__ptr)
	return retVal
end

function Color:getUint()
	local retVal =  Polycode.Color_getUint(self.__ptr)
	return retVal
end

function Color:__delete()
	if self then Polycode.delete_Color(self.__ptr) end
end
