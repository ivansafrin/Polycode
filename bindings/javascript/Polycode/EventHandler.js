function EventHandler() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.EventHandler()
	}
}


Duktape.fin(EventHandler.prototype, function (x) {
	if (x === EventHandler.prototype) {
		return;
	}
	Polycode.EventHandler__delete(x.__ptr)
})
