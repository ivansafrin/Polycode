function JSScriptInstance() {
	Object.defineProperties(this, {
		'objectRef': { enumerable: true, configurable: true, get: JSScriptInstance.prototype.__get_objectRef, set: JSScriptInstance.prototype.__set_objectRef}
	})
}
JSScriptInstance.prototype.__get_objectRef = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.JSScriptInstance__get_objectRef(this.__ptr)
	return retVal
}

JSScriptInstance.prototype.__set_objectRef = function(val) {
	Polycode.JSScriptInstance__set_objectRef(this.__ptr, val.__ptr)
}

