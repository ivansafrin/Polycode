function MaterialResourceLoader() {
}
Duktape.fin(MaterialResourceLoader.prototype, function (x) {
	if (x === MaterialResourceLoader.prototype) {
		return;
	}
	Polycode.MaterialResourceLoader__delete(x.__ptr)
})

MaterialResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.MaterialResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
