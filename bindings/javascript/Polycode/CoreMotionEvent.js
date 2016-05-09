function CoreMotionEvent() {
	Object.defineProperties(this, {
		'amount': { enumerable: true, configurable: true, get: CoreMotionEvent.prototype.__get_amount, set: CoreMotionEvent.prototype.__set_amount}
	})
}
CoreMotionEvent.prototype.__get_amount = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.CoreMotionEvent__get_amount(this.__ptr)
	return retVal
}

CoreMotionEvent.prototype.__set_amount = function(val) {
	Polycode.CoreMotionEvent__set_amount(this.__ptr, val.__ptr)
}

