require('Polycode/Event')

function InputEvent() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.InputEvent()
	}
	Object.defineProperties(this, {
		'mouseButton': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_mouseButton, set: InputEvent.prototype.__set_mouseButton},
		'mousePosition': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_mousePosition, set: InputEvent.prototype.__set_mousePosition},
		'key': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_key, set: InputEvent.prototype.__set_key},
		'timestamp': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_timestamp, set: InputEvent.prototype.__set_timestamp},
		'text': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_text, set: InputEvent.prototype.__set_text},
		'touch': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_touch, set: InputEvent.prototype.__set_touch},
		'touchType': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_touchType, set: InputEvent.prototype.__set_touchType},
		'joystickDeviceID': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_joystickDeviceID, set: InputEvent.prototype.__set_joystickDeviceID},
		'joystickAxisValue': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_joystickAxisValue, set: InputEvent.prototype.__set_joystickAxisValue},
		'joystickButton': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_joystickButton, set: InputEvent.prototype.__set_joystickButton},
		'joystickAxis': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_joystickAxis, set: InputEvent.prototype.__set_joystickAxis},
		'joystickIndex': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_joystickIndex, set: InputEvent.prototype.__set_joystickIndex},
		'hitDistance': { enumerable: true, configurable: true, get: InputEvent.prototype.__get_hitDistance, set: InputEvent.prototype.__set_hitDistance}
	})
}

InputEvent.prototype = Object.create(Event.prototype);

InputEvent.prototype.__get_mouseButton = function() {
	return Polycode.InputEvent__get_mouseButton(this.__ptr)
}

InputEvent.prototype.__set_mouseButton = function(val) {
	Polycode.InputEvent__set_mouseButton(this.__ptr, val)
}

InputEvent.prototype.__get_mousePosition = function() {
	var retVal = new Vector2()
	retVal.__ptr = 	Polycode.InputEvent__get_mousePosition(this.__ptr)
	return retVal
}

InputEvent.prototype.__set_mousePosition = function(val) {
	Polycode.InputEvent__set_mousePosition(this.__ptr, val.__ptr)
}

InputEvent.prototype.__get_key = function() {
	return Polycode.InputEvent__get_key(this.__ptr)
}

InputEvent.prototype.__set_key = function(val) {
	Polycode.InputEvent__set_key(this.__ptr, val)
}

InputEvent.prototype.__get_timestamp = function() {
	return Polycode.InputEvent__get_timestamp(this.__ptr)
}

InputEvent.prototype.__set_timestamp = function(val) {
	Polycode.InputEvent__set_timestamp(this.__ptr, val)
}

InputEvent.prototype.__get_text = function() {
	return Polycode.InputEvent__get_text(this.__ptr)
}

InputEvent.prototype.__set_text = function(val) {
	Polycode.InputEvent__set_text(this.__ptr, val)
}

InputEvent.prototype.__get_touch = function() {
	var retVal = new TouchInfo()
	retVal.__ptr = 	Polycode.InputEvent__get_touch(this.__ptr)
	return retVal
}

InputEvent.prototype.__set_touch = function(val) {
	Polycode.InputEvent__set_touch(this.__ptr, val.__ptr)
}

InputEvent.prototype.__get_touchType = function() {
	return Polycode.InputEvent__get_touchType(this.__ptr)
}

InputEvent.prototype.__set_touchType = function(val) {
	Polycode.InputEvent__set_touchType(this.__ptr, val)
}

InputEvent.prototype.__get_joystickDeviceID = function() {
	return Polycode.InputEvent__get_joystickDeviceID(this.__ptr)
}

InputEvent.prototype.__set_joystickDeviceID = function(val) {
	Polycode.InputEvent__set_joystickDeviceID(this.__ptr, val)
}

InputEvent.prototype.__get_joystickAxisValue = function() {
	return Polycode.InputEvent__get_joystickAxisValue(this.__ptr)
}

InputEvent.prototype.__set_joystickAxisValue = function(val) {
	Polycode.InputEvent__set_joystickAxisValue(this.__ptr, val)
}

InputEvent.prototype.__get_joystickButton = function() {
	return Polycode.InputEvent__get_joystickButton(this.__ptr)
}

InputEvent.prototype.__set_joystickButton = function(val) {
	Polycode.InputEvent__set_joystickButton(this.__ptr, val)
}

InputEvent.prototype.__get_joystickAxis = function() {
	return Polycode.InputEvent__get_joystickAxis(this.__ptr)
}

InputEvent.prototype.__set_joystickAxis = function(val) {
	Polycode.InputEvent__set_joystickAxis(this.__ptr, val)
}

InputEvent.prototype.__get_joystickIndex = function() {
	return Polycode.InputEvent__get_joystickIndex(this.__ptr)
}

InputEvent.prototype.__set_joystickIndex = function(val) {
	Polycode.InputEvent__set_joystickIndex(this.__ptr, val)
}

InputEvent.prototype.__get_hitDistance = function() {
	return Polycode.InputEvent__get_hitDistance(this.__ptr)
}

InputEvent.prototype.__set_hitDistance = function(val) {
	Polycode.InputEvent__set_hitDistance(this.__ptr, val)
}

Duktape.fin(InputEvent.prototype, function (x) {
	if (x === InputEvent.prototype) {
		return;
	}
	Polycode.InputEvent__delete(x.__ptr)
})

InputEvent.prototype.getMousePosition = function() {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.InputEvent_getMousePosition(this.__ptr)
	return retVal
}

InputEvent.prototype.getKey = function() {
	return Polycode.InputEvent_getKey(this.__ptr)
}

InputEvent.prototype.getMouseButton = function() {
	return Polycode.InputEvent_getMouseButton(this.__ptr)
}

InputEvent.prototype.keyCode = function() {
	return Polycode.InputEvent_keyCode(this.__ptr)
}
