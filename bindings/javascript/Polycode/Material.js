require('Polycode/Resource')

function Material(name) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Material(name)
	}
	Object.defineProperties(this, {
		'fp16RenderTargets': { enumerable: true, configurable: true, get: Material.prototype.__get_fp16RenderTargets, set: Material.prototype.__set_fp16RenderTargets},
		'blendingMode': { enumerable: true, configurable: true, get: Material.prototype.__get_blendingMode, set: Material.prototype.__set_blendingMode},
		'screenMaterial': { enumerable: true, configurable: true, get: Material.prototype.__get_screenMaterial, set: Material.prototype.__set_screenMaterial}
	})
}

Material.prototype = Object.create(Resource.prototype);

Material.prototype.__get_fp16RenderTargets = function() {
	return Polycode.Material__get_fp16RenderTargets(this.__ptr)
}

Material.prototype.__set_fp16RenderTargets = function(val) {
	Polycode.Material__set_fp16RenderTargets(this.__ptr, val)
}

Material.prototype.__get_blendingMode = function() {
	return Polycode.Material__get_blendingMode(this.__ptr)
}

Material.prototype.__set_blendingMode = function(val) {
	Polycode.Material__set_blendingMode(this.__ptr, val)
}

Material.prototype.__get_screenMaterial = function() {
	return Polycode.Material__get_screenMaterial(this.__ptr)
}

Material.prototype.__set_screenMaterial = function(val) {
	Polycode.Material__set_screenMaterial(this.__ptr, val)
}


Material.prototype.addShaderPass = function(pass) {
	Polycode.Material_addShaderPass(this.__ptr, pass)
}

Material.prototype.addShaderPassAtIndex = function(pass,shaderIndex) {
	Polycode.Material_addShaderPassAtIndex(this.__ptr, pass, shaderIndex)
}

Material.prototype.getNumShaderPasses = function() {
	return Polycode.Material_getNumShaderPasses(this.__ptr)
}

Material.prototype.removeShaderPass = function(shaderIndex) {
	Polycode.Material_removeShaderPass(this.__ptr, shaderIndex)
}

Material.prototype.addShaderRenderTarget = function(newTarget) {
	Polycode.Material_addShaderRenderTarget(this.__ptr, newTarget.__ptr)
}

Material.prototype.getNumShaderRenderTargets = function() {
	return Polycode.Material_getNumShaderRenderTargets(this.__ptr)
}

Material.prototype.getShaderRenderTarget = function(index) {
	var retVal = new ShaderRenderTarget()
	retVal.__ptr = Polycode.Material_getShaderRenderTarget(this.__ptr, index)
	return retVal
}

Material.prototype.removeShaderRenderTarget = function(index) {
	Polycode.Material_removeShaderRenderTarget(this.__ptr, index)
}

Material.prototype.recreateRenderTarget = function(renderTarget) {
	Polycode.Material_recreateRenderTarget(this.__ptr, renderTarget.__ptr)
}

Material.prototype.recreateRenderTargets = function() {
	Polycode.Material_recreateRenderTargets(this.__ptr)
}

Material.prototype.getName = function() {
	return Polycode.Material_getName(this.__ptr)
}

Material.prototype.getShaderPass = function(index) {
	var retVal = new ShaderPass()
	retVal.__ptr = Polycode.Material_getShaderPass(this.__ptr, index)
	return retVal
}

Material.prototype.getShaderBinding = function(index) {
	var retVal = new ShaderBinding()
	retVal.__ptr = Polycode.Material_getShaderBinding(this.__ptr, index)
	return retVal
}

Material.prototype.getShader = function(index) {
	var retVal = new Shader()
	retVal.__ptr = Polycode.Material_getShader(this.__ptr, index)
	return retVal
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
