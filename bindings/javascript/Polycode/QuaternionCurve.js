function QuaternionCurve(wCurve,xCurve,yCurve,zCurve) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.QuaternionCurve(wCurve,xCurve,yCurve,zCurve)
	}
}

Duktape.fin(QuaternionCurve.prototype, function (x) {
	if (x === QuaternionCurve.prototype) {
		return;
	}
	Polycode.QuaternionCurve__delete(x.__ptr)
})

QuaternionCurve.prototype.interpolate = function(t,useShortestPath) {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.QuaternionCurve_interpolate(this.__ptr, t, useShortestPath)
	return retVal
}

QuaternionCurve.prototype.generatePointsFromCurves = function(wCurve,xCurve,yCurve,zCurve) {
	Polycode.QuaternionCurve_generatePointsFromCurves(this.__ptr, wCurve.__ptr, xCurve.__ptr, yCurve.__ptr, zCurve.__ptr)
}
