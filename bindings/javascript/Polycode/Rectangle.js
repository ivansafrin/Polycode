function Rectangle() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Rectangle()
	}
	Object.defineProperties(this, {
		'x': { enumerable: true, configurable: true, get: Rectangle.prototype.__get_x, set: Rectangle.prototype.__set_x},
		'y': { enumerable: true, configurable: true, get: Rectangle.prototype.__get_y, set: Rectangle.prototype.__set_y},
		'w': { enumerable: true, configurable: true, get: Rectangle.prototype.__get_w, set: Rectangle.prototype.__set_w},
		'h': { enumerable: true, configurable: true, get: Rectangle.prototype.__get_h, set: Rectangle.prototype.__set_h}
	})
}


Rectangle.prototype.__get_x = function() {
	return Polycode.Rectangle__get_x(this.__ptr)
}

Rectangle.prototype.__set_x = function(val) {
	Polycode.Rectangle__set_x(this.__ptr, val)
}

Rectangle.prototype.__get_y = function() {
	return Polycode.Rectangle__get_y(this.__ptr)
}

Rectangle.prototype.__set_y = function(val) {
	Polycode.Rectangle__set_y(this.__ptr, val)
}

Rectangle.prototype.__get_w = function() {
	return Polycode.Rectangle__get_w(this.__ptr)
}

Rectangle.prototype.__set_w = function(val) {
	Polycode.Rectangle__set_w(this.__ptr, val)
}

Rectangle.prototype.__get_h = function() {
	return Polycode.Rectangle__get_h(this.__ptr)
}

Rectangle.prototype.__set_h = function(val) {
	Polycode.Rectangle__set_h(this.__ptr, val)
}

Duktape.fin(Rectangle.prototype, function (x) {
	if (x === Rectangle.prototype) {
		return;
	}
	Polycode.Rectangle__delete(x.__ptr)
})

Rectangle.prototype.setRect = function(x,y,w,h) {
	Polycode.Rectangle_setRect(this.__ptr, x, y, w, h)
}

Rectangle.prototype.Clipped = function(rect) {
	var retVal = new Rectangle("__skip_ptr__")
	retVal.__ptr = Polycode.Rectangle_Clipped(this.__ptr, rect)
	return retVal
}

Rectangle.prototype.minX = function() {
	return Polycode.Rectangle_minX(this.__ptr)
}

Rectangle.prototype.maxX = function() {
	return Polycode.Rectangle_maxX(this.__ptr)
}

Rectangle.prototype.minY = function() {
	return Polycode.Rectangle_minY(this.__ptr)
}

Rectangle.prototype.maxY = function() {
	return Polycode.Rectangle_maxY(this.__ptr)
}
