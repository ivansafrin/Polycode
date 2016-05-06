function Vector2() {
}

Vector2.prototype.set = function(x,y) {
	Polycode.Vector2_set(this.__ptr, x,y)
}

Vector2.prototype.distance = function(vec2) {
	Polycode.Vector2_distance(this.__ptr, vec2)
}

Vector2.prototype.length = function() {
	Polycode.Vector2_length(this.__ptr)
}

Vector2.prototype.dot = function(u) {
	Polycode.Vector2_dot(this.__ptr, u)
}

Vector2.prototype.crossProduct = function(vec2) {
	Polycode.Vector2_crossProduct(this.__ptr, vec2)
}

Vector2.prototype.angle = function(vec2) {
	Polycode.Vector2_angle(this.__ptr, vec2)
}

Vector2.prototype.Normalize = function() {
	Polycode.Vector2_Normalize(this.__ptr)
}
