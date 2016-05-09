function RenderTargetBinding() {
	Object.defineProperties(this, {
		'id': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_id, set: RenderTargetBinding.prototype.__set_id},
		'name': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_name, set: RenderTargetBinding.prototype.__set_name},
		'mode': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_mode, set: RenderTargetBinding.prototype.__set_mode},
		'buffer': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_buffer, set: RenderTargetBinding.prototype.__set_buffer}
	})
}
RenderTargetBinding.prototype.__get_id = function() {
	return Polycode.RenderTargetBinding__get_id(this.__ptr)
}

RenderTargetBinding.prototype.__set_id = function(val) {
	Polycode.RenderTargetBinding__set_id(this.__ptr, val)
}

RenderTargetBinding.prototype.__get_name = function() {
	return Polycode.RenderTargetBinding__get_name(this.__ptr)
}

RenderTargetBinding.prototype.__set_name = function(val) {
	Polycode.RenderTargetBinding__set_name(this.__ptr, val)
}

RenderTargetBinding.prototype.__get_mode = function() {
	return Polycode.RenderTargetBinding__get_mode(this.__ptr)
}

RenderTargetBinding.prototype.__set_mode = function(val) {
	Polycode.RenderTargetBinding__set_mode(this.__ptr, val)
}

RenderTargetBinding.prototype.__get_buffer = function() {
	var retVal = new RenderBuffer()
	retVal.__ptr = 	Polycode.RenderTargetBinding__get_buffer(this.__ptr)
	return retVal
}

RenderTargetBinding.prototype.__set_buffer = function(val) {
	Polycode.RenderTargetBinding__set_buffer(this.__ptr, val.__ptr)
}

