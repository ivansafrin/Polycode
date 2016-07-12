function MeshResourceLoader() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.MeshResourceLoader()
	}
}


Duktape.fin(MeshResourceLoader.prototype, function (x) {
	if (x === MeshResourceLoader.prototype) {
		return;
	}
	Polycode.MeshResourceLoader__delete(x.__ptr)
})
