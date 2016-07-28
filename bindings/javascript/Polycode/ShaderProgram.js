require('Polycode/Resource')

function ShaderProgram(fileName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ShaderProgram(fileName)
	}
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: ShaderProgram.prototype.__get_type, set: ShaderProgram.prototype.__set_type}
	})
}

ShaderProgram.TYPE_VERT = 0
ShaderProgram.TYPE_FRAG = 1

ShaderProgram.prototype = Object.create(Resource.prototype)

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
