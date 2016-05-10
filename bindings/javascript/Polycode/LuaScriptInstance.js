function LuaScriptInstance() {
	Object.defineProperties(this, {
		'tableRef': { enumerable: true, configurable: true, get: LuaScriptInstance.prototype.__get_tableRef, set: LuaScriptInstance.prototype.__set_tableRef}
	})
}
LuaScriptInstance.prototype.__get_tableRef = function() {
	return Polycode.LuaScriptInstance__get_tableRef(this.__ptr)
}

LuaScriptInstance.prototype.__set_tableRef = function(val) {
	Polycode.LuaScriptInstance__set_tableRef(this.__ptr, val)
}

Duktape.fin(LuaScriptInstance.prototype, function (x) {
	if (x === LuaScriptInstance.prototype) {
		return;
	}
	Polycode.LuaScriptInstance__delete(x.__ptr)
})
