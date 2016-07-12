function FontResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.FontResourceLoader()
	}
}


Duktape.fin(FontResourceLoader.prototype, function (x) {
	if (x === FontResourceLoader.prototype) {
		return;
	}
	Polycode.FontResourceLoader__delete(x.__ptr)
})
