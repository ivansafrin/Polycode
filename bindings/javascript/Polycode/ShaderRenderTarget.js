function ShaderRenderTarget() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ShaderRenderTarget()
	}
	Object.defineProperties(this, {
		'id': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_id, set: ShaderRenderTarget.prototype.__set_id},
		'width': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_width, set: ShaderRenderTarget.prototype.__set_width},
		'height': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_height, set: ShaderRenderTarget.prototype.__set_height},
		'sizeMode': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_sizeMode, set: ShaderRenderTarget.prototype.__set_sizeMode},
		'normalizedWidth': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_normalizedWidth, set: ShaderRenderTarget.prototype.__set_normalizedWidth},
		'normalizedHeight': { enumerable: true, configurable: true, get: ShaderRenderTarget.prototype.__get_normalizedHeight, set: ShaderRenderTarget.prototype.__set_normalizedHeight}
	})
}

ShaderRenderTarget.prototype.__get_id = function() {
	return Polycode.ShaderRenderTarget__get_id(this.__ptr)
}

ShaderRenderTarget.prototype.__set_id = function(val) {
	Polycode.ShaderRenderTarget__set_id(this.__ptr, val)
}

ShaderRenderTarget.prototype.__get_width = function() {
	return Polycode.ShaderRenderTarget__get_width(this.__ptr)
}

ShaderRenderTarget.prototype.__set_width = function(val) {
	Polycode.ShaderRenderTarget__set_width(this.__ptr, val)
}

ShaderRenderTarget.prototype.__get_height = function() {
	return Polycode.ShaderRenderTarget__get_height(this.__ptr)
}

ShaderRenderTarget.prototype.__set_height = function(val) {
	Polycode.ShaderRenderTarget__set_height(this.__ptr, val)
}

ShaderRenderTarget.prototype.__get_sizeMode = function() {
	return Polycode.ShaderRenderTarget__get_sizeMode(this.__ptr)
}

ShaderRenderTarget.prototype.__set_sizeMode = function(val) {
	Polycode.ShaderRenderTarget__set_sizeMode(this.__ptr, val)
}

ShaderRenderTarget.prototype.__get_normalizedWidth = function() {
	return Polycode.ShaderRenderTarget__get_normalizedWidth(this.__ptr)
}

ShaderRenderTarget.prototype.__set_normalizedWidth = function(val) {
	Polycode.ShaderRenderTarget__set_normalizedWidth(this.__ptr, val)
}

ShaderRenderTarget.prototype.__get_normalizedHeight = function() {
	return Polycode.ShaderRenderTarget__get_normalizedHeight(this.__ptr)
}

ShaderRenderTarget.prototype.__set_normalizedHeight = function(val) {
	Polycode.ShaderRenderTarget__set_normalizedHeight(this.__ptr, val)
}

Duktape.fin(ShaderRenderTarget.prototype, function (x) {
	if (x === ShaderRenderTarget.prototype) {
		return;
	}
	Polycode.ShaderRenderTarget__delete(x.__ptr)
})
