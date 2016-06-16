function Rotation() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Rotation()
	}
	Object.defineProperties(this, {
		'pitch': { enumerable: true, configurable: true, get: Rotation.prototype.__get_pitch, set: Rotation.prototype.__set_pitch},
		'yaw': { enumerable: true, configurable: true, get: Rotation.prototype.__get_yaw, set: Rotation.prototype.__set_yaw},
		'roll': { enumerable: true, configurable: true, get: Rotation.prototype.__get_roll, set: Rotation.prototype.__set_roll}
	})
}

Rotation.prototype.__get_pitch = function() {
	return Polycode.Rotation__get_pitch(this.__ptr)
}

Rotation.prototype.__set_pitch = function(val) {
	Polycode.Rotation__set_pitch(this.__ptr, val)
}

Rotation.prototype.__get_yaw = function() {
	return Polycode.Rotation__get_yaw(this.__ptr)
}

Rotation.prototype.__set_yaw = function(val) {
	Polycode.Rotation__set_yaw(this.__ptr, val)
}

Rotation.prototype.__get_roll = function() {
	return Polycode.Rotation__get_roll(this.__ptr)
}

Rotation.prototype.__set_roll = function(val) {
	Polycode.Rotation__set_roll(this.__ptr, val)
}

Duktape.fin(Rotation.prototype, function (x) {
	if (x === Rotation.prototype) {
		return;
	}
	Polycode.Rotation__delete(x.__ptr)
})
