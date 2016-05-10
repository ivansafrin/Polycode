function RenderFrame() {
}
Duktape.fin(RenderFrame.prototype, function (x) {
	if (x === RenderFrame.prototype) {
		return;
	}
	Polycode.RenderFrame__delete(x.__ptr)
})
