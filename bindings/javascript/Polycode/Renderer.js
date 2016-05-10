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

Renderer.prototype.createCubemap = function(t0,t1,t2,t3,t4,t5) {
	var retVal = new Cubemap()
	retVal.__ptr = Polycode.Renderer_createCubemap(this.__ptr, t0,t1,t2,t3,t4,t5)
	return retVal
}

Renderer.prototype.createTexture = function(width,height,textureData,clamp,createMipmaps,type,filteringMode,anisotropy,framebufferTexture) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.Renderer_createTexture(this.__ptr, width,height,textureData,clamp,createMipmaps,type,filteringMode,anisotropy,framebufferTexture)
	return retVal
}

Renderer.prototype.createRenderBuffer = function(width,height,attachDepthBuffer,floatingPoint) {
	var retVal = new RenderBuffer()
	retVal.__ptr = Polycode.Renderer_createRenderBuffer(this.__ptr, width,height,attachDepthBuffer,floatingPoint)
	return retVal
}

Renderer.prototype.destroyRenderBuffer = function(buffer) {
	Polycode.Renderer_destroyRenderBuffer(this.__ptr, buffer)
}

Renderer.prototype.destroyTexture = function(texture) {
	Polycode.Renderer_destroyTexture(this.__ptr, texture)
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

Renderer.prototype.createProgram = function(fileName) {
	var retVal = new ShaderProgram()
	retVal.__ptr = Polycode.Renderer_createProgram(this.__ptr, fileName)
	return retVal
}

Renderer.prototype.createShader = function(vertexProgram,fragmentProgram) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.Renderer_createShader(this.__ptr, vertexProgram,fragmentProgram)
	return retVal
}

Renderer.prototype.createVertexBuffers = function(mesh) {
	Polycode.Renderer_createVertexBuffers(this.__ptr, mesh)
}

Renderer.prototype.enqueueFrameJob = function(jobType,data) {
	Polycode.Renderer_enqueueFrameJob(this.__ptr, jobType,data)
}

Renderer.prototype.destroyProgram = function(program) {
	Polycode.Renderer_destroyProgram(this.__ptr, program)
}

Renderer.prototype.destroyShader = function(shader) {
	Polycode.Renderer_destroyShader(this.__ptr, shader)
}

Renderer.prototype.destroyBuffer = function(array) {
	Polycode.Renderer_destroyBuffer(this.__ptr, array)
}

Renderer.prototype.destroyShaderBinding = function(binding) {
	Polycode.Renderer_destroyShaderBinding(this.__ptr, binding)
}

Renderer.prototype.destroyShaderParam = function(param) {
	Polycode.Renderer_destroyShaderParam(this.__ptr, param)
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

Renderer.prototype.createMesh = function(fileName) {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.Renderer_createMesh(this.__ptr, fileName)
	return retVal
}

Renderer.prototype.destroyMesh = function(mesh) {
	Polycode.Renderer_destroyMesh(this.__ptr, mesh)
}

Renderer.prototype.beginFrame = function() {
	Polycode.Renderer_beginFrame(this.__ptr)
}

Renderer.prototype.endFrame = function() {
	Polycode.Renderer_endFrame(this.__ptr)
}
