function MouseEventResult() {
	Object.defineProperties(this, {
		'hit': { enumerable: true, configurable: true, get: MouseEventResult.prototype.__get_hit, set: MouseEventResult.prototype.__set_hit},
		'blocked': { enumerable: true, configurable: true, get: MouseEventResult.prototype.__get_blocked, set: MouseEventResult.prototype.__set_blocked}
	})
}
MouseEventResult.prototype.__get_hit = function() {
	return Polycode.MouseEventResult__get_hit(this.__ptr)
}

MouseEventResult.prototype.__set_hit = function(val) {
	Polycode.MouseEventResult__set_hit(this.__ptr, val)
}

MouseEventResult.prototype.__get_blocked = function() {
	return Polycode.MouseEventResult__get_blocked(this.__ptr)
}

MouseEventResult.prototype.__set_blocked = function(val) {
	Polycode.MouseEventResult__set_blocked(this.__ptr, val)
}

Duktape.fin(MouseEventResult.prototype, function (x) {
	if (x === MouseEventResult.prototype) {
		return;
	}
	Polycode.MouseEventResult__delete(x.__ptr)
})
