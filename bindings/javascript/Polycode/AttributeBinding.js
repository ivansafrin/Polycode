function AttributeBinding() {
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_name, set: AttributeBinding.prototype.__set_name},
		'vertexData': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_vertexData, set: AttributeBinding.prototype.__set_vertexData},
		'attribute': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_attribute, set: AttributeBinding.prototype.__set_attribute},
		'enabled': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_enabled, set: AttributeBinding.prototype.__set_enabled}
	})
}
AttributeBinding.prototype.__get_name = function() {
	return Polycode.AttributeBinding__get_name(this.__ptr)
}

AttributeBinding.prototype.__set_name = function(val) {
	Polycode.AttributeBinding__set_name(this.__ptr, val)
}

AttributeBinding.prototype.__get_vertexData = function() {
	var retVal = new VertexDataArray()
	retVal.__ptr = 	Polycode.AttributeBinding__get_vertexData(this.__ptr)
	return retVal
}

AttributeBinding.prototype.__set_vertexData = function(val) {
	Polycode.AttributeBinding__set_vertexData(this.__ptr, val.__ptr)
}

AttributeBinding.prototype.__get_attribute = function() {
	var retVal = new ProgramAttribute()
	retVal.__ptr = 	Polycode.AttributeBinding__get_attribute(this.__ptr)
	return retVal
}

AttributeBinding.prototype.__set_attribute = function(val) {
	Polycode.AttributeBinding__set_attribute(this.__ptr, val.__ptr)
}

AttributeBinding.prototype.__get_enabled = function() {
	return Polycode.AttributeBinding__get_enabled(this.__ptr)
}

AttributeBinding.prototype.__set_enabled = function(val) {
	Polycode.AttributeBinding__set_enabled(this.__ptr, val)
}

Duktape.fin(AttributeBinding.prototype, function (x) {
	if (x === AttributeBinding.prototype) {
		return;
	}
	Polycode.AttributeBinding__delete(x.__ptr)
})
