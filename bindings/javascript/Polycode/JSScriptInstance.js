function JSScriptInstance() {
}
Duktape.fin(JSScriptInstance.prototype, function (x) {
	if (x === JSScriptInstance.prototype) {
		return;
	}
	Polycode.JSScriptInstance__delete(x.__ptr)
})
