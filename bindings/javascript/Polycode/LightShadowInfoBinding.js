function LightShadowInfoBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.LightShadowInfoBinding()
	}
}


Duktape.fin(LightShadowInfoBinding.prototype, function (x) {
	if (x === LightShadowInfoBinding.prototype) {
		return;
	}
	Polycode.LightShadowInfoBinding__delete(x.__ptr)
})
