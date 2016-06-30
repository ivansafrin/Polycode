function RendererThreadJob() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RendererThreadJob()
	}
	Object.defineProperties(this, {
		'jobType': { enumerable: true, configurable: true, get: RendererThreadJob.prototype.__get_jobType, set: RendererThreadJob.prototype.__set_jobType}
	})
}


RendererThreadJob.prototype.__get_jobType = function() {
	return Polycode.RendererThreadJob__get_jobType(this.__ptr)
}

RendererThreadJob.prototype.__set_jobType = function(val) {
	Polycode.RendererThreadJob__set_jobType(this.__ptr, val)
}

Duktape.fin(RendererThreadJob.prototype, function (x) {
	if (x === RendererThreadJob.prototype) {
		return;
	}
	Polycode.RendererThreadJob__delete(x.__ptr)
})
