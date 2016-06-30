function Vector2(x,y) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Vector2(x,y)
	}
	Object.defineProperties(this, {
		'x': { enumerable: true, configurable: true, get: Vector2.prototype.__get_x, set: Vector2.prototype.__set_x},
		'y': { enumerable: true, configurable: true, get: Vector2.prototype.__get_y, set: Vector2.prototype.__set_y}
	})
}


Vector2.prototype.__get_x = function() {
	return Polycode.Vector2__get_x(this.__ptr)
}

Vector2.prototype.__set_x = function(val) {
	Polycode.Vector2__set_x(this.__ptr, val)
}

Vector2.prototype.__get_y = function() {
	return Polycode.Vector2__get_y(this.__ptr)
}

Vector2.prototype.__set_y = function(val) {
	Polycode.Vector2__set_y(this.__ptr, val)
}

Duktape.fin(Vector2.prototype, function (x) {
	if (x === Vector2.prototype) {
		return;
	}
	Polycode.Vector2__delete(x.__ptr)
})

Vector2.prototype.set = function(x,y) {
	Polycode.Vector2_set(this.__ptr, x, y)
}

Vector2.prototype.distance = function(vec2) {
	return Polycode.Vector2_distance(this.__ptr, vec2)
}

Vector2.prototype.length = function() {
	return Polycode.Vector2_length(this.__ptr)
}

Vector2.prototype.dot = function(u) {
	return Polycode.Vector2_dot(this.__ptr, u)
}

Vector2.prototype.crossProduct = function(vec2) {
	return Polycode.Vector2_crossProduct(this.__ptr, vec2)
}

Vector2.prototype.angle = function(vec2) {
	return Polycode.Vector2_angle(this.__ptr, vec2)
}

Vector2.prototype.Normalize = function() {
	Polycode.Vector2_Normalize(this.__ptr)
}
