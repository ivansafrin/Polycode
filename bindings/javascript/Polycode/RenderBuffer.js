function RenderBuffer() {
	Object.defineProperties(this, {
		'colorTexture': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_colorTexture, set: RenderBuffer.prototype.__set_colorTexture},
		'depthTexture': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_depthTexture, set: RenderBuffer.prototype.__set_depthTexture},
		'platformData': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_platformData, set: RenderBuffer.prototype.__set_platformData},
		'depthBufferPlatformData': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_depthBufferPlatformData, set: RenderBuffer.prototype.__set_depthBufferPlatformData}
	})
}
RenderBuffer.prototype.__get_colorTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = 	Polycode.RenderBuffer__get_colorTexture(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_colorTexture = function(val) {
	Polycode.RenderBuffer__set_colorTexture(this.__ptr, val.__ptr)
}

RenderBuffer.prototype.__get_depthTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = 	Polycode.RenderBuffer__get_depthTexture(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_depthTexture = function(val) {
	Polycode.RenderBuffer__set_depthTexture(this.__ptr, val.__ptr)
}

RenderBuffer.prototype.__get_platformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.RenderBuffer__get_platformData(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_platformData = function(val) {
	Polycode.RenderBuffer__set_platformData(this.__ptr, val.__ptr)
}

RenderBuffer.prototype.__get_depthBufferPlatformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.RenderBuffer__get_depthBufferPlatformData(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_depthBufferPlatformData = function(val) {
	Polycode.RenderBuffer__set_depthBufferPlatformData(this.__ptr, val.__ptr)
}


RenderBuffer.prototype.getWidth = function() {
	return Polycode.RenderBuffer_getWidth(this.__ptr)
}

RenderBuffer.prototype.getHeight = function() {
	return Polycode.RenderBuffer_getHeight(this.__ptr)
}
