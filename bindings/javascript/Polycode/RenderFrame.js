function RenderFrame() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderFrame()
	}
}


Duktape.fin(RenderFrame.prototype, function (x) {
	if (x === RenderFrame.prototype) {
		return;
	}
	Polycode.RenderFrame__delete(x.__ptr)
})
