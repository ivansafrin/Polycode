function BinaryObjectWriter() {
}

BinaryObjectWriter.prototype.parseKeysFromObjectEntry = function(entry) {
	Polycode.BinaryObjectWriter_parseKeysFromObjectEntry(this.__ptr, entry)
}

BinaryObjectWriter.prototype.writeEntryToFile = function(entry) {
	Polycode.BinaryObjectWriter_writeEntryToFile(this.__ptr, entry)
}

BinaryObjectWriter.prototype.addKey = function(key) {
	Polycode.BinaryObjectWriter_addKey(this.__ptr, key)
}

BinaryObjectWriter.prototype.getKeyIndex = function(key) {
	Polycode.BinaryObjectWriter_getKeyIndex(this.__ptr, key)
}

BinaryObjectWriter.prototype.writeToFile = function(fileName) {
	Polycode.BinaryObjectWriter_writeToFile(this.__ptr, fileName)
}
