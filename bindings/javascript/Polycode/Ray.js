function Ray() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Ray()
	}
	Object.defineProperties(this, {
		'origin': { enumerable: true, configurable: true, get: Ray.prototype.__get_origin, set: Ray.prototype.__set_origin},
		'direction': { enumerable: true, configurable: true, get: Ray.prototype.__get_direction, set: Ray.prototype.__set_direction},
		'inv_direction': { enumerable: true, configurable: true, get: Ray.prototype.__get_inv_direction, set: Ray.prototype.__set_inv_direction}
	})
}

Ray.prototype.__get_origin = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.Ray__get_origin(this.__ptr)
	return retVal
}

Ray.prototype.__set_origin = function(val) {
	Polycode.Ray__set_origin(this.__ptr, val.__ptr)
}

Ray.prototype.__get_direction = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.Ray__get_direction(this.__ptr)
	return retVal
}

Ray.prototype.__set_direction = function(val) {
	Polycode.Ray__set_direction(this.__ptr, val.__ptr)
}

Ray.prototype.__get_inv_direction = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.Ray__get_inv_direction(this.__ptr)
	return retVal
}

Ray.prototype.__set_inv_direction = function(val) {
	Polycode.Ray__set_inv_direction(this.__ptr, val.__ptr)
}

Duktape.fin(Ray.prototype, function (x) {
	if (x === Ray.prototype) {
		return;
	}
	Polycode.Ray__delete(x.__ptr)
})

Ray.prototype.boxIntersect = function(box,transformMatrix,vnear,vfar) {
	return Polycode.Ray_boxIntersect(this.__ptr, box, transformMatrix, vnear, vfar)
}

Ray.prototype.planeIntersectPoint = function(planeNormal,planeDistance) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Ray_planeIntersectPoint(this.__ptr, planeNormal, planeDistance)
	return retVal
}

Ray.prototype.tranformByMatrix = function(matrix) {
	var retVal = new Ray()
	retVal.__ptr = Polycode.Ray_tranformByMatrix(this.__ptr, matrix)
	return retVal
}

Ray.prototype.closestPointOnRay = function(point) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Ray_closestPointOnRay(this.__ptr, point)
	return retVal
}

Ray.prototype.closestPointsBetween = function(ray2,point1,point2) {
	return Polycode.Ray_closestPointsBetween(this.__ptr, ray2, point1.__ptr, point2.__ptr)
}

Ray.prototype.polygonIntersect = function(v1,v2,v3) {
	return Polycode.Ray_polygonIntersect(this.__ptr, v1, v2, v3)
}
