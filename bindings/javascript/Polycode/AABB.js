function AABB() {
	Object.defineProperties(this, {
		'min': { enumerable: true, configurable: true, get: AABB.prototype.__get_min, set: AABB.prototype.__set_min},
		'max': { enumerable: true, configurable: true, get: AABB.prototype.__get_max, set: AABB.prototype.__set_max}
	})
}
AABB.prototype.__get_min = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.AABB__get_min(this.__ptr)
	return retVal
}

AABB.prototype.__set_min = function(val) {
	Polycode.AABB__set_min(this.__ptr, val.__ptr)
}

AABB.prototype.__get_max = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.AABB__get_max(this.__ptr)
	return retVal
}

AABB.prototype.__set_max = function(val) {
	Polycode.AABB__set_max(this.__ptr, val.__ptr)
}

Duktape.fin(AABB.prototype, function (x) {
	if (x === AABB.prototype) {
		return;
	}
	Polycode.AABB__delete(x.__ptr)
})
