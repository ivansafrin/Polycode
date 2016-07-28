function RenderBuffer(width,height,attachDepthBuffer,floatingPoint) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderBuffer(width,height,attachDepthBuffer,floatingPoint)
	}
	Object.defineProperties(this, {
		'platformData': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_platformData, set: RenderBuffer.prototype.__set_platformData},
		'depthBufferPlatformData': { enumerable: true, configurable: true, get: RenderBuffer.prototype.__get_depthBufferPlatformData, set: RenderBuffer.prototype.__set_depthBufferPlatformData}
	})
}


RenderBuffer.prototype.__get_platformData = function() {
	var retVal = new RendererPlatformData("__skip_ptr__")
	retVal.__ptr = 	Polycode.RenderBuffer__get_platformData(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_platformData = function(val) {
	Polycode.RenderBuffer__set_platformData(this.__ptr, val.__ptr)
}

RenderBuffer.prototype.__get_depthBufferPlatformData = function() {
	var retVal = new RendererPlatformData("__skip_ptr__")
	retVal.__ptr = 	Polycode.RenderBuffer__get_depthBufferPlatformData(this.__ptr)
	return retVal
}

RenderBuffer.prototype.__set_depthBufferPlatformData = function(val) {
	Polycode.RenderBuffer__set_depthBufferPlatformData(this.__ptr, val.__ptr)
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
