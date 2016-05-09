function MaterialResourceLoader() {
}

MaterialResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.MaterialResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
