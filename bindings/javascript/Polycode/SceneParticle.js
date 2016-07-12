function SceneParticle() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneParticle()
	}
	Object.defineProperties(this, {
		'lifetime': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_lifetime, set: SceneParticle.prototype.__set_lifetime},
		'position': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_position, set: SceneParticle.prototype.__set_position},
		'velocity': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_velocity, set: SceneParticle.prototype.__set_velocity},
		'perlinPos': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_perlinPos, set: SceneParticle.prototype.__set_perlinPos},
		'rotation': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_rotation, set: SceneParticle.prototype.__set_rotation},
		'brightnessDeviation': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_brightnessDeviation, set: SceneParticle.prototype.__set_brightnessDeviation},
		'scale': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_scale, set: SceneParticle.prototype.__set_scale},
		'color': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_color, set: SceneParticle.prototype.__set_color},
		'varianceIndex': { enumerable: true, configurable: true, get: SceneParticle.prototype.__get_varianceIndex, set: SceneParticle.prototype.__set_varianceIndex}
	})
}


SceneParticle.prototype.__get_lifetime = function() {
	return Polycode.SceneParticle__get_lifetime(this.__ptr)
}

SceneParticle.prototype.__set_lifetime = function(val) {
	Polycode.SceneParticle__set_lifetime(this.__ptr, val)
}

SceneParticle.prototype.__get_position = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.SceneParticle__get_position(this.__ptr)
	return retVal
}

SceneParticle.prototype.__set_position = function(val) {
	Polycode.SceneParticle__set_position(this.__ptr, val.__ptr)
}

SceneParticle.prototype.__get_velocity = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.SceneParticle__get_velocity(this.__ptr)
	return retVal
}

SceneParticle.prototype.__set_velocity = function(val) {
	Polycode.SceneParticle__set_velocity(this.__ptr, val.__ptr)
}

SceneParticle.prototype.__get_perlinPos = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.SceneParticle__get_perlinPos(this.__ptr)
	return retVal
}

SceneParticle.prototype.__set_perlinPos = function(val) {
	Polycode.SceneParticle__set_perlinPos(this.__ptr, val.__ptr)
}

SceneParticle.prototype.__get_rotation = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.SceneParticle__get_rotation(this.__ptr)
	return retVal
}

SceneParticle.prototype.__set_rotation = function(val) {
	Polycode.SceneParticle__set_rotation(this.__ptr, val.__ptr)
}

SceneParticle.prototype.__get_brightnessDeviation = function() {
	return Polycode.SceneParticle__get_brightnessDeviation(this.__ptr)
}

SceneParticle.prototype.__set_brightnessDeviation = function(val) {
	Polycode.SceneParticle__set_brightnessDeviation(this.__ptr, val)
}

SceneParticle.prototype.__get_scale = function() {
	return Polycode.SceneParticle__get_scale(this.__ptr)
}

SceneParticle.prototype.__set_scale = function(val) {
	Polycode.SceneParticle__set_scale(this.__ptr, val)
}

SceneParticle.prototype.__get_color = function() {
	var retVal = new Color("__skip_ptr__")
	retVal.__ptr = 	Polycode.SceneParticle__get_color(this.__ptr)
	return retVal
}

SceneParticle.prototype.__set_color = function(val) {
	Polycode.SceneParticle__set_color(this.__ptr, val.__ptr)
}

SceneParticle.prototype.__get_varianceIndex = function() {
	return Polycode.SceneParticle__get_varianceIndex(this.__ptr)
}

SceneParticle.prototype.__set_varianceIndex = function(val) {
	Polycode.SceneParticle__set_varianceIndex(this.__ptr, val)
}

Duktape.fin(SceneParticle.prototype, function (x) {
	if (x === SceneParticle.prototype) {
		return;
	}
	Polycode.SceneParticle__delete(x.__ptr)
})
