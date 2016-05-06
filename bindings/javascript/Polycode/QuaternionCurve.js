function QuaternionCurve() {
}

QuaternionCurve.prototype.interpolate = function(t,useShortestPath) {
	Polycode.QuaternionCurve_interpolate(this.__ptr, t,useShortestPath)
}

QuaternionCurve.prototype.generatePointsFromCurves = function(wCurve,xCurve,yCurve,zCurve) {
	Polycode.QuaternionCurve_generatePointsFromCurves(this.__ptr, wCurve,xCurve,yCurve,zCurve)
}
