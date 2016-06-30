function BinaryObjectReader(fileName,object) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BinaryObjectReader(fileName,object)
	}
	Object.defineProperties(this, {
		'success': { enumerable: true, configurable: true, get: BinaryObjectReader.prototype.__get_success, set: BinaryObjectReader.prototype.__set_success}
	})
}


BinaryObjectReader.prototype.__get_success = function() {
	return Polycode.BinaryObjectReader__get_success(this.__ptr)
}

BinaryObjectReader.prototype.__set_success = function(val) {
	Polycode.BinaryObjectReader__set_success(this.__ptr, val)
}

Duktape.fin(BinaryObjectReader.prototype, function (x) {
	if (x === BinaryObjectReader.prototype) {
		return;
	}
	Polycode.BinaryObjectReader__delete(x.__ptr)
})
