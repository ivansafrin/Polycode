function RenderFrame() {
	Object.defineProperties(this, {
		'jobQueue': { enumerable: true, configurable: true, get: RenderFrame.prototype.__get_jobQueue, set: RenderFrame.prototype.__set_jobQueue}
	})
}
RenderFrame.prototype.__get_jobQueue = function() {
	var retVal = new queue<RendererThreadJob>()
	retVal.__ptr = 	Polycode.RenderFrame__get_jobQueue(this.__ptr)
	return retVal
}

RenderFrame.prototype.__set_jobQueue = function(val) {
	Polycode.RenderFrame__set_jobQueue(this.__ptr, val.__ptr)
}

