function Ray() {
}

Ray.prototype.boxIntersect = function(box,transformMatrix,near,far) {
	Polycode.Ray_boxIntersect(this.__ptr, box,transformMatrix,near,far)
}

Ray.prototype.planeIntersectPoint = function(planeNormal,planeDistance) {
	Polycode.Ray_planeIntersectPoint(this.__ptr, planeNormal,planeDistance)
}

Ray.prototype.tranformByMatrix = function(matrix) {
	Polycode.Ray_tranformByMatrix(this.__ptr, matrix)
}

Ray.prototype.closestPointOnRay = function(point) {
	Polycode.Ray_closestPointOnRay(this.__ptr, point)
}

Ray.prototype.closestPointsBetween = function(ray2,point1,point2) {
	Polycode.Ray_closestPointsBetween(this.__ptr, ray2,point1,point2)
}

Ray.prototype.polygonIntersect = function(v1,v2,v3) {
	Polycode.Ray_polygonIntersect(this.__ptr, v1,v2,v3)
}
