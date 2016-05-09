function JoystickInfo() {
	Object.defineProperties(this, {
		'deviceID': { enumerable: true, configurable: true, get: JoystickInfo.prototype.__get_deviceID, set: JoystickInfo.prototype.__set_deviceID},
		'deviceIndex': { enumerable: true, configurable: true, get: JoystickInfo.prototype.__get_deviceIndex, set: JoystickInfo.prototype.__set_deviceIndex}
	})
}
JoystickInfo.prototype.__get_deviceID = function() {
	return Polycode.JoystickInfo__get_deviceID(this.__ptr)
}

JoystickInfo.prototype.__set_deviceID = function(val) {
	Polycode.JoystickInfo__set_deviceID(this.__ptr, val)
}

JoystickInfo.prototype.__get_deviceIndex = function() {
	return Polycode.JoystickInfo__get_deviceIndex(this.__ptr)
}

JoystickInfo.prototype.__set_deviceIndex = function(val) {
	Polycode.JoystickInfo__set_deviceIndex(this.__ptr, val)
}

