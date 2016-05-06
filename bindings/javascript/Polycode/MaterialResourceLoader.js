function MaterialResourceLoader() {
}

MaterialResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.MaterialResourceLoader_loadResource(this.__ptr, path,targetPool)
}
