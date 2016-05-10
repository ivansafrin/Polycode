function CoreMutex() {
	Object.defineProperties(this, {
		'mutexID': { enumerable: true, configurable: true, get: CoreMutex.prototype.__get_mutexID, set: CoreMutex.prototype.__set_mutexID}
	})
}
CoreMutex.prototype.__get_mutexID = function() {
	return Polycode.CoreMutex__get_mutexID(this.__ptr)
}

CoreMutex.prototype.__set_mutexID = function(val) {
	Polycode.CoreMutex__set_mutexID(this.__ptr, val)
}

Duktape.fin(CoreMutex.prototype, function (x) {
	if (x === CoreMutex.prototype) {
		return;
	}
	Polycode.CoreMutex__delete(x.__ptr)
})

CoreMutex.prototype.lock = function() {
	Polycode.CoreMutex_lock(this.__ptr)
}

CoreMutex.prototype.unlock = function() {
	Polycode.CoreMutex_unlock(this.__ptr)
}
