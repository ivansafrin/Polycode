function ScenePrimitive() {
}

ScenePrimitive.prototype.setPrimitiveOptions = function(type,v1,v2,v3,v4,v5) {
	Polycode.ScenePrimitive_setPrimitiveOptions(this.__ptr, type,v1,v2,v3,v4,v5)
}

ScenePrimitive.prototype.recreatePrimitive = function() {
	Polycode.ScenePrimitive_recreatePrimitive(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveType = function() {
	Polycode.ScenePrimitive_getPrimitiveType(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter1 = function() {
	Polycode.ScenePrimitive_getPrimitiveParameter1(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter2 = function() {
	Polycode.ScenePrimitive_getPrimitiveParameter2(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter3 = function() {
	Polycode.ScenePrimitive_getPrimitiveParameter3(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter4 = function() {
	Polycode.ScenePrimitive_getPrimitiveParameter4(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter5 = function() {
	Polycode.ScenePrimitive_getPrimitiveParameter5(this.__ptr)
}

ScenePrimitive.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.ScenePrimitive_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

ScenePrimitive.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.ScenePrimitive_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}
