require('Polycode/Event')

function CoreMotionEvent() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.CoreMotionEvent()
	}
	Object.defineProperties(this, {
		'amount': { enumerable: true, configurable: true, get: CoreMotionEvent.prototype.__get_amount, set: CoreMotionEvent.prototype.__set_amount}
	})
}


CoreMotionEvent.prototype = Object.create(Event.prototype)

CoreMotionEvent.prototype.__get_amount = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.CoreMotionEvent__get_amount(this.__ptr)
	return retVal
}

CoreMotionEvent.prototype.__set_amount = function(val) {
	Polycode.CoreMotionEvent__set_amount(this.__ptr, val.__ptr)
}

Duktape.fin(CoreMotionEvent.prototype, function (x) {
	if (x === CoreMotionEvent.prototype) {
		return;
	}
	Polycode.CoreMotionEvent__delete(x.__ptr)
})
