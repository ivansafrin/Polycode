function CoreFileExtension() {
	Object.defineProperties(this, {
		'extension': { enumerable: true, configurable: true, get: CoreFileExtension.prototype.__get_extension, set: CoreFileExtension.prototype.__set_extension},
		'description': { enumerable: true, configurable: true, get: CoreFileExtension.prototype.__get_description, set: CoreFileExtension.prototype.__set_description}
	})
}
CoreFileExtension.prototype.__get_extension = function() {
	return Polycode.CoreFileExtension__get_extension(this.__ptr)
}

CoreFileExtension.prototype.__set_extension = function(val) {
	Polycode.CoreFileExtension__set_extension(this.__ptr, val)
}

CoreFileExtension.prototype.__get_description = function() {
	return Polycode.CoreFileExtension__get_description(this.__ptr)
}

CoreFileExtension.prototype.__set_description = function(val) {
	Polycode.CoreFileExtension__set_description(this.__ptr, val)
}

