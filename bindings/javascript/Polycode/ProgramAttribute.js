function ProgramAttribute() {
	Object.defineProperties(this, {
		'size': { enumerable: true, configurable: true, get: ProgramAttribute.prototype.__get_size, set: ProgramAttribute.prototype.__set_size},
		'name': { enumerable: true, configurable: true, get: ProgramAttribute.prototype.__get_name, set: ProgramAttribute.prototype.__set_name},
		'platformData': { enumerable: true, configurable: true, get: ProgramAttribute.prototype.__get_platformData, set: ProgramAttribute.prototype.__set_platformData}
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

ProgramAttribute.prototype.__get_platformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.ProgramAttribute__get_platformData(this.__ptr)
	return retVal
}

ProgramAttribute.prototype.__set_platformData = function(val) {
	Polycode.ProgramAttribute__set_platformData(this.__ptr, val.__ptr)
}

