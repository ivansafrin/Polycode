function RenderDataArray(type) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderDataArray(type)
	}
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_type, set: RenderDataArray.prototype.__set_type},
		'customArrayName': { enumerable: true, configurable: true, get: RenderDataArray.prototype.__get_customArrayName, set: RenderDataArray.prototype.__set_customArrayName}
	})
}

RenderDataArray.VERTEX_DATA_ARRAY = 0
RenderDataArray.COLOR_DATA_ARRAY = 1
RenderDataArray.NORMAL_DATA_ARRAY = 2
RenderDataArray.TEXCOORD_DATA_ARRAY = 3
RenderDataArray.TANGENT_DATA_ARRAY = 4
RenderDataArray.BONE_WEIGHT_DATA_ARRAY = 5
RenderDataArray.BONE_INDEX_DATA_ARRAY = 6
RenderDataArray.INDEX_DATA_ARRAY = 7
RenderDataArray.TEXCOORD2_DATA_ARRAY = 8
RenderDataArray.CUSTOM_DATA_ARRAY1 = 9
RenderDataArray.CUSTOM_DATA_ARRAY2 = 10
RenderDataArray.CUSTOM_DATA_ARRAY3 = 11
RenderDataArray.CUSTOM_DATA_ARRAY4 = 12
RenderDataArray.UNKNOWN_DATA_ARRAY = 13

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

Duktape.fin(RenderDataArray.prototype, function (x) {
	if (x === RenderDataArray.prototype) {
		return;
	}
	Polycode.RenderDataArray__delete(x.__ptr)
})

RenderDataArray.prototype.getArrayData = function() {
	Polycode.RenderDataArray_getArrayData(this.__ptr)
}

RenderDataArray.prototype.getDataSize = function() {
	return Polycode.RenderDataArray_getDataSize(this.__ptr)
}
