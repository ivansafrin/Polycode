function AttributeBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.AttributeBinding()
	}
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_name, set: AttributeBinding.prototype.__set_name},
		'enabled': { enumerable: true, configurable: true, get: AttributeBinding.prototype.__get_enabled, set: AttributeBinding.prototype.__set_enabled}
	})
}


AttributeBinding.prototype.__get_name = function() {
	return Polycode.AttributeBinding__get_name(this.__ptr)
}

AttributeBinding.prototype.__set_name = function(val) {
	Polycode.AttributeBinding__set_name(this.__ptr, val)
}

AttributeBinding.prototype.__get_enabled = function() {
	return Polycode.AttributeBinding__get_enabled(this.__ptr)
}

AttributeBinding.prototype.__set_enabled = function(val) {
	Polycode.AttributeBinding__set_enabled(this.__ptr, val)
}

Duktape.fin(AttributeBinding.prototype, function (x) {
	if (x === AttributeBinding.prototype) {
		return;
	}
	Polycode.AttributeBinding__delete(x.__ptr)
})
