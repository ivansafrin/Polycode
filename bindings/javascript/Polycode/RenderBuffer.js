function RenderBuffer() {
	Object.defineProperties(this, {
		'colorTexture': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_colorTexture, set: RenderBuffer.prototype.__set_colorTexture},
		'depthTexture': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_depthTexture, set: RenderBuffer.prototype.__set_depthTexture}
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

Duktape.fin(RenderBuffer.prototype, function (x) {
	if (x === RenderBuffer.prototype) {
		return;
	}
	Polycode.RenderBuffer__delete(x.__ptr)
})

RenderBuffer.prototype.getWidth = function() {
	return Polycode.RenderBuffer_getWidth(this.__ptr)
}

RenderBuffer.prototype.getHeight = function() {
	return Polycode.RenderBuffer_getHeight(this.__ptr)
}
