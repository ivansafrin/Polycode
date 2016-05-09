function IndexDataArray() {
}

IndexDataArray.prototype.getArrayData = function() {
	Polycode.IndexDataArray_getArrayData(this.__ptr)
}

IndexDataArray.prototype.getDataSize = function() {
	return Polycode.IndexDataArray_getDataSize(this.__ptr)
}
