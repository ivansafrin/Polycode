function ConfigEntry() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ConfigEntry()
	}
	Object.defineProperties(this, {
		'key': { enumerable: true, configurable: true, get: ConfigEntry.prototype.__get_key, set: ConfigEntry.prototype.__set_key},
		'configNamespace': { enumerable: true, configurable: true, get: ConfigEntry.prototype.__get_configNamespace, set: ConfigEntry.prototype.__set_configNamespace},
		'numVal': { enumerable: true, configurable: true, get: ConfigEntry.prototype.__get_numVal, set: ConfigEntry.prototype.__set_numVal},
		'stringVal': { enumerable: true, configurable: true, get: ConfigEntry.prototype.__get_stringVal, set: ConfigEntry.prototype.__set_stringVal},
		'isString': { enumerable: true, configurable: true, get: ConfigEntry.prototype.__get_isString, set: ConfigEntry.prototype.__set_isString}
	})
}

ConfigEntry.prototype.__get_key = function() {
	return Polycode.ConfigEntry__get_key(this.__ptr)
}

ConfigEntry.prototype.__set_key = function(val) {
	Polycode.ConfigEntry__set_key(this.__ptr, val)
}

ConfigEntry.prototype.__get_configNamespace = function() {
	return Polycode.ConfigEntry__get_configNamespace(this.__ptr)
}

ConfigEntry.prototype.__set_configNamespace = function(val) {
	Polycode.ConfigEntry__set_configNamespace(this.__ptr, val)
}

ConfigEntry.prototype.__get_numVal = function() {
	return Polycode.ConfigEntry__get_numVal(this.__ptr)
}

ConfigEntry.prototype.__set_numVal = function(val) {
	Polycode.ConfigEntry__set_numVal(this.__ptr, val)
}

ConfigEntry.prototype.__get_stringVal = function() {
	return Polycode.ConfigEntry__get_stringVal(this.__ptr)
}

ConfigEntry.prototype.__set_stringVal = function(val) {
	Polycode.ConfigEntry__set_stringVal(this.__ptr, val)
}

ConfigEntry.prototype.__get_isString = function() {
	return Polycode.ConfigEntry__get_isString(this.__ptr)
}

ConfigEntry.prototype.__set_isString = function(val) {
	Polycode.ConfigEntry__set_isString(this.__ptr, val)
}

Duktape.fin(ConfigEntry.prototype, function (x) {
	if (x === ConfigEntry.prototype) {
		return;
	}
	Polycode.ConfigEntry__delete(x.__ptr)
})
