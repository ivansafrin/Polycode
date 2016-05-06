function BezierCurve() {
}

BezierCurve.prototype.getControlPoint = function(index) {
	Polycode.BezierCurve_getControlPoint(this.__ptr, index)
}

BezierCurve.prototype.getNumControlPoints = function() {
	Polycode.BezierCurve_getNumControlPoints(this.__ptr)
}

BezierCurve.prototype.addControlPoint = function(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z) {
	Polycode.BezierCurve_addControlPoint(this.__ptr, p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z)
}

BezierCurve.prototype.addControlPoint3dWithHandles = function(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z) {
	Polycode.BezierCurve_addControlPoint3dWithHandles(this.__ptr, p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z)
}

BezierCurve.prototype.addControlPoint3d = function(x,y,z) {
	Polycode.BezierCurve_addControlPoint3d(this.__ptr, x,y,z)
}

BezierCurve.prototype.addControlPoint2dWithHandles = function(p1x,p1y,p2x,p2y,p3x,p3y) {
	Polycode.BezierCurve_addControlPoint2dWithHandles(this.__ptr, p1x,p1y,p2x,p2y,p3x,p3y)
}

BezierCurve.prototype.addControlPoint2d = function(x,y) {
	Polycode.BezierCurve_addControlPoint2d(this.__ptr, x,y)
}

BezierCurve.prototype.getPointAt = function(a) {
	Polycode.BezierCurve_getPointAt(this.__ptr, a)
}

BezierCurve.prototype.getPointBetween = function(a,bp1,bp2) {
	Polycode.BezierCurve_getPointBetween(this.__ptr, a,bp1,bp2)
}

BezierCurve.prototype.clearControlPoints = function() {
	Polycode.BezierCurve_clearControlPoints(this.__ptr)
}

BezierCurve.prototype.getYValueAtX = function(x) {
	Polycode.BezierCurve_getYValueAtX(this.__ptr, x)
}

BezierCurve.prototype.getTValueAtX = function(x) {
	Polycode.BezierCurve_getTValueAtX(this.__ptr, x)
}

BezierCurve.prototype.removePoint = function(point) {
	Polycode.BezierCurve_removePoint(this.__ptr, point)
}

BezierCurve.prototype.setHeightCacheResolution = function(resolution) {
	Polycode.BezierCurve_setHeightCacheResolution(this.__ptr, resolution)
}

BezierCurve.prototype.rebuildHeightCache = function() {
	Polycode.BezierCurve_rebuildHeightCache(this.__ptr)
}

BezierCurve.prototype.recalculateDistances = function() {
	Polycode.BezierCurve_recalculateDistances(this.__ptr)
}
