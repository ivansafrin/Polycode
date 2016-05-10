function OSFileEntry() {
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_name, set: OSFileEntry.prototype.__set_name},
		'extension': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_extension, set: OSFileEntry.prototype.__set_extension},
		'nameWithoutExtension': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_nameWithoutExtension, set: OSFileEntry.prototype.__set_nameWithoutExtension},
		'basePath': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_basePath, set: OSFileEntry.prototype.__set_basePath},
		'fullPath': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_fullPath, set: OSFileEntry.prototype.__set_fullPath},
		'type': { enumerable: true, configurable: true, get: OSFileEntry.prototype.__get_type, set: OSFileEntry.prototype.__set_type}
	})
}
OSFileEntry.prototype.__get_name = function() {
	return Polycode.OSFileEntry__get_name(this.__ptr)
}

OSFileEntry.prototype.__set_name = function(val) {
	Polycode.OSFileEntry__set_name(this.__ptr, val)
}

OSFileEntry.prototype.__get_extension = function() {
	return Polycode.OSFileEntry__get_extension(this.__ptr)
}

OSFileEntry.prototype.__set_extension = function(val) {
	Polycode.OSFileEntry__set_extension(this.__ptr, val)
}

OSFileEntry.prototype.__get_nameWithoutExtension = function() {
	return Polycode.OSFileEntry__get_nameWithoutExtension(this.__ptr)
}

OSFileEntry.prototype.__set_nameWithoutExtension = function(val) {
	Polycode.OSFileEntry__set_nameWithoutExtension(this.__ptr, val)
}

OSFileEntry.prototype.__get_basePath = function() {
	return Polycode.OSFileEntry__get_basePath(this.__ptr)
}

OSFileEntry.prototype.__set_basePath = function(val) {
	Polycode.OSFileEntry__set_basePath(this.__ptr, val)
}

OSFileEntry.prototype.__get_fullPath = function() {
	return Polycode.OSFileEntry__get_fullPath(this.__ptr)
}

OSFileEntry.prototype.__set_fullPath = function(val) {
	Polycode.OSFileEntry__set_fullPath(this.__ptr, val)
}

OSFileEntry.prototype.__get_type = function() {
	return Polycode.OSFileEntry__get_type(this.__ptr)
}

OSFileEntry.prototype.__set_type = function(val) {
	Polycode.OSFileEntry__set_type(this.__ptr, val)
}

Duktape.fin(OSFileEntry.prototype, function (x) {
	if (x === OSFileEntry.prototype) {
		return;
	}
	Polycode.OSFileEntry__delete(x.__ptr)
})

OSFileEntry.prototype.init = function(path,name,type) {
	Polycode.OSFileEntry_init(this.__ptr, path,name,type)
}
