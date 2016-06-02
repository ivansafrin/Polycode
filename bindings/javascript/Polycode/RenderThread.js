function RenderThread() {
}
Duktape.fin(RenderThread.prototype, function (x) {
	if (x === RenderThread.prototype) {
		return;
	}
	Polycode.RenderThread__delete(x.__ptr)
})

RenderThread.prototype.setGraphicsInterface = function(core,graphicsInterface) {
	Polycode.RenderThread_setGraphicsInterface(this.__ptr, core,graphicsInterface)
}

RenderThread.prototype.runThread = function() {
	Polycode.RenderThread_runThread(this.__ptr)
}

RenderThread.prototype.updateRenderThread = function() {
	Polycode.RenderThread_updateRenderThread(this.__ptr)
}

RenderThread.prototype.enqueueFrame = function(frame) {
	Polycode.RenderThread_enqueueFrame(this.__ptr, frame)
}

RenderThread.prototype.enqueueJob = function(jobType,data,data2) {
	Polycode.RenderThread_enqueueJob(this.__ptr, jobType,data,data2)
}

RenderThread.prototype.processJob = function(job) {
	Polycode.RenderThread_processJob(this.__ptr, job)
}

RenderThread.prototype.getShaderBinding = function() {
	var retVal = new ShaderBinding()
	retVal.__ptr = Polycode.RenderThread_getShaderBinding(this.__ptr)
	return retVal
}

RenderThread.prototype.processDrawBufferLights = function(buffer) {
	Polycode.RenderThread_processDrawBufferLights(this.__ptr, buffer)
}

RenderThread.prototype.processDrawBuffer = function(buffer) {
	Polycode.RenderThread_processDrawBuffer(this.__ptr, buffer)
}

RenderThread.prototype.getFrameInfo = function() {
	var retVal = new RenderThreadDebugInfo()
	retVal.__ptr = Polycode.RenderThread_getFrameInfo(this.__ptr)
	return retVal
}

RenderThread.prototype.clearFrameQueue = function() {
	Polycode.RenderThread_clearFrameQueue(this.__ptr)
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
