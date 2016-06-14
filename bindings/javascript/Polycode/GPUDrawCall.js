function GPUDrawCall() {
	Object.defineProperties(this, {
		'options': { enumerable: true, configurable: true, get: GPUDrawCall.prototype.__get_options, set: GPUDrawCall.prototype.__set_options},
		'modelMatrix': { enumerable: true, configurable: true, get: GPUDrawCall.prototype.__get_modelMatrix, set: GPUDrawCall.prototype.__set_modelMatrix}
	})
}
GPUDrawCall.prototype.__get_options = function() {
	var retVal = new GPUDrawOptions()
	retVal.__ptr = 	Polycode.GPUDrawCall__get_options(this.__ptr)
	return retVal
}

GPUDrawCall.prototype.__set_options = function(val) {
	Polycode.GPUDrawCall__set_options(this.__ptr, val.__ptr)
}

GPUDrawCall.prototype.__get_modelMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.GPUDrawCall__get_modelMatrix(this.__ptr)
	return retVal
}

GPUDrawCall.prototype.__set_modelMatrix = function(val) {
	Polycode.GPUDrawCall__set_modelMatrix(this.__ptr, val.__ptr)
}

Duktape.fin(GPUDrawCall.prototype, function (x) {
	if (x === GPUDrawCall.prototype) {
		return;
	}
	Polycode.GPUDrawCall__delete(x.__ptr)
})
