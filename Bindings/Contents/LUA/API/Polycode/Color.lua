class "Color"



function Color:__index__(name)
	if name == "r" then
		return Polycore.Color_get_r(self.__ptr)
	elseif name == "g" then
		return Polycore.Color_get_g(self.__ptr)
	elseif name == "b" then
		return Polycore.Color_get_b(self.__ptr)
	elseif name == "a" then
		return Polycore.Color_get_a(self.__ptr)
	end
end


function Color:__set_callback(name,value)
	if name == "r" then
		Polycore.Color_set_r(self.__ptr, value)
		return true
	elseif name == "g" then
		Polycore.Color_set_g(self.__ptr, value)
		return true
	elseif name == "b" then
		Polycore.Color_set_b(self.__ptr, value)
		return true
	elseif name == "a" then
		Polycore.Color_set_a(self.__ptr, value)
		return true
	end
	return false
end


function Color:Color(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Color(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Color:setColorHex(hex)
	local retVal = Polycore.Color_setColorHex(self.__ptr, hex)
end

function Color:setColorHexRGB(hex)
	local retVal = Polycore.Color_setColorHexRGB(self.__ptr, hex)
end

function Color:setColorHSV(h, s, v)
	local retVal = Polycore.Color_setColorHSV(self.__ptr, h, s, v)
end

function Color:setColorRGBA(r, g, b, a)
	local retVal = Polycore.Color_setColorRGBA(self.__ptr, r, g, b, a)
end

function Color:setColorRGB(r, g, b)
	local retVal = Polycore.Color_setColorRGB(self.__ptr, r, g, b)
end

function Color:setColor(r, g, b, a)
	local retVal = Polycore.Color_setColor(self.__ptr, r, g, b, a)
end

function Color:Random()
	local retVal =  Polycore.Color_Random(self.__ptr)
end

function Color:getBrightness()
	local retVal =  Polycore.Color_getBrightness(self.__ptr)
	return retVal
end

function Color:getUint()
	local retVal =  Polycore.Color_getUint(self.__ptr)
	return retVal
end



function Color:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Color(self.__ptr)
end
