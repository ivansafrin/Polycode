function QuaternionCurve() {
}

QuaternionCurve.prototype.interpolate = function(t,useShortestPath) {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.QuaternionCurve_interpolate(this.__ptr, t,useShortestPath)
	return retVal
}

QuaternionCurve.prototype.generatePointsFromCurves = function(wCurve,xCurve,yCurve,zCurve) {
	Polycode.QuaternionCurve_generatePointsFromCurves(this.__ptr, wCurve,xCurve,yCurve,zCurve)
}
