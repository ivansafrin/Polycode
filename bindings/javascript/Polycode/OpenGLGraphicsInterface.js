function OpenGLGraphicsInterface() {
}

OpenGLGraphicsInterface.prototype.createTexture = function(texture) {
	Polycode.OpenGLGraphicsInterface_createTexture(this.__ptr, texture)
}

OpenGLGraphicsInterface.prototype.destroyTexture = function(texture) {
	Polycode.OpenGLGraphicsInterface_destroyTexture(this.__ptr, texture)
}

OpenGLGraphicsInterface.prototype.setViewport = function(x,y,width,height) {
	Polycode.OpenGLGraphicsInterface_setViewport(this.__ptr, x,y,width,height)
}

OpenGLGraphicsInterface.prototype.clearBuffers = function(clearColor,colorBuffer,depthBuffer,stencilBuffer) {
	Polycode.OpenGLGraphicsInterface_clearBuffers(this.__ptr, clearColor,colorBuffer,depthBuffer,stencilBuffer)
}

OpenGLGraphicsInterface.prototype.setParamInShader = function(shader,param,localParam) {
	Polycode.OpenGLGraphicsInterface_setParamInShader(this.__ptr, shader,param,localParam)
}

OpenGLGraphicsInterface.prototype.setAttributeInShader = function(shader,attribute,attributeBinding) {
	Polycode.OpenGLGraphicsInterface_setAttributeInShader(this.__ptr, shader,attribute,attributeBinding)
}

OpenGLGraphicsInterface.prototype.disableAttribute = function(shader,attribute) {
	Polycode.OpenGLGraphicsInterface_disableAttribute(this.__ptr, shader,attribute)
}

OpenGLGraphicsInterface.prototype.useShader = function(shader) {
	Polycode.OpenGLGraphicsInterface_useShader(this.__ptr, shader)
}

OpenGLGraphicsInterface.prototype.createProgram = function(program) {
	Polycode.OpenGLGraphicsInterface_createProgram(this.__ptr, program)
}

OpenGLGraphicsInterface.prototype.destroyProgram = function(program) {
	Polycode.OpenGLGraphicsInterface_destroyProgram(this.__ptr, program)
}

OpenGLGraphicsInterface.prototype.createVBOForVertexArray = function(array) {
	Polycode.OpenGLGraphicsInterface_createVBOForVertexArray(this.__ptr, array)
}

OpenGLGraphicsInterface.prototype.createMesh = function(mesh) {
	Polycode.OpenGLGraphicsInterface_createMesh(this.__ptr, mesh)
}

OpenGLGraphicsInterface.prototype.destroyMesh = function(mesh) {
	Polycode.OpenGLGraphicsInterface_destroyMesh(this.__ptr, mesh)
}

OpenGLGraphicsInterface.prototype.createShader = function(shader) {
	Polycode.OpenGLGraphicsInterface_createShader(this.__ptr, shader)
}

OpenGLGraphicsInterface.prototype.destroyShader = function(shader) {
	Polycode.OpenGLGraphicsInterface_destroyShader(this.__ptr, shader)
}

OpenGLGraphicsInterface.prototype.beginDrawCall = function() {
	Polycode.OpenGLGraphicsInterface_beginDrawCall(this.__ptr)
}

OpenGLGraphicsInterface.prototype.endDrawCall = function() {
	Polycode.OpenGLGraphicsInterface_endDrawCall(this.__ptr)
}

OpenGLGraphicsInterface.prototype.setBlendingMode = function(blendingMode) {
	Polycode.OpenGLGraphicsInterface_setBlendingMode(this.__ptr, blendingMode)
}

OpenGLGraphicsInterface.prototype.createRenderBuffer = function(renderBuffer) {
	Polycode.OpenGLGraphicsInterface_createRenderBuffer(this.__ptr, renderBuffer)
}

OpenGLGraphicsInterface.prototype.destroyRenderBuffer = function(renderBuffer) {
	Polycode.OpenGLGraphicsInterface_destroyRenderBuffer(this.__ptr, renderBuffer)
}

OpenGLGraphicsInterface.prototype.bindRenderBuffer = function(renderBuffer) {
	Polycode.OpenGLGraphicsInterface_bindRenderBuffer(this.__ptr, renderBuffer)
}

OpenGLGraphicsInterface.prototype.createVertexBuffer = function(dataArray) {
	Polycode.OpenGLGraphicsInterface_createVertexBuffer(this.__ptr, dataArray)
}

OpenGLGraphicsInterface.prototype.createIndexBuffer = function(dataArray) {
	Polycode.OpenGLGraphicsInterface_createIndexBuffer(this.__ptr, dataArray)
}

OpenGLGraphicsInterface.prototype.destroyBuffer = function(array) {
	Polycode.OpenGLGraphicsInterface_destroyBuffer(this.__ptr, array)
}

OpenGLGraphicsInterface.prototype.drawIndices = function(type,indexArray) {
	Polycode.OpenGLGraphicsInterface_drawIndices(this.__ptr, type,indexArray)
}

OpenGLGraphicsInterface.prototype.drawArrays = function(type,vertexCount) {
	Polycode.OpenGLGraphicsInterface_drawArrays(this.__ptr, type,vertexCount)
}

OpenGLGraphicsInterface.prototype.enableDepthTest = function(val) {
	Polycode.OpenGLGraphicsInterface_enableDepthTest(this.__ptr, val)
}

OpenGLGraphicsInterface.prototype.enableDepthWrite = function(val) {
	Polycode.OpenGLGraphicsInterface_enableDepthWrite(this.__ptr, val)
}

OpenGLGraphicsInterface.prototype.enableBackfaceCulling = function(val) {
	Polycode.OpenGLGraphicsInterface_enableBackfaceCulling(this.__ptr, val)
}

OpenGLGraphicsInterface.prototype.setLineSize = function(lineSize) {
	Polycode.OpenGLGraphicsInterface_setLineSize(this.__ptr, lineSize)
}

OpenGLGraphicsInterface.prototype.setWireframeMode = function(val) {
	Polycode.OpenGLGraphicsInterface_setWireframeMode(this.__ptr, val)
}

OpenGLGraphicsInterface.prototype.enableScissor = function(val) {
	Polycode.OpenGLGraphicsInterface_enableScissor(this.__ptr, val)
}

OpenGLGraphicsInterface.prototype.setScissorBox = function(box) {
	Polycode.OpenGLGraphicsInterface_setScissorBox(this.__ptr, box)
}
