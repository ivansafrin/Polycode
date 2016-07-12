function ObjectEntry() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ObjectEntry()
	}
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_type, set: ObjectEntry.prototype.__set_type},
		'name': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_name, set: ObjectEntry.prototype.__set_name},
		'NumberVal': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_NumberVal, set: ObjectEntry.prototype.__set_NumberVal},
		'intVal': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_intVal, set: ObjectEntry.prototype.__set_intVal},
		'stringVal': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_stringVal, set: ObjectEntry.prototype.__set_stringVal},
		'boolVal': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_boolVal, set: ObjectEntry.prototype.__set_boolVal},
		'length': { enumerable: true, configurable: true, get: ObjectEntry.prototype.__get_length, set: ObjectEntry.prototype.__set_length}
	})
}

ObjectEntry.UNKNOWN_ENTRY = - 1
ObjectEntry.FLOAT_ENTRY = 0
ObjectEntry.INT_ENTRY = 1
ObjectEntry.BOOL_ENTRY = 2
ObjectEntry.ARRAY_ENTRY = 3
ObjectEntry.STRING_ENTRY = 4
ObjectEntry.CONTAINER_ENTRY = 5

ObjectEntry.prototype.__get_type = function() {
	return Polycode.ObjectEntry__get_type(this.__ptr)
}

ObjectEntry.prototype.__set_type = function(val) {
	Polycode.ObjectEntry__set_type(this.__ptr, val)
}

ObjectEntry.prototype.__get_name = function() {
	return Polycode.ObjectEntry__get_name(this.__ptr)
}

ObjectEntry.prototype.__set_name = function(val) {
	Polycode.ObjectEntry__set_name(this.__ptr, val)
}

ObjectEntry.prototype.__get_NumberVal = function() {
	return Polycode.ObjectEntry__get_NumberVal(this.__ptr)
}

ObjectEntry.prototype.__set_NumberVal = function(val) {
	Polycode.ObjectEntry__set_NumberVal(this.__ptr, val)
}

ObjectEntry.prototype.__get_intVal = function() {
	return Polycode.ObjectEntry__get_intVal(this.__ptr)
}

ObjectEntry.prototype.__set_intVal = function(val) {
	Polycode.ObjectEntry__set_intVal(this.__ptr, val)
}

ObjectEntry.prototype.__get_stringVal = function() {
	return Polycode.ObjectEntry__get_stringVal(this.__ptr)
}

ObjectEntry.prototype.__set_stringVal = function(val) {
	Polycode.ObjectEntry__set_stringVal(this.__ptr, val)
}

ObjectEntry.prototype.__get_boolVal = function() {
	return Polycode.ObjectEntry__get_boolVal(this.__ptr)
}

ObjectEntry.prototype.__set_boolVal = function(val) {
	Polycode.ObjectEntry__set_boolVal(this.__ptr, val)
}

ObjectEntry.prototype.__get_length = function() {
	return Polycode.ObjectEntry__get_length(this.__ptr)
}

ObjectEntry.prototype.__set_length = function(val) {
	Polycode.ObjectEntry__set_length(this.__ptr, val)
}

Duktape.fin(ObjectEntry.prototype, function (x) {
	if (x === ObjectEntry.prototype) {
		return;
	}
	Polycode.ObjectEntry__delete(x.__ptr)
})

ObjectEntry.prototype.getTypedName = function() {
	return Polycode.ObjectEntry_getTypedName(this.__ptr)
}

ObjectEntry.prototype.setTypedName = function(str) {
	Polycode.ObjectEntry_setTypedName(this.__ptr, str)
}

ObjectEntry.prototype.Clear = function() {
	Polycode.ObjectEntry_Clear(this.__ptr)
}
