function RendererPlatformData() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RendererPlatformData()
	}
	Object.defineProperties(this, {
		'type': { enumerable: true, configurable: true, get: RendererPlatformData.prototype.__get_type, set: RendererPlatformData.prototype.__set_type}
	})
}

RendererPlatformData.PLATFORM_DATA_NONE = 0
RendererPlatformData.PLATFORM_DATA_TEXTURE = 1
RendererPlatformData.PLATFORM_DATA_RENDER_BUFFER = 2
RendererPlatformData.PLATFORM_DATA_PROGRAM = 3
RendererPlatformData.PLATFORM_DATA_SHADER = 4
RendererPlatformData.PLATFORM_DATA_SUBMESH = 5

RendererPlatformData.prototype.__get_type = function() {
	return Polycode.RendererPlatformData__get_type(this.__ptr)
}

RendererPlatformData.prototype.__set_type = function(val) {
	Polycode.RendererPlatformData__set_type(this.__ptr, val)
}

Duktape.fin(RendererPlatformData.prototype, function (x) {
	if (x === RendererPlatformData.prototype) {
		return;
	}
	Polycode.RendererPlatformData__delete(x.__ptr)
})
