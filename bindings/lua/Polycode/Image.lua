class "Image"

Image.IMAGE_RGB = 0
Image.IMAGE_RGBA = 1
Image.IMAGE_FP16 = 2

function Image:Image(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Image(unpack(arg))
	end
end

function Image:BlankImage(width, height, type)
	local retVal = Polycode.Image_BlankImage(self.__ptr, width, height, type)
	if retVal == nil then return nil end
	local __c = _G["Image"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Image:loadImage(fileName)
	local retVal = Polycode.Image_loadImage(self.__ptr, fileName)
	return retVal
end

function Image:saveImage(fileName)
	local retVal = Polycode.Image_saveImage(self.__ptr, fileName)
	return retVal
end

function Image:pasteImage(image, x, y, blendingMode, blendAmount, blendColor)
	local retVal = Polycode.Image_pasteImage(self.__ptr, image.__ptr, x, y, blendingMode, blendAmount, blendColor.__ptr)
end

function Image:createEmpty(width, height, fillColor)
	local retVal = Polycode.Image_createEmpty(self.__ptr, width, height, fillColor.__ptr)
end

function Image:fill(color)
	local retVal = Polycode.Image_fill(self.__ptr, color.__ptr)
end

function Image:setPixel(x, y, r, g, b, a)
	local retVal = Polycode.Image_setPixel(self.__ptr, x, y, r, g, b, a)
end

function Image:getPixel(x, y)
	local retVal = Polycode.Image_getPixel(self.__ptr, x, y)
	if retVal == nil then return nil end
	local __c = _G["Color"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Image:swap(v1, v2)
	local retVal = Polycode.Image_swap(self.__ptr, v1.__ptr, v2.__ptr)
end

function Image:drawLine(x0, y0, x1, y1, col)
	local retVal = Polycode.Image_drawLine(self.__ptr, x0, y0, x1, y1, col.__ptr)
end

function Image:moveBrushTo(x, y)
	local retVal = Polycode.Image_moveBrushTo(self.__ptr, x, y)
end

function Image:moveBrush(x, y)
	local retVal = Polycode.Image_moveBrush(self.__ptr, x, y)
end

function Image:drawLineTo(x, y, col)
	local retVal = Polycode.Image_drawLineTo(self.__ptr, x, y, col.__ptr)
end

function Image:fillRect(x, y, w, h, col)
	local retVal = Polycode.Image_fillRect(self.__ptr, x, y, w, h, col.__ptr)
end

function Image:perlinNoise(seed, alpha)
	local retVal = Polycode.Image_perlinNoise(self.__ptr, seed, alpha)
end

function Image:fastBlur(blurSize)
	local retVal = Polycode.Image_fastBlur(self.__ptr, blurSize)
end

function Image:fastBlurVert(blurSize)
	local retVal = Polycode.Image_fastBlurVert(self.__ptr, blurSize)
end

function Image:fastBlurHor(blurSize)
	local retVal = Polycode.Image_fastBlurHor(self.__ptr, blurSize)
end

function Image:getPixelsInRect(x, y, width, height)
	local retVal = Polycode.Image_getPixelsInRect(self.__ptr, x, y, width, height)
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Image:getImagePart(subRect)
	local retVal = Polycode.Image_getImagePart(self.__ptr, subRect.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Image"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Image:getBrushX()
	local retVal =  Polycode.Image_getBrushX(self.__ptr)
	return retVal
end

function Image:getBrushY()
	local retVal =  Polycode.Image_getBrushY(self.__ptr)
	return retVal
end

function Image:isLoaded()
	local retVal =  Polycode.Image_isLoaded(self.__ptr)
	return retVal
end

function Image:getType()
	local retVal =  Polycode.Image_getType(self.__ptr)
	return retVal
end

function Image:getWidth()
	local retVal =  Polycode.Image_getWidth(self.__ptr)
	return retVal
end

function Image:getHeight()
	local retVal =  Polycode.Image_getHeight(self.__ptr)
	return retVal
end

function Image:getPixels()
	local retVal =  Polycode.Image_getPixels(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Image:premultiplyAlpha()
	local retVal =  Polycode.Image_premultiplyAlpha(self.__ptr)
end

function Image:savePNG(fileName)
	local retVal = Polycode.Image_savePNG(self.__ptr, fileName)
	return retVal
end

function Image:__delete()
	if self then Polycode.delete_Image(self.__ptr) end
end
