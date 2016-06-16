function FontResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.FontResourceLoader()
	}
}

Duktape.fin(FontResourceLoader.prototype, function (x) {
	if (x === FontResourceLoader.prototype) {
		return;
	}
	Polycode.FontResourceLoader__delete(x.__ptr)
})

FontResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.FontResourceLoader_loadResource(this.__ptr, path, targetPool.__ptr)
	return retVal
}
