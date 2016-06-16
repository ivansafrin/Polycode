function ColorRange(color,rangeStart,rangeEnd) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ColorRange(color,rangeStart,rangeEnd)
	}
	Object.defineProperties(this, {
		'color': { enumerable: true, configurable: true, get: ColorRange.prototype.__get_color, set: ColorRange.prototype.__set_color},
		'rangeStart': { enumerable: true, configurable: true, get: ColorRange.prototype.__get_rangeStart, set: ColorRange.prototype.__set_rangeStart},
		'rangeEnd': { enumerable: true, configurable: true, get: ColorRange.prototype.__get_rangeEnd, set: ColorRange.prototype.__set_rangeEnd}
	})
}

ColorRange.prototype.__get_color = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.ColorRange__get_color(this.__ptr)
	return retVal
}

ColorRange.prototype.__set_color = function(val) {
	Polycode.ColorRange__set_color(this.__ptr, val.__ptr)
}

ColorRange.prototype.__get_rangeStart = function() {
	return Polycode.ColorRange__get_rangeStart(this.__ptr)
}

ColorRange.prototype.__set_rangeStart = function(val) {
	Polycode.ColorRange__set_rangeStart(this.__ptr, val)
}

ColorRange.prototype.__get_rangeEnd = function() {
	return Polycode.ColorRange__get_rangeEnd(this.__ptr)
}

ColorRange.prototype.__set_rangeEnd = function(val) {
	Polycode.ColorRange__set_rangeEnd(this.__ptr, val)
}

Duktape.fin(ColorRange.prototype, function (x) {
	if (x === ColorRange.prototype) {
		return;
	}
	Polycode.ColorRange__delete(x.__ptr)
})
