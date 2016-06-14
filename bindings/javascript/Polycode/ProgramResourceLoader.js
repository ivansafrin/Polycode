function ProgramResourceLoader() {
}
Duktape.fin(ProgramResourceLoader.prototype, function (x) {
	if (x === ProgramResourceLoader.prototype) {
		return;
	}
	Polycode.ProgramResourceLoader__delete(x.__ptr)
})

ProgramResourceLoader.prototype.loadResource = function(path,targetPool) {
	var retVal = new shared_ptr<Resource>()
	retVal.__ptr = Polycode.ProgramResourceLoader_loadResource(this.__ptr, path,targetPool)
	return retVal
}
