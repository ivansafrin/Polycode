require('Polycode/EventHandler')

function EventDispatcher() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.EventDispatcher()
	}
}


EventDispatcher.prototype = Object.create(EventHandler.prototype)

Duktape.fin(EventDispatcher.prototype, function (x) {
	if (x === EventDispatcher.prototype) {
		return;
	}
	Polycode.EventDispatcher__delete(x.__ptr)
})

EventDispatcher.prototype.removeAllHandlers = function() {
	Polycode.EventDispatcher_removeAllHandlers(this.__ptr)
}

EventDispatcher.prototype.removeAllHandlersForListener = function(handler) {
	Polycode.EventDispatcher_removeAllHandlersForListener(this.__ptr, handler.__ptr)
}

EventDispatcher.prototype.addEventListener = function(handler,eventCode) {
	Polycode.EventDispatcher_addEventListener(this.__ptr, handler.__ptr, eventCode)
}

EventDispatcher.prototype.addEventListenerUnique = function(handler,eventCode) {
	Polycode.EventDispatcher_addEventListenerUnique(this.__ptr, handler.__ptr, eventCode)
}

EventDispatcher.prototype.hasEventListener = function(handler,eventCode) {
	return Polycode.EventDispatcher_hasEventListener(this.__ptr, handler.__ptr, eventCode)
}

EventDispatcher.prototype.removeEventListener = function(handler,eventCode) {
	Polycode.EventDispatcher_removeEventListener(this.__ptr, handler.__ptr, eventCode)
}

EventDispatcher.prototype.__dispatchEvent = function(event,eventCode) {
	Polycode.EventDispatcher___dispatchEvent(this.__ptr, event.__ptr, eventCode)
}

EventDispatcher.prototype.dispatchEvent = function(event,eventCode) {
	Polycode.EventDispatcher_dispatchEvent(this.__ptr, event.__ptr, eventCode)
}

EventDispatcher.prototype.dispatchEventNoDelete = function(event,eventCode) {
	Polycode.EventDispatcher_dispatchEventNoDelete(this.__ptr, event.__ptr, eventCode)
}
