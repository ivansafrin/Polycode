function MaterialResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.MaterialResourceLoader()
	}
}


Duktape.fin(MaterialResourceLoader.prototype, function (x) {
	if (x === MaterialResourceLoader.prototype) {
		return;
	}
	Polycode.MaterialResourceLoader__delete(x.__ptr)
})
