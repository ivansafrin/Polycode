function FontResourceLoader() {
}

FontResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.FontResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
