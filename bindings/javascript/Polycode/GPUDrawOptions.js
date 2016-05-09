function GPUDrawOptions() {
	Object.defineProperties(this, {
		'depthTest': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_depthTest, set: GPUDrawOptions.prototype.__set_depthTest},
		'depthWrite': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_depthWrite, set: GPUDrawOptions.prototype.__set_depthWrite},
		'linePointSize': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_linePointSize, set: GPUDrawOptions.prototype.__set_linePointSize},
		'alphaTest': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_alphaTest, set: GPUDrawOptions.prototype.__set_alphaTest},
		'backfaceCull': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_backfaceCull, set: GPUDrawOptions.prototype.__set_backfaceCull},
		'depthOnly': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_depthOnly, set: GPUDrawOptions.prototype.__set_depthOnly},
		'forceMaterial': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_forceMaterial, set: GPUDrawOptions.prototype.__set_forceMaterial},
		'blendingMode': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_blendingMode, set: GPUDrawOptions.prototype.__set_blendingMode},
		'scissorBox': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_scissorBox, set: GPUDrawOptions.prototype.__set_scissorBox},
		'enableScissor': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_enableScissor, set: GPUDrawOptions.prototype.__set_enableScissor},
		'drawColor': { enumerable: true, configurable: true, get: GPUDrawOptions.prototype.__get_drawColor, set: GPUDrawOptions.prototype.__set_drawColor}
	})
}
GPUDrawOptions.prototype.__get_depthTest = function() {
	return Polycode.GPUDrawOptions__get_depthTest(this.__ptr)
}

GPUDrawOptions.prototype.__set_depthTest = function(val) {
	Polycode.GPUDrawOptions__set_depthTest(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_depthWrite = function() {
	return Polycode.GPUDrawOptions__get_depthWrite(this.__ptr)
}

GPUDrawOptions.prototype.__set_depthWrite = function(val) {
	Polycode.GPUDrawOptions__set_depthWrite(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_linePointSize = function() {
	return Polycode.GPUDrawOptions__get_linePointSize(this.__ptr)
}

GPUDrawOptions.prototype.__set_linePointSize = function(val) {
	Polycode.GPUDrawOptions__set_linePointSize(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_alphaTest = function() {
	return Polycode.GPUDrawOptions__get_alphaTest(this.__ptr)
}

GPUDrawOptions.prototype.__set_alphaTest = function(val) {
	Polycode.GPUDrawOptions__set_alphaTest(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_backfaceCull = function() {
	return Polycode.GPUDrawOptions__get_backfaceCull(this.__ptr)
}

GPUDrawOptions.prototype.__set_backfaceCull = function(val) {
	Polycode.GPUDrawOptions__set_backfaceCull(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_depthOnly = function() {
	return Polycode.GPUDrawOptions__get_depthOnly(this.__ptr)
}

GPUDrawOptions.prototype.__set_depthOnly = function(val) {
	Polycode.GPUDrawOptions__set_depthOnly(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_forceMaterial = function() {
	return Polycode.GPUDrawOptions__get_forceMaterial(this.__ptr)
}

GPUDrawOptions.prototype.__set_forceMaterial = function(val) {
	Polycode.GPUDrawOptions__set_forceMaterial(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_blendingMode = function() {
	return Polycode.GPUDrawOptions__get_blendingMode(this.__ptr)
}

GPUDrawOptions.prototype.__set_blendingMode = function(val) {
	Polycode.GPUDrawOptions__set_blendingMode(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_scissorBox = function() {
	var retVal = new Rectangle()
	retVal.__ptr = 	Polycode.GPUDrawOptions__get_scissorBox(this.__ptr)
	return retVal
}

GPUDrawOptions.prototype.__set_scissorBox = function(val) {
	Polycode.GPUDrawOptions__set_scissorBox(this.__ptr, val.__ptr)
}

GPUDrawOptions.prototype.__get_enableScissor = function() {
	return Polycode.GPUDrawOptions__get_enableScissor(this.__ptr)
}

GPUDrawOptions.prototype.__set_enableScissor = function(val) {
	Polycode.GPUDrawOptions__set_enableScissor(this.__ptr, val)
}

GPUDrawOptions.prototype.__get_drawColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.GPUDrawOptions__get_drawColor(this.__ptr)
	return retVal
}

GPUDrawOptions.prototype.__set_drawColor = function(val) {
	Polycode.GPUDrawOptions__set_drawColor(this.__ptr, val.__ptr)
}

