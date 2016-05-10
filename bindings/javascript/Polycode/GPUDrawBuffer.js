function GPUDrawBuffer() {
	Object.defineProperties(this, {
		'targetFramebuffer': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_targetFramebuffer, set: GPUDrawBuffer.prototype.__set_targetFramebuffer},
		'projectionMatrix': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_projectionMatrix, set: GPUDrawBuffer.prototype.__set_projectionMatrix},
		'viewMatrix': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_viewMatrix, set: GPUDrawBuffer.prototype.__set_viewMatrix},
		'cameraMatrix': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_cameraMatrix, set: GPUDrawBuffer.prototype.__set_cameraMatrix},
		'clearColor': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_clearColor, set: GPUDrawBuffer.prototype.__set_clearColor},
		'clearDepthBuffer': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_clearDepthBuffer, set: GPUDrawBuffer.prototype.__set_clearDepthBuffer},
		'clearColorBuffer': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_clearColorBuffer, set: GPUDrawBuffer.prototype.__set_clearColorBuffer},
		'backingResolutionScale': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_backingResolutionScale, set: GPUDrawBuffer.prototype.__set_backingResolutionScale},
		'globalMaterial': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_globalMaterial, set: GPUDrawBuffer.prototype.__set_globalMaterial},
		'viewport': { enumerable: true, configurable: true, get: GPUDrawBuffer.prototype.__get_viewport, set: GPUDrawBuffer.prototype.__set_viewport}
	})
}
GPUDrawBuffer.prototype.__get_targetFramebuffer = function() {
	var retVal = new RenderBuffer()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_targetFramebuffer(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_targetFramebuffer = function(val) {
	Polycode.GPUDrawBuffer__set_targetFramebuffer(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_projectionMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_projectionMatrix(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_projectionMatrix = function(val) {
	Polycode.GPUDrawBuffer__set_projectionMatrix(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_viewMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_viewMatrix(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_viewMatrix = function(val) {
	Polycode.GPUDrawBuffer__set_viewMatrix(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_cameraMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_cameraMatrix(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_cameraMatrix = function(val) {
	Polycode.GPUDrawBuffer__set_cameraMatrix(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_clearColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_clearColor(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_clearColor = function(val) {
	Polycode.GPUDrawBuffer__set_clearColor(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_clearDepthBuffer = function() {
	return Polycode.GPUDrawBuffer__get_clearDepthBuffer(this.__ptr)
}

GPUDrawBuffer.prototype.__set_clearDepthBuffer = function(val) {
	Polycode.GPUDrawBuffer__set_clearDepthBuffer(this.__ptr, val)
}

GPUDrawBuffer.prototype.__get_clearColorBuffer = function() {
	return Polycode.GPUDrawBuffer__get_clearColorBuffer(this.__ptr)
}

GPUDrawBuffer.prototype.__set_clearColorBuffer = function(val) {
	Polycode.GPUDrawBuffer__set_clearColorBuffer(this.__ptr, val)
}

GPUDrawBuffer.prototype.__get_backingResolutionScale = function() {
	var retVal = new Vector2()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_backingResolutionScale(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_backingResolutionScale = function(val) {
	Polycode.GPUDrawBuffer__set_backingResolutionScale(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_globalMaterial = function() {
	var retVal = new Material()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_globalMaterial(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_globalMaterial = function(val) {
	Polycode.GPUDrawBuffer__set_globalMaterial(this.__ptr, val.__ptr)
}

GPUDrawBuffer.prototype.__get_viewport = function() {
	var retVal = new Rectangle()
	retVal.__ptr = 	Polycode.GPUDrawBuffer__get_viewport(this.__ptr)
	return retVal
}

GPUDrawBuffer.prototype.__set_viewport = function(val) {
	Polycode.GPUDrawBuffer__set_viewport(this.__ptr, val.__ptr)
}

Duktape.fin(GPUDrawBuffer.prototype, function (x) {
	if (x === GPUDrawBuffer.prototype) {
		return;
	}
	Polycode.GPUDrawBuffer__delete(x.__ptr)
})
