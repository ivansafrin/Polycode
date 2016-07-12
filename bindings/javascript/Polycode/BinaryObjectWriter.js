function BinaryObjectWriter() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BinaryObjectWriter()
	}
}


Duktape.fin(BinaryObjectWriter.prototype, function (x) {
	if (x === BinaryObjectWriter.prototype) {
		return;
	}
	Polycode.BinaryObjectWriter__delete(x.__ptr)
})

BinaryObjectWriter.prototype.addKey = function(key) {
	return Polycode.BinaryObjectWriter_addKey(this.__ptr, key)
}

BinaryObjectWriter.prototype.getKeyIndex = function(key) {
	return Polycode.BinaryObjectWriter_getKeyIndex(this.__ptr, key)
}

BinaryObjectWriter.prototype.writeToFile = function(fileName) {
	return Polycode.BinaryObjectWriter_writeToFile(this.__ptr, fileName)
}
