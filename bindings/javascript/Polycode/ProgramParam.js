function ProgramParam() {
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_name, set: ProgramParam.prototype.__set_name},
		'type': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_type, set: ProgramParam.prototype.__set_type},
		'platformData': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_platformData, set: ProgramParam.prototype.__set_platformData},
		'globalParam': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_globalParam, set: ProgramParam.prototype.__set_globalParam}
	})
}
ProgramParam.prototype.__get_name = function() {
	return Polycode.ProgramParam__get_name(this.__ptr)
}

ProgramParam.prototype.__set_name = function(val) {
	Polycode.ProgramParam__set_name(this.__ptr, val)
}

ProgramParam.prototype.__get_type = function() {
	return Polycode.ProgramParam__get_type(this.__ptr)
}

ProgramParam.prototype.__set_type = function(val) {
	Polycode.ProgramParam__set_type(this.__ptr, val)
}

ProgramParam.prototype.__get_platformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.ProgramParam__get_platformData(this.__ptr)
	return retVal
}

ProgramParam.prototype.__set_platformData = function(val) {
	Polycode.ProgramParam__set_platformData(this.__ptr, val.__ptr)
}

ProgramParam.prototype.__get_globalParam = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.ProgramParam__get_globalParam(this.__ptr)
	return retVal
}

ProgramParam.prototype.__set_globalParam = function(val) {
	Polycode.ProgramParam__set_globalParam(this.__ptr, val.__ptr)
}

