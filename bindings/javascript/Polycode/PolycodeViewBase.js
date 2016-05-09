function PolycodeViewBase() {
	Object.defineProperties(this, {
		'windowData': { enumerable: true, configurable: true, get: PolycodeViewBase.prototype.__get_windowData, set: PolycodeViewBase.prototype.__set_windowData},
		'resizable': { enumerable: true, configurable: true, get: PolycodeViewBase.prototype.__get_resizable, set: PolycodeViewBase.prototype.__set_resizable}
	})
}
PolycodeViewBase.prototype.__get_windowData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.PolycodeViewBase__get_windowData(this.__ptr)
	return retVal
}

PolycodeViewBase.prototype.__set_windowData = function(val) {
	Polycode.PolycodeViewBase__set_windowData(this.__ptr, val.__ptr)
}

PolycodeViewBase.prototype.__get_resizable = function() {
	return Polycode.PolycodeViewBase__get_resizable(this.__ptr)
}

PolycodeViewBase.prototype.__set_resizable = function(val) {
	Polycode.PolycodeViewBase__set_resizable(this.__ptr, val)
}

