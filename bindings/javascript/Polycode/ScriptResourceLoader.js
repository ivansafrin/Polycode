function ScriptResourceLoader() {
}

ScriptResourceLoader.prototype.loadResource = function(path,targetPool) {
	Polycode.ScriptResourceLoader_loadResource(this.__ptr, path,targetPool)
}
