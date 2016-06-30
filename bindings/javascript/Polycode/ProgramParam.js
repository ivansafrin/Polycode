function ProgramParam() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ProgramParam()
	}
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_name, set: ProgramParam.prototype.__set_name},
		'type': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_type, set: ProgramParam.prototype.__set_type},
		'globalParam': { enumerable: true, configurable: true, get: ProgramParam.prototype.__get_globalParam, set: ProgramParam.prototype.__set_globalParam}
	})
}

ProgramParam.PARAM_UNKNOWN = 0
ProgramParam.PARAM_NUMBER = 1
ProgramParam.PARAM_VECTOR2 = 2
ProgramParam.PARAM_VECTOR3 = 3
ProgramParam.PARAM_COLOR = 4
ProgramParam.PARAM_MATRIX = 5
ProgramParam.PARAM_TEXTURE = 6
ProgramParam.PARAM_CUBEMAP = 7

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

ProgramParam.prototype.__get_globalParam = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.ProgramParam__get_globalParam(this.__ptr)
	return retVal
}

ProgramParam.prototype.__set_globalParam = function(val) {
	Polycode.ProgramParam__set_globalParam(this.__ptr, val.__ptr)
}

Duktape.fin(ProgramParam.prototype, function (x) {
	if (x === ProgramParam.prototype) {
		return;
	}
	Polycode.ProgramParam__delete(x.__ptr)
})

ProgramParam.prototype.createParamData = function(type) {
	Polycode.ProgramParam_createParamData(type)
}
