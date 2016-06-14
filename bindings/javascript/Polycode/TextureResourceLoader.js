function TextureResourceLoader() {
}
Duktape.fin(TextureResourceLoader.prototype, function (x) {
	if (x === TextureResourceLoader.prototype) {
		return;
	}
	Polycode.TextureResourceLoader__delete(x.__ptr)
})

TextureResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new shared_ptr<Resource>()
	retVal.__ptr = Polycode.TextureResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
