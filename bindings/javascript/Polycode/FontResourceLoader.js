function FontResourceLoader() {
}

FontResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.FontResourceLoader_loadResource(this.__ptr, path,targetPool)
}
