function CoreMutex() {
}

CoreMutex.prototype.lock = function() {
	Polycode.CoreMutex_lock(this.__ptr)
}

CoreMutex.prototype.unlock = function() {
	Polycode.CoreMutex_unlock(this.__ptr)
}
