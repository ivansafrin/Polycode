function ObjectEntry() {
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


ObjectEntry.prototype.readNumber = function(key,out) {
	return Polycode.ObjectEntry_readNumber(this.__ptr, key,out)
}

ObjectEntry.prototype.readString = function(key,out) {
	return Polycode.ObjectEntry_readString(this.__ptr, key,out)
}

ObjectEntry.prototype.readBool = function(key,out) {
	return Polycode.ObjectEntry_readBool(this.__ptr, key,out)
}

ObjectEntry.prototype.addChild = function(name) {
	var retVal = new ObjectEntry()
	retVal.__ptr = Polycode.ObjectEntry_addChild(this.__ptr, name)
	return retVal
}

ObjectEntry.prototype.getTypedName = function() {
	return Polycode.ObjectEntry_getTypedName(this.__ptr)
}

ObjectEntry.prototype.setTypedName = function(str) {
	Polycode.ObjectEntry_setTypedName(this.__ptr, str)
}

ObjectEntry.prototype.Clear = function() {
	Polycode.ObjectEntry_Clear(this.__ptr)
}
