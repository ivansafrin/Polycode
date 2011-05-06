class "Image"



IMAGE_RGB = 0
IMAGE_RGBA = 1




function Image:Image(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Image(unpack(arg))
	end
end

function Image:loadImage(fileName)
	local retVal = Polycore.Image_loadImage(self.__ptr, fileName)
	return retVal
end

function Image:loadPNG(fileName)
	local retVal = Polycore.Image_loadPNG(self.__ptr, fileName)
	return retVal
end

function Image:createEmpty(width, height)
	local retVal = Polycore.Image_createEmpty(self.__ptr, width, height)
end

function Image:fill(r, g, b, a)
	local retVal = Polycore.Image_fill(self.__ptr, r, g, b, a)
end

function Image:setPixel(x, y, r, g, b, a)
	local retVal = Polycore.Image_setPixel(self.__ptr, x, y, r, g, b, a)
end

function Image:getPixel(x, y)
	local retVal = Polycore.Image_getPixel(self.__ptr, x, y)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Color("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Image:swap(v1, v2)
	local retVal = Polycore.Image_swap(self.__ptr, v1.__ptr, v2.__ptr)
end

function Image:line(x0, y0, x1, y1, col)
	local retVal = Polycore.Image_line(self.__ptr, x0, y0, x1, y1, col.__ptr)
end

function Image:moveTo(x, y)
	local retVal = Polycore.Image_moveTo(self.__ptr, x, y)
end

function Image:move(x, y)
	local retVal = Polycore.Image_move(self.__ptr, x, y)
end

function Image:lineTo(x, y, col)
	local retVal = Polycore.Image_lineTo(self.__ptr, x, y, col.__ptr)
end

function Image:drawRect(x, y, w, h, col)
	local retVal = Polycore.Image_drawRect(self.__ptr, x, y, w, h, col.__ptr)
end

function Image:perlinNoise(seed, alpha)
	local retVal = Polycore.Image_perlinNoise(self.__ptr, seed, alpha)
end

function Image:fastBlur(blurSize)
	local retVal = Polycore.Image_fastBlur(self.__ptr, blurSize)
end

function Image:fastBlurVert(blurSize)
	local retVal = Polycore.Image_fastBlurVert(self.__ptr, blurSize)
end

function Image:fastBlurHor(blurSize)
	local retVal = Polycore.Image_fastBlurHor(self.__ptr, blurSize)
end

function Image:darken(amt, color, alpha)
	local retVal = Polycore.Image_darken(self.__ptr, amt, color, alpha)
end

function Image:lighten(amt, color, alpha)
	local retVal = Polycore.Image_lighten(self.__ptr, amt, color, alpha)
end

function Image:multiply(amt, color, alpha)
	local retVal = Polycore.Image_multiply(self.__ptr, amt, color, alpha)
end

function Image:getBrushX()
	local retVal =  Polycore.Image_getBrushX(self.__ptr)
	return retVal
end

function Image:getBrushY()
	local retVal =  Polycore.Image_getBrushY(self.__ptr)
	return retVal
end

function Image:isLoaded()
	local retVal =  Polycore.Image_isLoaded(self.__ptr)
	return retVal
end

function Image:getType()
	local retVal =  Polycore.Image_getType(self.__ptr)
	return retVal
end

function Image:writeBMP(fileName)
	local retVal = Polycore.Image_writeBMP(self.__ptr, fileName)
end

function Image:getWidth()
	local retVal =  Polycore.Image_getWidth(self.__ptr)
	return retVal
end

function Image:getHeight()
	local retVal =  Polycore.Image_getHeight(self.__ptr)
	return retVal
end

function Image:getPixels()
	local retVal =  Polycore.Image_getPixels(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

