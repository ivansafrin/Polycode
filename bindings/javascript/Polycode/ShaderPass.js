function ShaderPass() {
	Object.defineProperties(this, {
		'shader': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_shader, set: ShaderPass.prototype.__set_shader},
		'wireframe': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_wireframe, set: ShaderPass.prototype.__set_wireframe},
		'blendingMode': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_blendingMode, set: ShaderPass.prototype.__set_blendingMode},
		'shaderBinding': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_shaderBinding, set: ShaderPass.prototype.__set_shaderBinding},
		'materialShaderBinding': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_materialShaderBinding, set: ShaderPass.prototype.__set_materialShaderBinding}
	})
}
ShaderPass.prototype.__get_shader = function() {
	var retVal = new Shader()
	retVal.__ptr = 	Polycode.ShaderPass__get_shader(this.__ptr)
	return retVal
}

ShaderPass.prototype.__set_shader = function(val) {
	Polycode.ShaderPass__set_shader(this.__ptr, val.__ptr)
}

ShaderPass.prototype.__get_wireframe = function() {
	return Polycode.ShaderPass__get_wireframe(this.__ptr)
}

ShaderPass.prototype.__set_wireframe = function(val) {
	Polycode.ShaderPass__set_wireframe(this.__ptr, val)
}

ShaderPass.prototype.__get_blendingMode = function() {
	return Polycode.ShaderPass__get_blendingMode(this.__ptr)
}

ShaderPass.prototype.__set_blendingMode = function(val) {
	Polycode.ShaderPass__set_blendingMode(this.__ptr, val)
}

ShaderPass.prototype.__get_shaderBinding = function() {
	var retVal = new ShaderBinding()
	retVal.__ptr = 	Polycode.ShaderPass__get_shaderBinding(this.__ptr)
	return retVal
}

ShaderPass.prototype.__set_shaderBinding = function(val) {
	Polycode.ShaderPass__set_shaderBinding(this.__ptr, val.__ptr)
}

ShaderPass.prototype.__get_materialShaderBinding = function() {
	var retVal = new ShaderBinding()
	retVal.__ptr = 	Polycode.ShaderPass__get_materialShaderBinding(this.__ptr)
	return retVal
}

ShaderPass.prototype.__set_materialShaderBinding = function(val) {
	Polycode.ShaderPass__set_materialShaderBinding(this.__ptr, val.__ptr)
}


ShaderPass.prototype.setAttributeArraysFromMesh = function(mesh) {
	Polycode.ShaderPass_setAttributeArraysFromMesh(this.__ptr, mesh)
}

ShaderPass.prototype.setExpectedAttributes = function() {
	Polycode.ShaderPass_setExpectedAttributes(this.__ptr)
}
