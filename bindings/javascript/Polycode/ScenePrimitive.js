require('Polycode/SceneMesh')

function ScenePrimitive(type,v1,v2,v3,v4,v5) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ScenePrimitive(type,v1,v2,v3,v4,v5)
	}
}

ScenePrimitive.prototype = Object.create(SceneMesh.prototype);


ScenePrimitive.prototype.setPrimitiveOptions = function(type,v1,v2,v3,v4,v5) {
	Polycode.ScenePrimitive_setPrimitiveOptions(this.__ptr, type, v1, v2, v3, v4, v5)
}

ScenePrimitive.prototype.recreatePrimitive = function() {
	Polycode.ScenePrimitive_recreatePrimitive(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveType = function() {
	return Polycode.ScenePrimitive_getPrimitiveType(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter1 = function() {
	return Polycode.ScenePrimitive_getPrimitiveParameter1(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter2 = function() {
	return Polycode.ScenePrimitive_getPrimitiveParameter2(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter3 = function() {
	return Polycode.ScenePrimitive_getPrimitiveParameter3(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter4 = function() {
	return Polycode.ScenePrimitive_getPrimitiveParameter4(this.__ptr)
}

ScenePrimitive.prototype.getPrimitiveParameter5 = function() {
	return Polycode.ScenePrimitive_getPrimitiveParameter5(this.__ptr)
}

ScenePrimitive.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.ScenePrimitive_Clone(this.__ptr, deepClone, ignoreEditorOnly)
	return retVal
}

ScenePrimitive.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.ScenePrimitive_applyClone(this.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
}
