function Renderer() {
}

Renderer.BLEND_MODE_NONE = 0
Renderer.BLEND_MODE_NORMAL = 1
Renderer.BLEND_MODE_LIGHTEN = 2
Renderer.BLEND_MODE_COLOR = 3
Renderer.BLEND_MODE_PREMULTIPLIED = 4
Renderer.BLEND_MODE_MULTIPLY = 5
Renderer.BLEND_MODE_MATERIAL = 6
Renderer.DEPTH_FUNCTION_GREATER = 0
Renderer.DEPTH_FUNCTION_LEQUAL = 1

Duktape.fin(Renderer.prototype, function (x) {
	if (x === Renderer.prototype) {
		return;
	}
	Polycode.Renderer__delete(x.__ptr)
})

Renderer.prototype.setGraphicsInterface = function(core,graphicsInterface) {
	Polycode.Renderer_setGraphicsInterface(this.__ptr, core.__ptr, graphicsInterface.__ptr)
}

Renderer.prototype.getRenderThread = function() {
	var retVal = new RenderThread()
	retVal.__ptr = Polycode.Renderer_getRenderThread(this.__ptr)
	return retVal
}

Renderer.prototype.processDrawBuffer = function(buffer) {
	Polycode.Renderer_processDrawBuffer(this.__ptr, buffer.__ptr)
}

Renderer.prototype.setBackingResolutionScale = function(xScale,yScale) {
	Polycode.Renderer_setBackingResolutionScale(this.__ptr, xScale, yScale)
}

Renderer.prototype.getBackingResolutionScaleX = function() {
	return Polycode.Renderer_getBackingResolutionScaleX(this.__ptr)
}

Renderer.prototype.getBackingResolutionScaleY = function() {
	return Polycode.Renderer_getBackingResolutionScaleY(this.__ptr)
}

Renderer.prototype.enqueueFrameJob = function(jobType,data) {
	Polycode.Renderer_enqueueFrameJob(this.__ptr, jobType, data.__ptr)
}

Renderer.prototype.destroyRenderBufferPlatformData = function(platformData) {
	Polycode.Renderer_destroyRenderBufferPlatformData(this.__ptr, platformData.__ptr)
}

Renderer.prototype.destroyTexturePlatformData = function(platformData) {
	Polycode.Renderer_destroyTexturePlatformData(this.__ptr, platformData.__ptr)
}

Renderer.prototype.destroyProgramPlatformData = function(platformData) {
	Polycode.Renderer_destroyProgramPlatformData(this.__ptr, platformData.__ptr)
}

Renderer.prototype.destroyShaderPlatformData = function(platformData) {
	Polycode.Renderer_destroyShaderPlatformData(this.__ptr, platformData.__ptr)
}

Renderer.prototype.destroySubmeshPlatformData = function(platformData) {
	Polycode.Renderer_destroySubmeshPlatformData(this.__ptr, platformData.__ptr)
}

Renderer.prototype.setTextureParam = function(param,texture) {
	Polycode.Renderer_setTextureParam(this.__ptr, param.__ptr, texture.__ptr)
}

Renderer.prototype.setAnisotropyAmount = function(amount) {
	Polycode.Renderer_setAnisotropyAmount(this.__ptr, amount)
}

Renderer.prototype.getAnisotropyAmount = function() {
	return Polycode.Renderer_getAnisotropyAmount(this.__ptr)
}

Renderer.prototype.unProject = function(position,modelMatrix,projectionMatrix,viewport) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Renderer_unProject(position, modelMatrix, projectionMatrix, viewport)
	return retVal
}

Renderer.prototype.project = function(position,modelMatrix,projectionMatrix,viewport) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Renderer_project(position, modelMatrix, projectionMatrix, viewport)
	return retVal
}

Renderer.prototype.beginFrame = function() {
	Polycode.Renderer_beginFrame(this.__ptr)
}

Renderer.prototype.endFrame = function() {
	Polycode.Renderer_endFrame(this.__ptr)
}
