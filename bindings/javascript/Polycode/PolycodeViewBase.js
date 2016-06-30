function PolycodeViewBase() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.PolycodeViewBase()
	}
	Object.defineProperties(this, {
		'resizable': { enumerable: true, configurable: true, get: PolycodeViewBase.prototype.__get_resizable, set: PolycodeViewBase.prototype.__set_resizable}
	})
}


PolycodeViewBase.prototype.__get_resizable = function() {
	return Polycode.PolycodeViewBase__get_resizable(this.__ptr)
}

PolycodeViewBase.prototype.__set_resizable = function(val) {
	Polycode.PolycodeViewBase__set_resizable(this.__ptr, val)
}

Duktape.fin(PolycodeViewBase.prototype, function (x) {
	if (x === PolycodeViewBase.prototype) {
		return;
	}
	Polycode.PolycodeViewBase__delete(x.__ptr)
})
