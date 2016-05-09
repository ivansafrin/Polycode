function ProgramResourceLoader() {
}

ProgramResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.ProgramResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
