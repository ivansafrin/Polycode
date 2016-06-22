function LightInfoBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.LightInfoBinding()
	}
}

Duktape.fin(LightInfoBinding.prototype, function (x) {
	if (x === LightInfoBinding.prototype) {
		return;
	}
	Polycode.LightInfoBinding__delete(x.__ptr)
})
