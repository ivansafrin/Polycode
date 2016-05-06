function Material() {
}

Material.prototype.addShaderPass = function(pass) {
	Polycode.Material_addShaderPass(this.__ptr, pass)
}

Material.prototype.addShaderPassAtIndex = function(pass,shaderIndex) {
	Polycode.Material_addShaderPassAtIndex(this.__ptr, pass,shaderIndex)
}

Material.prototype.addShader = function(shader,shaderBinding) {
	Polycode.Material_addShader(this.__ptr, shader,shaderBinding)
}

Material.prototype.addShaderAtIndex = function(shader,shaderBinding,shaderIndex) {
	Polycode.Material_addShaderAtIndex(this.__ptr, shader,shaderBinding,shaderIndex)
}

Material.prototype.getNumShaderPasses = function() {
	Polycode.Material_getNumShaderPasses(this.__ptr)
}

Material.prototype.removeShaderPass = function(shaderIndex) {
	Polycode.Material_removeShaderPass(this.__ptr, shaderIndex)
}

Material.prototype.recreateExpectedShaderParams = function() {
	Polycode.Material_recreateExpectedShaderParams(this.__ptr)
}

Material.prototype.addShaderRenderTarget = function(newTarget) {
	Polycode.Material_addShaderRenderTarget(this.__ptr, newTarget)
}

Material.prototype.getNumShaderRenderTargets = function() {
	Polycode.Material_getNumShaderRenderTargets(this.__ptr)
}

Material.prototype.getShaderRenderTarget = function(index) {
	Polycode.Material_getShaderRenderTarget(this.__ptr, index)
}

Material.prototype.removeShaderRenderTarget = function(index) {
	Polycode.Material_removeShaderRenderTarget(this.__ptr, index)
}

Material.prototype.recreateRenderTarget = function(renderTarget) {
	Polycode.Material_recreateRenderTarget(this.__ptr, renderTarget)
}

Material.prototype.recreateRenderTargets = function() {
	Polycode.Material_recreateRenderTargets(this.__ptr)
}

Material.prototype.getName = function() {
	Polycode.Material_getName(this.__ptr)
}

Material.prototype.getShaderPass = function(index) {
	Polycode.Material_getShaderPass(this.__ptr, index)
}

Material.prototype.getShaderBinding = function(index) {
	Polycode.Material_getShaderBinding(this.__ptr, index)
}

Material.prototype.getShader = function(index) {
	Polycode.Material_getShader(this.__ptr, index)
}

Material.prototype.loadMaterial = function(fileName) {
	Polycode.Material_loadMaterial(this.__ptr, fileName)
}

Material.prototype.setName = function(name) {
	Polycode.Material_setName(this.__ptr, name)
}

Material.prototype.clearShaders = function() {
	Polycode.Material_clearShaders(this.__ptr)
}
