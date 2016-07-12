function ScriptInstance() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ScriptInstance()
	}
}


Duktape.fin(ScriptInstance.prototype, function (x) {
	if (x === ScriptInstance.prototype) {
		return;
	}
	Polycode.ScriptInstance__delete(x.__ptr)
})
