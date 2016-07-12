function Event() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Event()
	}
	Object.defineProperties(this, {
		'deleteOnDispatch': { enumerable: true, configurable: true, get: Event.prototype.__get_deleteOnDispatch, set: Event.prototype.__set_deleteOnDispatch},
		'cancelEventFlag': { enumerable: true, configurable: true, get: Event.prototype.__get_cancelEventFlag, set: Event.prototype.__set_cancelEventFlag}
	})
}

Event.EVENTBASE_EVENT = 0x100
Event.COMPLETE_EVENT = EVENTBASE_EVENT + 0
Event.CHANGE_EVENT = EVENTBASE_EVENT + 1
Event.CANCEL_EVENT = EVENTBASE_EVENT + 2
Event.NOTIFY_EVENT = EVENTBASE_EVENT + 3
Event.FIRE_EVENT = EVENTBASE_EVENT + 4
Event.RESOURCE_RELOAD_EVENT = EVENTBASE_EVENT + 5
Event.SELECT_EVENT = EVENTBASE_EVENT + 6
Event.REMOVE_EVENT = EVENTBASE_EVENT + 7
Event.RESOURCE_CHANGE_EVENT = EVENTBASE_EVENT + 8
Event.EVENTBASE_NONPOLYCODE = 0x10000

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

Duktape.fin(Event.prototype, function (x) {
	if (x === Event.prototype) {
		return;
	}
	Polycode.Event__delete(x.__ptr)
})

Event.prototype.getEventCode = function() {
	return Polycode.Event_getEventCode(this.__ptr)
}

Event.prototype.setEventCode = function(eventCode) {
	Polycode.Event_setEventCode(this.__ptr, eventCode)
}

Event.prototype.getEventType = function() {
	return Polycode.Event_getEventType(this.__ptr)
}

Event.prototype.cancelEvent = function() {
	Polycode.Event_cancelEvent(this.__ptr)
}
