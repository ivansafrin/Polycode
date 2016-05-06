function TextureResourceLoader() {
}

TextureResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.TextureResourceLoader_loadResource(this.__ptr, path,targetPool)
}
