require('Polycode/EventDispatcher')

function CoreInput() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.CoreInput()
	}
	Object.defineProperties(this, {
		'simulateTouchWithMouse': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_simulateTouchWithMouse, set: CoreInput.prototype.__set_simulateTouchWithMouse},
		'simulateTouchAsPen': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_simulateTouchAsPen, set: CoreInput.prototype.__set_simulateTouchAsPen},
		'simulateMouseWithTouch': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_simulateMouseWithTouch, set: CoreInput.prototype.__set_simulateMouseWithTouch},
		'keyRepeat': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_keyRepeat, set: CoreInput.prototype.__set_keyRepeat},
		'mousePosition': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_mousePosition, set: CoreInput.prototype.__set_mousePosition},
		'deltaMousePosition': { enumerable: true, configurable: true, get: CoreInput.prototype.__get_deltaMousePosition, set: CoreInput.prototype.__set_deltaMousePosition}
	})
}

CoreInput.MOUSE_BUTTON1 = 0
CoreInput.MOUSE_BUTTON2 = 1
CoreInput.MOUSE_BUTTON3 = 2

CoreInput.prototype = Object.create(EventDispatcher.prototype)

CoreInput.prototype.__get_simulateTouchWithMouse = function() {
	return Polycode.CoreInput__get_simulateTouchWithMouse(this.__ptr)
}

CoreInput.prototype.__set_simulateTouchWithMouse = function(val) {
	Polycode.CoreInput__set_simulateTouchWithMouse(this.__ptr, val)
}

CoreInput.prototype.__get_simulateTouchAsPen = function() {
	return Polycode.CoreInput__get_simulateTouchAsPen(this.__ptr)
}

CoreInput.prototype.__set_simulateTouchAsPen = function(val) {
	Polycode.CoreInput__set_simulateTouchAsPen(this.__ptr, val)
}

CoreInput.prototype.__get_simulateMouseWithTouch = function() {
	return Polycode.CoreInput__get_simulateMouseWithTouch(this.__ptr)
}

CoreInput.prototype.__set_simulateMouseWithTouch = function(val) {
	Polycode.CoreInput__set_simulateMouseWithTouch(this.__ptr, val)
}

CoreInput.prototype.__get_keyRepeat = function() {
	return Polycode.CoreInput__get_keyRepeat(this.__ptr)
}

CoreInput.prototype.__set_keyRepeat = function(val) {
	Polycode.CoreInput__set_keyRepeat(this.__ptr, val)
}

CoreInput.prototype.__get_mousePosition = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = 	Polycode.CoreInput__get_mousePosition(this.__ptr)
	return retVal
}

CoreInput.prototype.__set_mousePosition = function(val) {
	Polycode.CoreInput__set_mousePosition(this.__ptr, val.__ptr)
}

CoreInput.prototype.__get_deltaMousePosition = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = 	Polycode.CoreInput__get_deltaMousePosition(this.__ptr)
	return retVal
}

CoreInput.prototype.__set_deltaMousePosition = function(val) {
	Polycode.CoreInput__set_deltaMousePosition(this.__ptr, val.__ptr)
}

Duktape.fin(CoreInput.prototype, function (x) {
	if (x === CoreInput.prototype) {
		return;
	}
	Polycode.CoreInput__delete(x.__ptr)
})

CoreInput.prototype.getMousePosition = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.CoreInput_getMousePosition(this.__ptr)
	return retVal
}

CoreInput.prototype.getKeyState = function(keyCode) {
	return Polycode.CoreInput_getKeyState(this.__ptr, keyCode)
}

CoreInput.prototype.getJoystickButtonState = function(joystickIndex,button) {
	return Polycode.CoreInput_getJoystickButtonState(this.__ptr, joystickIndex, button)
}

CoreInput.prototype.getJoystickAxisValue = function(joystickIndex,axis) {
	return Polycode.CoreInput_getJoystickAxisValue(this.__ptr, joystickIndex, axis)
}

CoreInput.prototype.getMouseDelta = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = Polycode.CoreInput_getMouseDelta(this.__ptr)
	return retVal
}

CoreInput.prototype.getMouseButtonState = function(mouseButton) {
	return Polycode.CoreInput_getMouseButtonState(this.__ptr, mouseButton)
}

CoreInput.prototype.getNumJoysticks = function() {
	return Polycode.CoreInput_getNumJoysticks(this.__ptr)
}

CoreInput.prototype.addJoystick = function(deviceID) {
	Polycode.CoreInput_addJoystick(this.__ptr, deviceID)
}

CoreInput.prototype.removeJoystick = function(deviceID) {
	Polycode.CoreInput_removeJoystick(this.__ptr, deviceID)
}

CoreInput.prototype.joystickAxisMoved = function(axisID,value,deviceID) {
	Polycode.CoreInput_joystickAxisMoved(this.__ptr, axisID, value, deviceID)
}

CoreInput.prototype.joystickButtonDown = function(buttonID,deviceID) {
	Polycode.CoreInput_joystickButtonDown(this.__ptr, buttonID, deviceID)
}

CoreInput.prototype.joystickButtonUp = function(buttonID,deviceID) {
	Polycode.CoreInput_joystickButtonUp(this.__ptr, buttonID, deviceID)
}

CoreInput.prototype.mouseWheelUp = function(ticks) {
	Polycode.CoreInput_mouseWheelUp(this.__ptr, ticks)
}

CoreInput.prototype.mouseWheelDown = function(ticks) {
	Polycode.CoreInput_mouseWheelDown(this.__ptr, ticks)
}

CoreInput.prototype.setMouseButtonState = function(mouseButton,state,ticks) {
	Polycode.CoreInput_setMouseButtonState(this.__ptr, mouseButton, state, ticks)
}

CoreInput.prototype.setMousePosition = function(x,y,ticks) {
	Polycode.CoreInput_setMousePosition(this.__ptr, x, y, ticks)
}

CoreInput.prototype.setKeyState = function(keyCode,newState,ticks) {
	Polycode.CoreInput_setKeyState(this.__ptr, keyCode, newState, ticks)
}

CoreInput.prototype.setDeltaPosition = function(x,y) {
	Polycode.CoreInput_setDeltaPosition(this.__ptr, x, y)
}

CoreInput.prototype.touchesBegan = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesBegan(this.__ptr, touch, touches, ticks)
}

CoreInput.prototype.touchesMoved = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesMoved(this.__ptr, touch, touches, ticks)
}

CoreInput.prototype.touchesEnded = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesEnded(this.__ptr, touch, touches, ticks)
}

CoreInput.prototype.textInput = function(text) {
	Polycode.CoreInput_textInput(this.__ptr, text)
}

CoreInput.prototype.clearInput = function() {
	Polycode.CoreInput_clearInput(this.__ptr)
}
