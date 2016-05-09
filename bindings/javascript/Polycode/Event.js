function Event() {
	Object.defineProperties(this, {
		'deleteOnDispatch': { enumerable: true, configurable: true, get: Event.prototype.__get_deleteOnDispatch, set: Event.prototype.__set_deleteOnDispatch},
		'cancelEventFlag': { enumerable: true, configurable: true, get: Event.prototype.__get_cancelEventFlag, set: Event.prototype.__set_cancelEventFlag}
	})
}
Event.prototype.__get_deleteOnDispatch = function() {
	return Polycode.Event__get_deleteOnDispatch(this.__ptr)
}

Event.prototype.__set_deleteOnDispatch = function(val) {
	Polycode.Event__set_deleteOnDispatch(this.__ptr, val)
}

Event.prototype.__get_cancelEventFlag = function() {
	return Polycode.Event__get_cancelEventFlag(this.__ptr)
}

Event.prototype.__set_cancelEventFlag = function(val) {
	Polycode.Event__set_cancelEventFlag(this.__ptr, val)
}


Event.prototype.getEventCode = function() {
	return Polycode.Event_getEventCode(this.__ptr)
}

Event.prototype.getDispatcher = function() {
	var retVal = new EventDispatcher()
	retVal.__ptr = Polycode.Event_getDispatcher(this.__ptr)
	return retVal
}

Event.prototype.setEventCode = function(eventCode) {
	Polycode.Event_setEventCode(this.__ptr, eventCode)
}

Event.prototype.setDispatcher = function(dispatcher) {
	Polycode.Event_setDispatcher(this.__ptr, dispatcher)
}

Event.prototype.getEventType = function() {
	return Polycode.Event_getEventType(this.__ptr)
}

Event.prototype.cancelEvent = function() {
	Polycode.Event_cancelEvent(this.__ptr)
}
