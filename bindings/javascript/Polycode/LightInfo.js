function LightInfo() {
	Object.defineProperties(this, {
		'importance': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_importance, set: LightInfo.prototype.__set_importance},
		'position': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_position, set: LightInfo.prototype.__set_position},
		'direction': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_direction, set: LightInfo.prototype.__set_direction},
		'type': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_type, set: LightInfo.prototype.__set_type},
		'diffuseColor': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_diffuseColor, set: LightInfo.prototype.__set_diffuseColor},
		'specularColor': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_specularColor, set: LightInfo.prototype.__set_specularColor},
		'constantAttenuation': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_constantAttenuation, set: LightInfo.prototype.__set_constantAttenuation},
		'linearAttenuation': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_linearAttenuation, set: LightInfo.prototype.__set_linearAttenuation},
		'quadraticAttenuation': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_quadraticAttenuation, set: LightInfo.prototype.__set_quadraticAttenuation},
		'intensity': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_intensity, set: LightInfo.prototype.__set_intensity},
		'spotlightCutoff': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_spotlightCutoff, set: LightInfo.prototype.__set_spotlightCutoff},
		'spotlightExponent': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_spotlightExponent, set: LightInfo.prototype.__set_spotlightExponent},
		'shadowsEnabled': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_shadowsEnabled, set: LightInfo.prototype.__set_shadowsEnabled},
		'shadowMapTexture': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_shadowMapTexture, set: LightInfo.prototype.__set_shadowMapTexture},
		'lightViewMatrix': { enumerable: true, configurable: true, get: LightInfo.prototype.__get_lightViewMatrix, set: LightInfo.prototype.__set_lightViewMatrix}
	})
}
LightInfo.prototype.__get_importance = function() {
	return Polycode.LightInfo__get_importance(this.__ptr)
}

LightInfo.prototype.__set_importance = function(val) {
	Polycode.LightInfo__set_importance(this.__ptr, val)
}

LightInfo.prototype.__get_position = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.LightInfo__get_position(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_position = function(val) {
	Polycode.LightInfo__set_position(this.__ptr, val.__ptr)
}

LightInfo.prototype.__get_direction = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.LightInfo__get_direction(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_direction = function(val) {
	Polycode.LightInfo__set_direction(this.__ptr, val.__ptr)
}

LightInfo.prototype.__get_type = function() {
	return Polycode.LightInfo__get_type(this.__ptr)
}

LightInfo.prototype.__set_type = function(val) {
	Polycode.LightInfo__set_type(this.__ptr, val)
}

LightInfo.prototype.__get_diffuseColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.LightInfo__get_diffuseColor(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_diffuseColor = function(val) {
	Polycode.LightInfo__set_diffuseColor(this.__ptr, val.__ptr)
}

LightInfo.prototype.__get_specularColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.LightInfo__get_specularColor(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_specularColor = function(val) {
	Polycode.LightInfo__set_specularColor(this.__ptr, val.__ptr)
}

LightInfo.prototype.__get_constantAttenuation = function() {
	return Polycode.LightInfo__get_constantAttenuation(this.__ptr)
}

LightInfo.prototype.__set_constantAttenuation = function(val) {
	Polycode.LightInfo__set_constantAttenuation(this.__ptr, val)
}

LightInfo.prototype.__get_linearAttenuation = function() {
	return Polycode.LightInfo__get_linearAttenuation(this.__ptr)
}

LightInfo.prototype.__set_linearAttenuation = function(val) {
	Polycode.LightInfo__set_linearAttenuation(this.__ptr, val)
}

LightInfo.prototype.__get_quadraticAttenuation = function() {
	return Polycode.LightInfo__get_quadraticAttenuation(this.__ptr)
}

LightInfo.prototype.__set_quadraticAttenuation = function(val) {
	Polycode.LightInfo__set_quadraticAttenuation(this.__ptr, val)
}

LightInfo.prototype.__get_intensity = function() {
	return Polycode.LightInfo__get_intensity(this.__ptr)
}

LightInfo.prototype.__set_intensity = function(val) {
	Polycode.LightInfo__set_intensity(this.__ptr, val)
}

LightInfo.prototype.__get_spotlightCutoff = function() {
	return Polycode.LightInfo__get_spotlightCutoff(this.__ptr)
}

LightInfo.prototype.__set_spotlightCutoff = function(val) {
	Polycode.LightInfo__set_spotlightCutoff(this.__ptr, val)
}

LightInfo.prototype.__get_spotlightExponent = function() {
	return Polycode.LightInfo__get_spotlightExponent(this.__ptr)
}

LightInfo.prototype.__set_spotlightExponent = function(val) {
	Polycode.LightInfo__set_spotlightExponent(this.__ptr, val)
}

LightInfo.prototype.__get_shadowsEnabled = function() {
	return Polycode.LightInfo__get_shadowsEnabled(this.__ptr)
}

LightInfo.prototype.__set_shadowsEnabled = function(val) {
	Polycode.LightInfo__set_shadowsEnabled(this.__ptr, val)
}

LightInfo.prototype.__get_shadowMapTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = 	Polycode.LightInfo__get_shadowMapTexture(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_shadowMapTexture = function(val) {
	Polycode.LightInfo__set_shadowMapTexture(this.__ptr, val.__ptr)
}

LightInfo.prototype.__get_lightViewMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.LightInfo__get_lightViewMatrix(this.__ptr)
	return retVal
}

LightInfo.prototype.__set_lightViewMatrix = function(val) {
	Polycode.LightInfo__set_lightViewMatrix(this.__ptr, val.__ptr)
}

Duktape.fin(LightInfo.prototype, function (x) {
	if (x === LightInfo.prototype) {
		return;
	}
	Polycode.LightInfo__delete(x.__ptr)
})
