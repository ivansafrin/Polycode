function Vector3() {
}

Vector3.prototype.set = function(x,y,z) {
	Polycode.Vector3_set(this.__ptr, x,y,z)
}

Vector3.prototype.distance = function(vec2) {
	Polycode.Vector3_distance(this.__ptr, vec2)
}

Vector3.prototype.angleBetween = function(dest) {
	Polycode.Vector3_angleBetween(this.__ptr, dest)
}

Vector3.prototype.length = function() {
	Polycode.Vector3_length(this.__ptr)
}

Vector3.prototype.lengthSquared = function() {
	Polycode.Vector3_lengthSquared(this.__ptr)
}

Vector3.prototype.setLength = function(newLength) {
	Polycode.Vector3_setLength(this.__ptr, newLength)
}

Vector3.prototype.dot = function(u) {
	Polycode.Vector3_dot(this.__ptr, u)
}

Vector3.prototype.crossProduct = function(vec2) {
	Polycode.Vector3_crossProduct(this.__ptr, vec2)
}

Vector3.prototype.Normalize = function() {
	Polycode.Vector3_Normalize(this.__ptr)
}
