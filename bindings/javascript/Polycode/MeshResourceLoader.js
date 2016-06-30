function MeshResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.MeshResourceLoader()
	}
}


Duktape.fin(MeshResourceLoader.prototype, function (x) {
	if (x === MeshResourceLoader.prototype) {
		return;
	}
	Polycode.MeshResourceLoader__delete(x.__ptr)
})

MeshResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.MeshResourceLoader_loadResource(this.__ptr, path, targetPool.__ptr)
	return retVal
}
