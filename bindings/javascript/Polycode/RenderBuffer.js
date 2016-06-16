function RenderBuffer(width,height,attachDepthBuffer,floatingPoint) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderBuffer(width,height,attachDepthBuffer,floatingPoint)
	}
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
