function ObjectEntry() {
}

ObjectEntry.prototype.readNumber = function(key,out) {
	Polycode.ObjectEntry_readNumber(this.__ptr, key,out)
}

ObjectEntry.prototype.readString = function(key,out) {
	Polycode.ObjectEntry_readString(this.__ptr, key,out)
}

ObjectEntry.prototype.readBool = function(key,out) {
	Polycode.ObjectEntry_readBool(this.__ptr, key,out)
}

ObjectEntry.prototype.addChild = function(name) {
	Polycode.ObjectEntry_addChild(this.__ptr, name)
}

ObjectEntry.prototype.getTypedName = function() {
	Polycode.ObjectEntry_getTypedName(this.__ptr)
}

ObjectEntry.prototype.setTypedName = function(str) {
	Polycode.ObjectEntry_setTypedName(this.__ptr, str)
}

ObjectEntry.prototype.Clear = function() {
	Polycode.ObjectEntry_Clear(this.__ptr)
}
