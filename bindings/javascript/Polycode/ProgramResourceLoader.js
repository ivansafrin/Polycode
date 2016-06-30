function ProgramResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ProgramResourceLoader()
	}
}


Duktape.fin(ProgramResourceLoader.prototype, function (x) {
	if (x === ProgramResourceLoader.prototype) {
		return;
	}
	Polycode.ProgramResourceLoader__delete(x.__ptr)
})

ProgramResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new Resource()
	retVal.__ptr = Polycode.ProgramResourceLoader_loadResource(this.__ptr, path, targetPool.__ptr)
	return retVal
}
