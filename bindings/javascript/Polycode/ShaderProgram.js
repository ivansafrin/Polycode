function ShaderProgram() {
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: ShaderProgram.prototype.__get_type, set: ShaderProgram.prototype.__set_type}
	})
}
ShaderProgram.prototype.__get_type = function() {
	return Polycode.ShaderProgram__get_type(this.__ptr)
}

ShaderProgram.prototype.__set_type = function(val) {
	Polycode.ShaderProgram__set_type(this.__ptr, val)
}

Duktape.fin(ShaderProgram.prototype, function (x) {
	if (x === ShaderProgram.prototype) {
		return;
	}
	Polycode.ShaderProgram__delete(x.__ptr)
})

ShaderProgram.prototype.reloadProgram = function() {
	Polycode.ShaderProgram_reloadProgram(this.__ptr)
}

ShaderProgram.prototype.reloadResource = function() {
	Polycode.ShaderProgram_reloadResource(this.__ptr)
}
