function RenderTargetBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderTargetBinding()
	}
	Object.defineProperties(this, {
		'id': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_id, set: RenderTargetBinding.prototype.__set_id},
		'name': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_name, set: RenderTargetBinding.prototype.__set_name},
		'mode': { enumerable: true, configurable: true, get: RenderTargetBinding.prototype.__get_mode, set: RenderTargetBinding.prototype.__set_mode}
	})
}

RenderTargetBinding.MODE_IN = 0
RenderTargetBinding.MODE_OUT = 1
RenderTargetBinding.MODE_COLOR = 2
RenderTargetBinding.MODE_DEPTH = 3

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

Duktape.fin(RenderTargetBinding.prototype, function (x) {
	if (x === RenderTargetBinding.prototype) {
		return;
	}
	Polycode.RenderTargetBinding__delete(x.__ptr)
})
