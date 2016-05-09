function ScriptResourceLoader() {
}

ScriptResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.ScriptResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
