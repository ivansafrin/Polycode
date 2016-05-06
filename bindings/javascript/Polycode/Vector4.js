function Vector4() {
}

Vector4.prototype.set = function(x,y,z,w) {
	Polycode.Vector4_set(this.__ptr, x,y,z,w)
}

Vector4.prototype.dot = function(u) {
	Polycode.Vector4_dot(this.__ptr, u)
}
