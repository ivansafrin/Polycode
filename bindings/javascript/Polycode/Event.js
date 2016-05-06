function Event() {
}

Event.prototype.getEventCode = function() {
	Polycode.Event_getEventCode(this.__ptr)
}

Event.prototype.getDispatcher = function() {
	Polycode.Event_getDispatcher(this.__ptr)
}

Event.prototype.setEventCode = function(eventCode) {
	Polycode.Event_setEventCode(this.__ptr, eventCode)
}

Event.prototype.setDispatcher = function(dispatcher) {
	Polycode.Event_setDispatcher(this.__ptr, dispatcher)
}

Event.prototype.getEventType = function() {
	Polycode.Event_getEventType(this.__ptr)
}

Event.prototype.cancelEvent = function() {
	Polycode.Event_cancelEvent(this.__ptr)
}
