function QuaternionCurve() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.QuaternionCurve()
	}
}


Duktape.fin(QuaternionCurve.prototype, function (x) {
	if (x === QuaternionCurve.prototype) {
		return;
	}
	Polycode.QuaternionCurve__delete(x.__ptr)
})

QuaternionCurve.prototype.interpolate = function(t,useShortestPath) {
	var retVal = new Quaternion("__skip_ptr__")
	retVal.__ptr = Polycode.QuaternionCurve_interpolate(this.__ptr, t, useShortestPath)
	return retVal
}
