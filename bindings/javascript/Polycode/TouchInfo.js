function TouchInfo() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.TouchInfo()
	}
	Object.defineProperties(this, {
		'id': { enumerable: true, configurable: true, get: TouchInfo.prototype.__get_id, set: TouchInfo.prototype.__set_id},
		'position': { enumerable: true, configurable: true, get: TouchInfo.prototype.__get_position, set: TouchInfo.prototype.__set_position},
		'type': { enumerable: true, configurable: true, get: TouchInfo.prototype.__get_type, set: TouchInfo.prototype.__set_type}
	})
}

TouchInfo.prototype.__get_id = function() {
	return Polycode.TouchInfo__get_id(this.__ptr)
}

TouchInfo.prototype.__set_id = function(val) {
	Polycode.TouchInfo__set_id(this.__ptr, val)
}

TouchInfo.prototype.__get_position = function() {
	var retVal = new Vector2()
	retVal.__ptr = 	Polycode.TouchInfo__get_position(this.__ptr)
	return retVal
}

TouchInfo.prototype.__set_position = function(val) {
	Polycode.TouchInfo__set_position(this.__ptr, val.__ptr)
}

TouchInfo.prototype.__get_type = function() {
	return Polycode.TouchInfo__get_type(this.__ptr)
}

TouchInfo.prototype.__set_type = function(val) {
	Polycode.TouchInfo__set_type(this.__ptr, val)
}

Duktape.fin(TouchInfo.prototype, function (x) {
	if (x === TouchInfo.prototype) {
		return;
	}
	Polycode.TouchInfo__delete(x.__ptr)
})
