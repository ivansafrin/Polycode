function Image(fileName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Image(fileName)
	}
}


Image.prototype.BlankImage = function(width,height,type) {
	var retVal = new Image()
	retVal.__ptr = Polycode.Image_BlankImage(width, height, type)
	return retVal
}

Image.prototype.loadImage = function(fileName) {
	return Polycode.Image_loadImage(this.__ptr, fileName)
}

Image.prototype.saveImage = function(fileName) {
	return Polycode.Image_saveImage(this.__ptr, fileName)
}

Image.prototype.pasteImage = function(image,x,y,blendingMode,blendAmount,blendColor) {
	Polycode.Image_pasteImage(this.__ptr, image.__ptr, x, y, blendingMode, blendAmount, blendColor)
}

Image.prototype.createEmpty = function(width,height,fillColor) {
	Polycode.Image_createEmpty(this.__ptr, width, height, fillColor)
}

Image.prototype.fill = function(color) {
	Polycode.Image_fill(this.__ptr, color)
}

Image.prototype.setPixel = function(x,y,r,g,b,a) {
	Polycode.Image_setPixel(this.__ptr, x, y, r, g, b, a)
}

Image.prototype.getPixel = function(x,y) {
	var retVal = new Color()
	retVal.__ptr = Polycode.Image_getPixel(this.__ptr, x, y)
	return retVal
}

Image.prototype.swap = function(v1,v2) {
	Polycode.Image_swap(this.__ptr, v1.__ptr, v2.__ptr)
}

Image.prototype.drawLine = function(x0,y0,x1,y1,col) {
	Polycode.Image_drawLine(this.__ptr, x0, y0, x1, y1, col)
}

Image.prototype.moveBrushTo = function(x,y) {
	Polycode.Image_moveBrushTo(this.__ptr, x, y)
}

Image.prototype.moveBrush = function(x,y) {
	Polycode.Image_moveBrush(this.__ptr, x, y)
}

Image.prototype.drawLineTo = function(x,y,col) {
	Polycode.Image_drawLineTo(this.__ptr, x, y, col)
}

Image.prototype.fillRect = function(x,y,w,h,col) {
	Polycode.Image_fillRect(this.__ptr, x, y, w, h, col)
}

Image.prototype.perlinNoise = function(seed,alpha) {
	Polycode.Image_perlinNoise(this.__ptr, seed, alpha)
}

Image.prototype.fastBlur = function(blurSize) {
	Polycode.Image_fastBlur(this.__ptr, blurSize)
}

Image.prototype.fastBlurVert = function(blurSize) {
	Polycode.Image_fastBlurVert(this.__ptr, blurSize)
}

Image.prototype.fastBlurHor = function(blurSize) {
	Polycode.Image_fastBlurHor(this.__ptr, blurSize)
}

Image.prototype.getPixelsInRect = function(x,y,width,height) {
	var retVal = new char()
	retVal.__ptr = Polycode.Image_getPixelsInRect(this.__ptr, x, y, width, height)
	return retVal
}

Image.prototype.getImagePart = function(subRect) {
	var retVal = new Image()
	retVal.__ptr = Polycode.Image_getImagePart(this.__ptr, subRect)
	return retVal
}

Image.prototype.getBrushX = function() {
	return Polycode.Image_getBrushX(this.__ptr)
}

Image.prototype.getBrushY = function() {
	return Polycode.Image_getBrushY(this.__ptr)
}

Image.prototype.isLoaded = function() {
	return Polycode.Image_isLoaded(this.__ptr)
}

Image.prototype.getType = function() {
	return Polycode.Image_getType(this.__ptr)
}

Image.prototype.getWidth = function() {
	return Polycode.Image_getWidth(this.__ptr)
}

Image.prototype.getHeight = function() {
	return Polycode.Image_getHeight(this.__ptr)
}

Image.prototype.getPixels = function() {
	var retVal = new char()
	retVal.__ptr = Polycode.Image_getPixels(this.__ptr)
	return retVal
}

Image.prototype.premultiplyAlpha = function() {
	Polycode.Image_premultiplyAlpha(this.__ptr)
}

Image.prototype.savePNG = function(fileName) {
	return Polycode.Image_savePNG(this.__ptr, fileName)
}
