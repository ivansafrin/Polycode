require('Polycode/Resource')

function Texture() {
	Object.defineProperties(this, {
		'clamp': { enumerable: true, configurable: true, get: Texture.prototype.__get_clamp, set: Texture.prototype.__set_clamp},
		'textureData': { enumerable: true, configurable: true, get: Texture.prototype.__get_textureData, set: Texture.prototype.__set_textureData},
		'type': { enumerable: true, configurable: true, get: Texture.prototype.__get_type, set: Texture.prototype.__set_type},
		'filteringMode': { enumerable: true, configurable: true, get: Texture.prototype.__get_filteringMode, set: Texture.prototype.__set_filteringMode},
		'createMipmaps': { enumerable: true, configurable: true, get: Texture.prototype.__get_createMipmaps, set: Texture.prototype.__set_createMipmaps},
		'anisotropy': { enumerable: true, configurable: true, get: Texture.prototype.__get_anisotropy, set: Texture.prototype.__set_anisotropy},
		'framebufferTexture': { enumerable: true, configurable: true, get: Texture.prototype.__get_framebufferTexture, set: Texture.prototype.__set_framebufferTexture},
		'depthTexture': { enumerable: true, configurable: true, get: Texture.prototype.__get_depthTexture, set: Texture.prototype.__set_depthTexture}
	})
}

Texture.FILTERING_NEAREST = 0
Texture.FILTERING_LINEAR = 1

Texture.prototype = Object.create(Resource.prototype)

Texture.prototype.__get_clamp = function() {
	return Polycode.Texture__get_clamp(this.__ptr)
}

Texture.prototype.__set_clamp = function(val) {
	Polycode.Texture__set_clamp(this.__ptr, val)
}

Texture.prototype.__get_textureData = function() {
	var retVal = new char()
	retVal.__ptr = 	Polycode.Texture__get_textureData(this.__ptr)
	return retVal
}

Texture.prototype.__set_textureData = function(val) {
	Polycode.Texture__set_textureData(this.__ptr, val.__ptr)
}

Texture.prototype.__get_type = function() {
	return Polycode.Texture__get_type(this.__ptr)
}

Texture.prototype.__set_type = function(val) {
	Polycode.Texture__set_type(this.__ptr, val)
}

Texture.prototype.__get_filteringMode = function() {
	return Polycode.Texture__get_filteringMode(this.__ptr)
}

Texture.prototype.__set_filteringMode = function(val) {
	Polycode.Texture__set_filteringMode(this.__ptr, val)
}

Texture.prototype.__get_createMipmaps = function() {
	return Polycode.Texture__get_createMipmaps(this.__ptr)
}

Texture.prototype.__set_createMipmaps = function(val) {
	Polycode.Texture__set_createMipmaps(this.__ptr, val)
}

Texture.prototype.__get_anisotropy = function() {
	return Polycode.Texture__get_anisotropy(this.__ptr)
}

Texture.prototype.__set_anisotropy = function(val) {
	Polycode.Texture__set_anisotropy(this.__ptr, val)
}

Texture.prototype.__get_framebufferTexture = function() {
	return Polycode.Texture__get_framebufferTexture(this.__ptr)
}

Texture.prototype.__set_framebufferTexture = function(val) {
	Polycode.Texture__set_framebufferTexture(this.__ptr, val)
}

Texture.prototype.__get_depthTexture = function() {
	return Polycode.Texture__get_depthTexture(this.__ptr)
}

Texture.prototype.__set_depthTexture = function(val) {
	Polycode.Texture__set_depthTexture(this.__ptr, val)
}


Texture.prototype.reloadResource = function() {
	Polycode.Texture_reloadResource(this.__ptr)
}

Texture.prototype.setImageData = function(data) {
	Polycode.Texture_setImageData(this.__ptr, data.__ptr)
}

Texture.prototype.getTextureData = function() {
	var retVal = new char()
	retVal.__ptr = Polycode.Texture_getTextureData(this.__ptr)
	return retVal
}

Texture.prototype.getWidth = function() {
	return Polycode.Texture_getWidth(this.__ptr)
}

Texture.prototype.getHeight = function() {
	return Polycode.Texture_getHeight(this.__ptr)
}

Texture.prototype.setCreateMipmaps = function(createMipmapsIn) {
	Polycode.Texture_setCreateMipmaps(this.__ptr, createMipmapsIn)
}

Texture.prototype.getCreateMipmaps = function() {
	return Polycode.Texture_getCreateMipmaps(this.__ptr)
}
