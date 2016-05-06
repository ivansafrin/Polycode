function Image() {
}

Image.prototype.loadImage = function(fileName) {
	Polycode.Image_loadImage(this.__ptr, fileName)
}

Image.prototype.saveImage = function(fileName) {
	Polycode.Image_saveImage(this.__ptr, fileName)
}

Image.prototype.pasteImage = function(image,x,y,blendingMode,blendAmount,blendColor) {
	Polycode.Image_pasteImage(this.__ptr, image,x,y,blendingMode,blendAmount,blendColor)
}

Image.prototype.createEmpty = function(width,height,fillColor) {
	Polycode.Image_createEmpty(this.__ptr, width,height,fillColor)
}

Image.prototype.fill = function(color) {
	Polycode.Image_fill(this.__ptr, color)
}

Image.prototype.setPixel = function(x,y,r,g,b,a) {
	Polycode.Image_setPixel(this.__ptr, x,y,r,g,b,a)
}

Image.prototype.getPixel = function(x,y) {
	Polycode.Image_getPixel(this.__ptr, x,y)
}

Image.prototype.swap = function(v1,v2) {
	Polycode.Image_swap(this.__ptr, v1,v2)
}

Image.prototype.drawLine = function(x0,y0,x1,y1,col) {
	Polycode.Image_drawLine(this.__ptr, x0,y0,x1,y1,col)
}

Image.prototype.moveBrushTo = function(x,y) {
	Polycode.Image_moveBrushTo(this.__ptr, x,y)
}

Image.prototype.moveBrush = function(x,y) {
	Polycode.Image_moveBrush(this.__ptr, x,y)
}

Image.prototype.drawLineTo = function(x,y,col) {
	Polycode.Image_drawLineTo(this.__ptr, x,y,col)
}

Image.prototype.fillRect = function(x,y,w,h,col) {
	Polycode.Image_fillRect(this.__ptr, x,y,w,h,col)
}

Image.prototype.perlinNoise = function(seed,alpha) {
	Polycode.Image_perlinNoise(this.__ptr, seed,alpha)
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
	Polycode.Image_getPixelsInRect(this.__ptr, x,y,width,height)
}

Image.prototype.getImagePart = function(subRect) {
	Polycode.Image_getImagePart(this.__ptr, subRect)
}

Image.prototype.getBrushX = function() {
	Polycode.Image_getBrushX(this.__ptr)
}

Image.prototype.getBrushY = function() {
	Polycode.Image_getBrushY(this.__ptr)
}

Image.prototype.isLoaded = function() {
	Polycode.Image_isLoaded(this.__ptr)
}

Image.prototype.getType = function() {
	Polycode.Image_getType(this.__ptr)
}

Image.prototype.getWidth = function() {
	Polycode.Image_getWidth(this.__ptr)
}

Image.prototype.getHeight = function() {
	Polycode.Image_getHeight(this.__ptr)
}

Image.prototype.getPixels = function() {
	Polycode.Image_getPixels(this.__ptr)
}

Image.prototype.premultiplyAlpha = function() {
	Polycode.Image_premultiplyAlpha(this.__ptr)
}

Image.prototype.savePNG = function(fileName) {
	Polycode.Image_savePNG(this.__ptr, fileName)
}
