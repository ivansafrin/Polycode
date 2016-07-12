function TextureResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.TextureResourceLoader()
	}
}


Duktape.fin(TextureResourceLoader.prototype, function (x) {
	if (x === TextureResourceLoader.prototype) {
		return;
	}
	Polycode.TextureResourceLoader__delete(x.__ptr)
})
