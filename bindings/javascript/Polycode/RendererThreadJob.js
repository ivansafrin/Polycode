function RendererThreadJob() {
	Object.defineProperties(this, {
		'jobType': { enumerable: true, configurable: true, get: RendererThreadJob.prototype.__get_jobType, set: RendererThreadJob.prototype.__set_jobType},
		'data': { enumerable: true, configurable: true, get: RendererThreadJob.prototype.__get_data, set: RendererThreadJob.prototype.__set_data},
		'data2': { enumerable: true, configurable: true, get: RendererThreadJob.prototype.__get_data2, set: RendererThreadJob.prototype.__set_data2}
	})
}
RendererThreadJob.prototype.__get_jobType = function() {
	return Polycode.RendererThreadJob__get_jobType(this.__ptr)
}

RendererThreadJob.prototype.__set_jobType = function(val) {
	Polycode.RendererThreadJob__set_jobType(this.__ptr, val)
}

RendererThreadJob.prototype.__get_data = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.RendererThreadJob__get_data(this.__ptr)
	return retVal
}

RendererThreadJob.prototype.__set_data = function(val) {
	Polycode.RendererThreadJob__set_data(this.__ptr, val.__ptr)
}

RendererThreadJob.prototype.__get_data2 = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.RendererThreadJob__get_data2(this.__ptr)
	return retVal
}

RendererThreadJob.prototype.__set_data2 = function(val) {
	Polycode.RendererThreadJob__set_data2(this.__ptr, val.__ptr)
}

