function BezierPoint(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BezierPoint(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z)
	}
	Object.defineProperties(this, {
		'p1': { enumerable: true, configurable: true, get: BezierPoint.prototype.__get_p1, set: BezierPoint.prototype.__set_p1},
		'p2': { enumerable: true, configurable: true, get: BezierPoint.prototype.__get_p2, set: BezierPoint.prototype.__set_p2},
		'p3': { enumerable: true, configurable: true, get: BezierPoint.prototype.__get_p3, set: BezierPoint.prototype.__set_p3}
	})
}

BezierPoint.prototype.__get_p1 = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.BezierPoint__get_p1(this.__ptr)
	return retVal
}

BezierPoint.prototype.__set_p1 = function(val) {
	Polycode.BezierPoint__set_p1(this.__ptr, val.__ptr)
}

BezierPoint.prototype.__get_p2 = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.BezierPoint__get_p2(this.__ptr)
	return retVal
}

BezierPoint.prototype.__set_p2 = function(val) {
	Polycode.BezierPoint__set_p2(this.__ptr, val.__ptr)
}

BezierPoint.prototype.__get_p3 = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.BezierPoint__get_p3(this.__ptr)
	return retVal
}

BezierPoint.prototype.__set_p3 = function(val) {
	Polycode.BezierPoint__set_p3(this.__ptr, val.__ptr)
}

Duktape.fin(BezierPoint.prototype, function (x) {
	if (x === BezierPoint.prototype) {
		return;
	}
	Polycode.BezierPoint__delete(x.__ptr)
})
