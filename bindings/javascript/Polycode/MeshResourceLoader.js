function MeshResourceLoader() {
}
Duktape.fin(MeshResourceLoader.prototype, function (x) {
	if (x === MeshResourceLoader.prototype) {
		return;
	}
	Polycode.MeshResourceLoader__delete(x.__ptr)
})

MeshResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new shared_ptr<Resource>()
	retVal.__ptr = Polycode.MeshResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
