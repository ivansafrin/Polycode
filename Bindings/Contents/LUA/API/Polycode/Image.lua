class "Image"

function Image:Image(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Image(fileName)
	end
end

function Image:loadImage(fileName)
	return Polycore.Image_loadImage(self.__ptr, fileName)
end

function Image:loadPNG(fileName)
	return Polycore.Image_loadPNG(self.__ptr, fileName)
end

function Image:createEmpty(width, height)
	return Polycore.Image_createEmpty(self.__ptr, width, height)
end

function Image:fill(r, g, b, a)
	return Polycore.Image_fill(self.__ptr, r, g, b, a)
end

function Image:setPixel(x, y, r, g, b, a)
	return Polycore.Image_setPixel(self.__ptr, x, y, r, g, b, a)
end

function Image:getPixel(x, y)
	return Polycore.Image_getPixel(self.__ptr, x, y)
end

function Image:setAAPixel(x, y, col)
	return Polycore.Image_setAAPixel(self.__ptr, x, y, col.__ptr)
end

function Image:swap(v1, v2)
	return Polycore.Image_swap(self.__ptr, v1.__ptr, v2.__ptr)
end

function Image:line(x0, y0, x1, y1, col)
	return Polycore.Image_line(self.__ptr, x0, y0, x1, y1, col.__ptr)
end

function Image:moveTo(x, y)
	return Polycore.Image_moveTo(self.__ptr, x, y)
end

function Image:move(x, y)
	return Polycore.Image_move(self.__ptr, x, y)
end

function Image:lineTo(x, y, col)
	return Polycore.Image_lineTo(self.__ptr, x, y, col.__ptr)
end

function Image:drawRect(x, y, w, h, col)
	return Polycore.Image_drawRect(self.__ptr, x, y, w, h, col.__ptr)
end

function Image:perlinNoise(seed, alpha)
	return Polycore.Image_perlinNoise(self.__ptr, seed, alpha)
end

function Image:fastBlur(blurSize)
	return Polycore.Image_fastBlur(self.__ptr, blurSize)
end

function Image:fastBlurVert(blurSize)
	return Polycore.Image_fastBlurVert(self.__ptr, blurSize)
end

function Image:fastBlurHor(blurSize)
	return Polycore.Image_fastBlurHor(self.__ptr, blurSize)
end

function Image:darken(amt, color, alpha)
	return Polycore.Image_darken(self.__ptr, amt, color, alpha)
end

function Image:lighten(amt, color, alpha)
	return Polycore.Image_lighten(self.__ptr, amt, color, alpha)
end

function Image:multiply(amt, color, alpha)
	return Polycore.Image_multiply(self.__ptr, amt, color, alpha)
end

function Image:getBrushX()
	return Polycore.Image_getBrushX(self.__ptr)
end

function Image:getBrushY()
	return Polycore.Image_getBrushY(self.__ptr)
end

function Image:isLoaded()
	return Polycore.Image_isLoaded(self.__ptr)
end

function Image:getType()
	return Polycore.Image_getType(self.__ptr)
end

function Image:writeBMP(fileName)
	return Polycore.Image_writeBMP(self.__ptr, fileName)
end

function Image:getWidth()
	return Polycore.Image_getWidth(self.__ptr)
end

function Image:getHeight()
	return Polycore.Image_getHeight(self.__ptr)
end

function Image:getPixels()
	return Polycore.Image_getPixels(self.__ptr)
end

