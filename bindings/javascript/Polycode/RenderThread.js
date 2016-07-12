function RenderThread() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderThread()
	}
}

RenderThread.JOB_REQUEST_CONTEXT_CHANGE = 0
RenderThread.JOB_DESTROY_TEXTURE = 8
RenderThread.JOB_DESTROY_SHADER = 9
RenderThread.JOB_DESTROY_PROGRAM = 10
RenderThread.JOB_DESTROY_SUBMESH_BUFFER = 11
RenderThread.JOB_DESTROY_RENDER_BUFFER = 13
RenderThread.JOB_SET_TEXTURE_PARAM = 14

Duktape.fin(RenderThread.prototype, function (x) {
	if (x === RenderThread.prototype) {
		return;
	}
	Polycode.RenderThread__delete(x.__ptr)
})

RenderThread.prototype.runThread = function() {
	Polycode.RenderThread_runThread(this.__ptr)
}

RenderThread.prototype.beginFrame = function() {
	Polycode.RenderThread_beginFrame(this.__ptr)
}

RenderThread.prototype.endFrame = function() {
	Polycode.RenderThread_endFrame(this.__ptr)
}

RenderThread.prototype.updateRenderThread = function() {
	Polycode.RenderThread_updateRenderThread(this.__ptr)
}

RenderThread.prototype.processJob = function(job) {
	Polycode.RenderThread_processJob(this.__ptr, job)
}

RenderThread.prototype.clearFrameQueue = function() {
	Polycode.RenderThread_clearFrameQueue(this.__ptr)
}

RenderThread.prototype.getFrameInfo = function() {
	var retVal = new RenderThreadDebugInfo("__skip_ptr__")
	retVal.__ptr = Polycode.RenderThread_getFrameInfo(this.__ptr)
	return retVal
}

RenderThread.prototype.initGlobals = function() {
	Polycode.RenderThread_initGlobals(this.__ptr)
}

RenderThread.prototype.lockRenderMutex = function() {
	Polycode.RenderThread_lockRenderMutex(this.__ptr)
}

RenderThread.prototype.unlockRenderMutex = function() {
	Polycode.RenderThread_unlockRenderMutex(this.__ptr)
}
