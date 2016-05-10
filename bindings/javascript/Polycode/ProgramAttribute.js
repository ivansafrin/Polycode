function ProgramAttribute() {
	Object.defineProperties(this, {
		'size': { enumerable: true, configurable: true, get: ProgramAttribute.prototype.__get_size, set: ProgramAttribute.prototype.__set_size},
		'name': { enumerable: true, configurable: true, get: ProgramAttribute.prototype.__get_name, set: ProgramAttribute.prototype.__set_name}
	})
}
ProgramAttribute.prototype.__get_size = function() {
	return Polycode.ProgramAttribute__get_size(this.__ptr)
}

ProgramAttribute.prototype.__set_size = function(val) {
	Polycode.ProgramAttribute__set_size(this.__ptr, val)
}

ProgramAttribute.prototype.__get_name = function() {
	return Polycode.ProgramAttribute__get_name(this.__ptr)
}

ProgramAttribute.prototype.__set_name = function(val) {
	Polycode.ProgramAttribute__set_name(this.__ptr, val)
}

Duktape.fin(ProgramAttribute.prototype, function (x) {
	if (x === ProgramAttribute.prototype) {
		return;
	}
	Polycode.ProgramAttribute__delete(x.__ptr)
})
