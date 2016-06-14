function Renderer() {
}
Duktape.fin(Renderer.prototype, function (x) {
	if (x === Renderer.prototype) {
		return;
	}
	Polycode.Renderer__delete(x.__ptr)
})

Renderer.prototype.setGraphicsInterface = function(core,graphicsInterface) {
	Polycode.Renderer_setGraphicsInterface(this.__ptr, core,graphicsInterface)
}

Renderer.prototype.getRenderThread = function() {
	var retVal = new RenderThread()
	retVal.__ptr = Polycode.Renderer_getRenderThread(this.__ptr)
	return retVal
}

Renderer.prototype.processDrawBuffer = function(buffer) {
	Polycode.Renderer_processDrawBuffer(this.__ptr, buffer)
}

Renderer.prototype.setBackingResolutionScale = function(xScale,yScale) {
	Polycode.Renderer_setBackingResolutionScale(this.__ptr, xScale,yScale)
}

Renderer.prototype.getBackingResolutionScaleX = function() {
	return Polycode.Renderer_getBackingResolutionScaleX(this.__ptr)
}

Renderer.prototype.getBackingResolutionScaleY = function() {
	return Polycode.Renderer_getBackingResolutionScaleY(this.__ptr)
}

Renderer.prototype.enqueueFrameJob = function(jobType,data) {
	Polycode.Renderer_enqueueFrameJob(this.__ptr, jobType,data)
}

Renderer.prototype.destroyRenderBufferPlatformData = function(platformData) {
	Polycode.Renderer_destroyRenderBufferPlatformData(this.__ptr, platformData)
}

Renderer.prototype.destroyTexturePlatformData = function(platformData) {
	Polycode.Renderer_destroyTexturePlatformData(this.__ptr, platformData)
}

Renderer.prototype.destroyProgramPlatformData = function(platformData) {
	Polycode.Renderer_destroyProgramPlatformData(this.__ptr, platformData)
}

Renderer.prototype.destroyShaderPlatformData = function(platformData) {
	Polycode.Renderer_destroyShaderPlatformData(this.__ptr, platformData)
}

Renderer.prototype.destroySubmeshPlatformData = function(platformData) {
	Polycode.Renderer_destroySubmeshPlatformData(this.__ptr, platformData)
}

Renderer.prototype.setTextureParam = function(param,texture) {
	Polycode.Renderer_setTextureParam(this.__ptr, param,texture)
}

Renderer.prototype.setAnisotropyAmount = function(amount) {
	Polycode.Renderer_setAnisotropyAmount(this.__ptr, amount)
}

Renderer.prototype.getAnisotropyAmount = function() {
	return Polycode.Renderer_getAnisotropyAmount(this.__ptr)
}

Renderer.prototype.beginFrame = function() {
	Polycode.Renderer_beginFrame(this.__ptr)
}

Renderer.prototype.endFrame = function() {
	Polycode.Renderer_endFrame(this.__ptr)
}
