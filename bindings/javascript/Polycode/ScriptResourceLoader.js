function ScriptResourceLoader() {
}
Duktape.fin(ScriptResourceLoader.prototype, function (x) {
	if (x === ScriptResourceLoader.prototype) {
		return;
	}
	Polycode.ScriptResourceLoader__delete(x.__ptr)
})

ScriptResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new shared_ptr<Resource>()
	retVal.__ptr = Polycode.ScriptResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
