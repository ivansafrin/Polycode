function ScriptInstance() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ScriptInstance()
	}
	Object.defineProperties(this, {
		'script': { enumerable: true, configurable: true, get: ScriptInstance.prototype.__get_script, set: ScriptInstance.prototype.__set_script}
	})
}

ScriptInstance.prototype.__get_script = function() {
	var retVal = new Script()
	retVal.__ptr = 	Polycode.ScriptInstance__get_script(this.__ptr)
	return retVal
}

ScriptInstance.prototype.__set_script = function(val) {
	Polycode.ScriptInstance__set_script(this.__ptr, val.__ptr)
}

Duktape.fin(ScriptInstance.prototype, function (x) {
	if (x === ScriptInstance.prototype) {
		return;
	}
	Polycode.ScriptInstance__delete(x.__ptr)
})
