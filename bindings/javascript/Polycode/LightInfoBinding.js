function LightInfoBinding() {
}
Duktape.fin(LightInfoBinding.prototype, function (x) {
	if (x === LightInfoBinding.prototype) {
		return;
	}
	Polycode.LightInfoBinding__delete(x.__ptr)
})
