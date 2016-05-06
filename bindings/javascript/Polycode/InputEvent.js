function InputEvent() {
}

InputEvent.prototype.getMousePosition = function() {
	Polycode.InputEvent_getMousePosition(this.__ptr)
}

InputEvent.prototype.getKey = function() {
	Polycode.InputEvent_getKey(this.__ptr)
}

InputEvent.prototype.getMouseButton = function() {
	Polycode.InputEvent_getMouseButton(this.__ptr)
}

InputEvent.prototype.getCharCode = function() {
	Polycode.InputEvent_getCharCode(this.__ptr)
}

InputEvent.prototype.keyCode = function() {
	Polycode.InputEvent_keyCode(this.__ptr)
}
