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

TextureResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.TextureResourceLoader_loadResource(this.__ptr, path, targetPool.__ptr)
	return retVal
}
