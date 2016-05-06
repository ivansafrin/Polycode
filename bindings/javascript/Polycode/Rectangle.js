function Rectangle() {
}

Rectangle.prototype.setRect = function(x,y,w,h) {
	Polycode.Rectangle_setRect(this.__ptr, x,y,w,h)
}

Rectangle.prototype.Clipped = function(rect) {
	Polycode.Rectangle_Clipped(this.__ptr, rect)
}

Rectangle.prototype.minX = function() {
	Polycode.Rectangle_minX(this.__ptr)
}

Rectangle.prototype.maxX = function() {
	Polycode.Rectangle_maxX(this.__ptr)
}

Rectangle.prototype.minY = function() {
	Polycode.Rectangle_minY(this.__ptr)
}

Rectangle.prototype.maxY = function() {
	Polycode.Rectangle_maxY(this.__ptr)
}
