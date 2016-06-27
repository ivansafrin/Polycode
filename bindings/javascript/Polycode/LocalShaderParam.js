function LocalShaderParam() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.LocalShaderParam()
	}
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_name, set: LocalShaderParam.prototype.__set_name},
		'type': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_type, set: LocalShaderParam.prototype.__set_type},
		'ownsPointer': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_ownsPointer, set: LocalShaderParam.prototype.__set_ownsPointer},
		'arraySize': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_arraySize, set: LocalShaderParam.prototype.__set_arraySize},
		'param': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_param, set: LocalShaderParam.prototype.__set_param},
		'accessMutex': { enumerable: true, configurable: true, get: LocalShaderParam.prototype.__get_accessMutex, set: LocalShaderParam.prototype.__set_accessMutex}
	})
}

LocalShaderParam.prototype.__get_name = function() {
	return Polycode.LocalShaderParam__get_name(this.__ptr)
}

LocalShaderParam.prototype.__set_name = function(val) {
	Polycode.LocalShaderParam__set_name(this.__ptr, val)
}

LocalShaderParam.prototype.__get_type = function() {
	return Polycode.LocalShaderParam__get_type(this.__ptr)
}

LocalShaderParam.prototype.__set_type = function(val) {
	Polycode.LocalShaderParam__set_type(this.__ptr, val)
}

LocalShaderParam.prototype.__get_ownsPointer = function() {
	return Polycode.LocalShaderParam__get_ownsPointer(this.__ptr)
}

LocalShaderParam.prototype.__set_ownsPointer = function(val) {
	Polycode.LocalShaderParam__set_ownsPointer(this.__ptr, val)
}

LocalShaderParam.prototype.__get_arraySize = function() {
	return Polycode.LocalShaderParam__get_arraySize(this.__ptr)
}

LocalShaderParam.prototype.__set_arraySize = function(val) {
	Polycode.LocalShaderParam__set_arraySize(this.__ptr, val)
}

LocalShaderParam.prototype.__get_param = function() {
	var retVal = new ProgramParam()
	retVal.__ptr = 	Polycode.LocalShaderParam__get_param(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.__set_param = function(val) {
	Polycode.LocalShaderParam__set_param(this.__ptr, val.__ptr)
}

LocalShaderParam.prototype.__get_accessMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = 	Polycode.LocalShaderParam__get_accessMutex(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.__set_accessMutex = function(val) {
	Polycode.LocalShaderParam__set_accessMutex(this.__ptr, val.__ptr)
}

Duktape.fin(LocalShaderParam.prototype, function (x) {
	if (x === LocalShaderParam.prototype) {
		return;
	}
	Polycode.LocalShaderParam__delete(x.__ptr)
})

LocalShaderParam.prototype.Copy = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.LocalShaderParam_Copy(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.getNumber = function() {
	return Polycode.LocalShaderParam_getNumber(this.__ptr)
}

LocalShaderParam.prototype.getVector2 = function() {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.LocalShaderParam_getVector2(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.getVector3 = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.LocalShaderParam_getVector3(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.getMatrix4 = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.LocalShaderParam_getMatrix4(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.getColor = function() {
	var retVal = new Color()
	retVal.__ptr = Polycode.LocalShaderParam_getColor(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.setNumber = function(x) {
	Polycode.LocalShaderParam_setNumber(this.__ptr, x)
}

LocalShaderParam.prototype.setVector2 = function(x) {
	Polycode.LocalShaderParam_setVector2(this.__ptr, x)
}

LocalShaderParam.prototype.setVector3 = function(x) {
	Polycode.LocalShaderParam_setVector3(this.__ptr, x)
}

LocalShaderParam.prototype.setMatrix4 = function(x) {
	Polycode.LocalShaderParam_setMatrix4(this.__ptr, x)
}

LocalShaderParam.prototype.setMatrix4Array = function(x) {
	Polycode.LocalShaderParam_setMatrix4Array(this.__ptr, x)
}

LocalShaderParam.prototype.setColor = function(x) {
	Polycode.LocalShaderParam_setColor(this.__ptr, x)
}

LocalShaderParam.prototype.setTexture = function(texture) {
	Polycode.LocalShaderParam_setTexture(this.__ptr, texture)
}

LocalShaderParam.prototype.getTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = Polycode.LocalShaderParam_getTexture(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.setCubemap = function(cubemap) {
	Polycode.LocalShaderParam_setCubemap(this.__ptr, cubemap)
}

LocalShaderParam.prototype.getCubemap = function() {
	var retVal = new Cubemap()
	retVal.__ptr = Polycode.LocalShaderParam_getCubemap(this.__ptr)
	return retVal
}

LocalShaderParam.prototype.setParamValueFromString = function(type,pvalue) {
	Polycode.LocalShaderParam_setParamValueFromString(this.__ptr, type, pvalue)
}
