function ProgramResourceLoader() {
}

ProgramResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.ProgramResourceLoader_loadResource(this.__ptr, path,targetPool)
}
