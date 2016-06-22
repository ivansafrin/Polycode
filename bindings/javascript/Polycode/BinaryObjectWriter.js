function BinaryObjectWriter(object) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BinaryObjectWriter(object)
	}
}

Duktape.fin(BinaryObjectWriter.prototype, function (x) {
	if (x === BinaryObjectWriter.prototype) {
		return;
	}
	Polycode.BinaryObjectWriter__delete(x.__ptr)
})

BinaryObjectWriter.prototype.parseKeysFromObjectEntry = function(entry) {
	Polycode.BinaryObjectWriter_parseKeysFromObjectEntry(this.__ptr, entry.__ptr)
}

BinaryObjectWriter.prototype.writeEntryToFile = function(entry) {
	Polycode.BinaryObjectWriter_writeEntryToFile(this.__ptr, entry.__ptr)
}

BinaryObjectWriter.prototype.addKey = function(key) {
	return Polycode.BinaryObjectWriter_addKey(this.__ptr, key)
}

BinaryObjectWriter.prototype.getKeyIndex = function(key) {
	return Polycode.BinaryObjectWriter_getKeyIndex(this.__ptr, key)
}

BinaryObjectWriter.prototype.writeToFile = function(fileName) {
	return Polycode.BinaryObjectWriter_writeToFile(this.__ptr, fileName)
}
