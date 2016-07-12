function ShaderPass() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ShaderPass()
	}
	Object.defineProperties(this, {
		'wireframe': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_wireframe, set: ShaderPass.prototype.__set_wireframe},
		'blendingMode': { enumerable: true, configurable: true, get: ShaderPass.prototype.__get_blendingMode, set: ShaderPass.prototype.__set_blendingMode}
	})
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

Duktape.fin(ShaderPass.prototype, function (x) {
	if (x === ShaderPass.prototype) {
		return;
	}
	Polycode.ShaderPass__delete(x.__ptr)
})

ShaderPass.prototype.getShaderBinding = function() {
	var retVal = new ShaderBinding("__skip_ptr__")
	retVal.__ptr = Polycode.ShaderPass_getShaderBinding(this.__ptr)
	return retVal
}
