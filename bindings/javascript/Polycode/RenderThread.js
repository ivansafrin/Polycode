function RenderThread() {
}

RenderThread.prototype.setGraphicsInterface = function(core,graphicsInterface) {
	Polycode.RenderThread_setGraphicsInterface(this.__ptr, core,graphicsInterface)
}

RenderThread.prototype.runThread = function() {
	Polycode.RenderThread_runThread(this.__ptr)
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
	Polycode.RenderThread_getShaderBinding(this.__ptr)
}

RenderThread.prototype.processDrawBuffer = function(buffer) {
	Polycode.RenderThread_processDrawBuffer(this.__ptr, buffer)
}

RenderThread.prototype.getFrameInfo = function() {
	Polycode.RenderThread_getFrameInfo(this.__ptr)
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
