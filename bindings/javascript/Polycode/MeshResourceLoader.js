function MeshResourceLoader() {
}

MeshResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.MeshResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
