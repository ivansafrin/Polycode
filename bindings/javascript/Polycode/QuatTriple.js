function QuatTriple() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.QuatTriple()
	}
	Object.defineProperties(this, {
		'q1': { enumerable: true, configurable: true, get: QuatTriple.prototype.__get_q1, set: QuatTriple.prototype.__set_q1},
		'q2': { enumerable: true, configurable: true, get: QuatTriple.prototype.__get_q2, set: QuatTriple.prototype.__set_q2},
		'q3': { enumerable: true, configurable: true, get: QuatTriple.prototype.__get_q3, set: QuatTriple.prototype.__set_q3},
		'time': { enumerable: true, configurable: true, get: QuatTriple.prototype.__get_time, set: QuatTriple.prototype.__set_time}
	})
}

QuatTriple.prototype.__get_q1 = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.QuatTriple__get_q1(this.__ptr)
	return retVal
}

QuatTriple.prototype.__set_q1 = function(val) {
	Polycode.QuatTriple__set_q1(this.__ptr, val.__ptr)
}

QuatTriple.prototype.__get_q2 = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.QuatTriple__get_q2(this.__ptr)
	return retVal
}

QuatTriple.prototype.__set_q2 = function(val) {
	Polycode.QuatTriple__set_q2(this.__ptr, val.__ptr)
}

QuatTriple.prototype.__get_q3 = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.QuatTriple__get_q3(this.__ptr)
	return retVal
}

QuatTriple.prototype.__set_q3 = function(val) {
	Polycode.QuatTriple__set_q3(this.__ptr, val.__ptr)
}

QuatTriple.prototype.__get_time = function() {
	return Polycode.QuatTriple__get_time(this.__ptr)
}

QuatTriple.prototype.__set_time = function(val) {
	Polycode.QuatTriple__set_time(this.__ptr, val)
}

Duktape.fin(QuatTriple.prototype, function (x) {
	if (x === QuatTriple.prototype) {
		return;
	}
	Polycode.QuatTriple__delete(x.__ptr)
})
