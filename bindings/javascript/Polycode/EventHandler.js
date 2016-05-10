function EventHandler() {
}
Duktape.fin(EventHandler.prototype, function (x) {
	if (x === EventHandler.prototype) {
		return;
	}
	Polycode.EventHandler__delete(x.__ptr)
})
