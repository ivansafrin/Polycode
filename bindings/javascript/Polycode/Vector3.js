function Vector3() {
	Object.defineProperties(this, {
		'x': { enumerable: true, configurable: true, get: Vector3.prototype.__get_x, set: Vector3.prototype.__set_x},
		'y': { enumerable: true, configurable: true, get: Vector3.prototype.__get_y, set: Vector3.prototype.__set_y},
		'z': { enumerable: true, configurable: true, get: Vector3.prototype.__get_z, set: Vector3.prototype.__set_z}
	})
}
Vector3.prototype.__get_x = function() {
	return Polycode.Vector3__get_x(this.__ptr)
}

Vector3.prototype.__set_x = function(val) {
	Polycode.Vector3__set_x(this.__ptr, val)
}

Vector3.prototype.__get_y = function() {
	return Polycode.Vector3__get_y(this.__ptr)
}

Vector3.prototype.__set_y = function(val) {
	Polycode.Vector3__set_y(this.__ptr, val)
}

Vector3.prototype.__get_z = function() {
	return Polycode.Vector3__get_z(this.__ptr)
}

Vector3.prototype.__set_z = function(val) {
	Polycode.Vector3__set_z(this.__ptr, val)
}


Vector3.prototype.set = function(x,y,z) {
	Polycode.Vector3_set(this.__ptr, x,y,z)
}

Vector3.prototype.distance = function(vec2) {
	return Polycode.Vector3_distance(this.__ptr, vec2)
}

Vector3.prototype.angleBetween = function(dest) {
	return Polycode.Vector3_angleBetween(this.__ptr, dest)
}

Vector3.prototype.length = function() {
	return Polycode.Vector3_length(this.__ptr)
}

Vector3.prototype.lengthSquared = function() {
	return Polycode.Vector3_lengthSquared(this.__ptr)
}

Vector3.prototype.setLength = function(newLength) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Vector3_setLength(this.__ptr, newLength)
	return retVal
}

Vector3.prototype.dot = function(u) {
	return Polycode.Vector3_dot(this.__ptr, u)
}

Vector3.prototype.crossProduct = function(vec2) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Vector3_crossProduct(this.__ptr, vec2)
	return retVal
}

Vector3.prototype.Normalize = function() {
	Polycode.Vector3_Normalize(this.__ptr)
}
