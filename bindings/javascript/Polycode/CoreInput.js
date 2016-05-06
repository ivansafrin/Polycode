function CoreInput() {
}

CoreInput.prototype.getMousePosition = function() {
	Polycode.CoreInput_getMousePosition(this.__ptr)
}

CoreInput.prototype.getKeyState = function(keyCode) {
	Polycode.CoreInput_getKeyState(this.__ptr, keyCode)
}

CoreInput.prototype.getJoystickButtonState = function(joystickIndex,button) {
	Polycode.CoreInput_getJoystickButtonState(this.__ptr, joystickIndex,button)
}

CoreInput.prototype.getJoystickAxisValue = function(joystickIndex,axis) {
	Polycode.CoreInput_getJoystickAxisValue(this.__ptr, joystickIndex,axis)
}

CoreInput.prototype.getMouseDelta = function() {
	Polycode.CoreInput_getMouseDelta(this.__ptr)
}

CoreInput.prototype.getMouseButtonState = function(mouseButton) {
	Polycode.CoreInput_getMouseButtonState(this.__ptr, mouseButton)
}

CoreInput.prototype.getNumJoysticks = function() {
	Polycode.CoreInput_getNumJoysticks(this.__ptr)
}

CoreInput.prototype.getJoystickInfoByIndex = function(index) {
	Polycode.CoreInput_getJoystickInfoByIndex(this.__ptr, index)
}

CoreInput.prototype.getJoystickInfoByID = function(deviceID) {
	Polycode.CoreInput_getJoystickInfoByID(this.__ptr, deviceID)
}

CoreInput.prototype.addJoystick = function(deviceID) {
	Polycode.CoreInput_addJoystick(this.__ptr, deviceID)
}

CoreInput.prototype.removeJoystick = function(deviceID) {
	Polycode.CoreInput_removeJoystick(this.__ptr, deviceID)
}

CoreInput.prototype.joystickAxisMoved = function(axisID,value,deviceID) {
	Polycode.CoreInput_joystickAxisMoved(this.__ptr, axisID,value,deviceID)
}

CoreInput.prototype.joystickButtonDown = function(buttonID,deviceID) {
	Polycode.CoreInput_joystickButtonDown(this.__ptr, buttonID,deviceID)
}

CoreInput.prototype.joystickButtonUp = function(buttonID,deviceID) {
	Polycode.CoreInput_joystickButtonUp(this.__ptr, buttonID,deviceID)
}

CoreInput.prototype.mouseWheelUp = function(ticks) {
	Polycode.CoreInput_mouseWheelUp(this.__ptr, ticks)
}

CoreInput.prototype.mouseWheelDown = function(ticks) {
	Polycode.CoreInput_mouseWheelDown(this.__ptr, ticks)
}

CoreInput.prototype.setMouseButtonState = function(mouseButton,state,ticks) {
	Polycode.CoreInput_setMouseButtonState(this.__ptr, mouseButton,state,ticks)
}

CoreInput.prototype.setMousePosition = function(x,y,ticks) {
	Polycode.CoreInput_setMousePosition(this.__ptr, x,y,ticks)
}

CoreInput.prototype.setKeyState = function(keyCode,code,newState,ticks) {
	Polycode.CoreInput_setKeyState(this.__ptr, keyCode,code,newState,ticks)
}

CoreInput.prototype.setDeltaPosition = function(x,y) {
	Polycode.CoreInput_setDeltaPosition(this.__ptr, x,y)
}

CoreInput.prototype.touchesBegan = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesBegan(this.__ptr, touch,touches,ticks)
}

CoreInput.prototype.touchesMoved = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesMoved(this.__ptr, touch,touches,ticks)
}

CoreInput.prototype.touchesEnded = function(touch,touches,ticks) {
	Polycode.CoreInput_touchesEnded(this.__ptr, touch,touches,ticks)
}

CoreInput.prototype.clearInput = function() {
	Polycode.CoreInput_clearInput(this.__ptr)
}
