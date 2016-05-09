function LightInfoBinding() {
	Object.defineProperties(this, {
		'position': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_position, set: LightInfoBinding.prototype.__set_position},
		'direction': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_direction, set: LightInfoBinding.prototype.__set_direction},
		'specular': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_specular, set: LightInfoBinding.prototype.__set_specular},
		'diffuse': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_diffuse, set: LightInfoBinding.prototype.__set_diffuse},
		'spotExponent': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_spotExponent, set: LightInfoBinding.prototype.__set_spotExponent},
		'spotCosCutoff': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_spotCosCutoff, set: LightInfoBinding.prototype.__set_spotCosCutoff},
		'constantAttenuation': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_constantAttenuation, set: LightInfoBinding.prototype.__set_constantAttenuation},
		'linearAttenuation': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_linearAttenuation, set: LightInfoBinding.prototype.__set_linearAttenuation},
		'quadraticAttenuation': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_quadraticAttenuation, set: LightInfoBinding.prototype.__set_quadraticAttenuation},
		'shadowEnabled': { enumerable: true, configurable: true, get: LightInfoBinding.prototype.__get_shadowEnabled, set: LightInfoBinding.prototype.__set_shadowEnabled}
	})
}
LightInfoBinding.prototype.__get_position = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_position(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_position = function(val) {
	Polycode.LightInfoBinding__set_position(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_direction = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_direction(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_direction = function(val) {
	Polycode.LightInfoBinding__set_direction(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_specular = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_specular(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_specular = function(val) {
	Polycode.LightInfoBinding__set_specular(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_diffuse = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_diffuse(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_diffuse = function(val) {
	Polycode.LightInfoBinding__set_diffuse(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_spotExponent = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_spotExponent(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_spotExponent = function(val) {
	Polycode.LightInfoBinding__set_spotExponent(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_spotCosCutoff = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_spotCosCutoff(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_spotCosCutoff = function(val) {
	Polycode.LightInfoBinding__set_spotCosCutoff(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_constantAttenuation = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_constantAttenuation(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_constantAttenuation = function(val) {
	Polycode.LightInfoBinding__set_constantAttenuation(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_linearAttenuation = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_linearAttenuation(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_linearAttenuation = function(val) {
	Polycode.LightInfoBinding__set_linearAttenuation(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_quadraticAttenuation = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_quadraticAttenuation(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_quadraticAttenuation = function(val) {
	Polycode.LightInfoBinding__set_quadraticAttenuation(this.__ptr, val.__ptr)
}

LightInfoBinding.prototype.__get_shadowEnabled = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightInfoBinding__get_shadowEnabled(this.__ptr)
	return retVal
}

LightInfoBinding.prototype.__set_shadowEnabled = function(val) {
	Polycode.LightInfoBinding__set_shadowEnabled(this.__ptr, val.__ptr)
}

