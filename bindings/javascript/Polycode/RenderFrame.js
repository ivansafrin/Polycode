function RenderFrame(viewport) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.RenderFrame(viewport)
	}
	Object.defineProperties(this, {
		'viewport': { enumerable: true, configurable: true, get: RenderFrame.prototype.__get_viewport, set: RenderFrame.prototype.__set_viewport}
	})
}


RenderFrame.prototype.__get_viewport = function() {
	var retVal = new Rectangle("__skip_ptr__")
	retVal.__ptr = 	Polycode.RenderFrame__get_viewport(this.__ptr)
	return retVal
}

RenderFrame.prototype.__set_viewport = function(val) {
	Polycode.RenderFrame__set_viewport(this.__ptr, val.__ptr)
}

Duktape.fin(RenderFrame.prototype, function (x) {
	if (x === RenderFrame.prototype) {
		return;
	}
	Polycode.RenderFrame__delete(x.__ptr)
})
