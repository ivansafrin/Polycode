function VertexDataArray() {
}

VertexDataArray.prototype.getCountPerVertex = function() {
	Polycode.VertexDataArray_getCountPerVertex(this.__ptr)
}

VertexDataArray.prototype.getArrayData = function() {
	Polycode.VertexDataArray_getArrayData(this.__ptr)
}

VertexDataArray.prototype.getDataSize = function() {
	Polycode.VertexDataArray_getDataSize(this.__ptr)
}
