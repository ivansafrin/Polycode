function ScriptResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ScriptResourceLoader()
	}
}


Duktape.fin(ScriptResourceLoader.prototype, function (x) {
	if (x === ScriptResourceLoader.prototype) {
		return;
	}
	Polycode.ScriptResourceLoader__delete(x.__ptr)
})

ScriptResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.ScriptResourceLoader_loadResource(this.__ptr, path, targetPool.__ptr)
	return retVal
}
