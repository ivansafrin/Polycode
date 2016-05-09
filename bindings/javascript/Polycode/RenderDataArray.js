function RenderDataArray() {
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_type, set: RenderDataArray.prototype.__set_type},
		'customArrayName': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_customArrayName, set: RenderDataArray.prototype.__set_customArrayName},
		'hasVBO': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_hasVBO, set: RenderDataArray.prototype.__set_hasVBO},
		'platformData': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_platformData, set: RenderDataArray.prototype.__set_platformData}
	})
}
RenderDataArray.prototype.__get_type = function() {
	return Polycode.RenderDataArray__get_type(this.__ptr)
}

RenderDataArray.prototype.__set_type = function(val) {
	Polycode.RenderDataArray__set_type(this.__ptr, val)
}

RenderDataArray.prototype.__get_customArrayName = function() {
	return Polycode.RenderDataArray__get_customArrayName(this.__ptr)
}

RenderDataArray.prototype.__set_customArrayName = function(val) {
	Polycode.RenderDataArray__set_customArrayName(this.__ptr, val)
}

RenderDataArray.prototype.__get_hasVBO = function() {
	return Polycode.RenderDataArray__get_hasVBO(this.__ptr)
}

RenderDataArray.prototype.__set_hasVBO = function(val) {
	Polycode.RenderDataArray__set_hasVBO(this.__ptr, val)
}

RenderDataArray.prototype.__get_platformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.RenderDataArray__get_platformData(this.__ptr)
	return retVal
}

RenderDataArray.prototype.__set_platformData = function(val) {
	Polycode.RenderDataArray__set_platformData(this.__ptr, val.__ptr)
}


RenderDataArray.prototype.getArrayData = function() {
	Polycode.RenderDataArray_getArrayData(this.__ptr)
}

RenderDataArray.prototype.getDataSize = function() {
	return Polycode.RenderDataArray_getDataSize(this.__ptr)
}
