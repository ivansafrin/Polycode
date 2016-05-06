function MeshResourceLoader() {
}

MeshResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.MeshResourceLoader_loadResource(this.__ptr, path,targetPool)
}
