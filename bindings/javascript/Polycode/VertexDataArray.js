function VertexDataArray() {
	Object.defineProperties(this, {
		'countPerVertex': { enumerable: true, configurable: true, get: VertexDataArray.prototype.__get_countPerVertex, set: VertexDataArray.prototype.__set_countPerVertex}
	})
}
VertexDataArray.prototype.__get_countPerVertex = function() {
	return Polycode.VertexDataArray__get_countPerVertex(this.__ptr)
}

VertexDataArray.prototype.__set_countPerVertex = function(val) {
	Polycode.VertexDataArray__set_countPerVertex(this.__ptr, val)
}


VertexDataArray.prototype.getCountPerVertex = function() {
	var retVal = new char()
	retVal.__ptr = Polycode.VertexDataArray_getCountPerVertex(this.__ptr)
	return retVal
}

VertexDataArray.prototype.getArrayData = function() {
	Polycode.VertexDataArray_getArrayData(this.__ptr)
}

VertexDataArray.prototype.getDataSize = function() {
	return Polycode.VertexDataArray_getDataSize(this.__ptr)
}
