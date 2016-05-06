function RenderBuffer() {
}

RenderBuffer.prototype.getWidth = function() {
	Polycode.RenderBuffer_getWidth(this.__ptr)
}

RenderBuffer.prototype.getHeight = function() {
	Polycode.RenderBuffer_getHeight(this.__ptr)
}
