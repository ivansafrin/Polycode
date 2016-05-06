function EventDispatcher() {
}

EventDispatcher.prototype.removeAllHandlers = function() {
	Polycode.EventDispatcher_removeAllHandlers(this.__ptr)
}

EventDispatcher.prototype.removeAllHandlersForListener = function(handler) {
	Polycode.EventDispatcher_removeAllHandlersForListener(this.__ptr, handler)
}

EventDispatcher.prototype.addEventListener = function(handler,eventCode) {
	Polycode.EventDispatcher_addEventListener(this.__ptr, handler,eventCode)
}

EventDispatcher.prototype.addEventListenerUnique = function(handler,eventCode) {
	Polycode.EventDispatcher_addEventListenerUnique(this.__ptr, handler,eventCode)
}

EventDispatcher.prototype.hasEventListener = function(handler,eventCode) {
	Polycode.EventDispatcher_hasEventListener(this.__ptr, handler,eventCode)
}

EventDispatcher.prototype.removeEventListener = function(handler,eventCode) {
	Polycode.EventDispatcher_removeEventListener(this.__ptr, handler,eventCode)
}

EventDispatcher.prototype.__dispatchEvent = function(event,eventCode) {
	Polycode.EventDispatcher___dispatchEvent(this.__ptr, event,eventCode)
}

EventDispatcher.prototype.dispatchEvent = function(event,eventCode) {
	Polycode.EventDispatcher_dispatchEvent(this.__ptr, event,eventCode)
}

EventDispatcher.prototype.dispatchEventNoDelete = function(event,eventCode) {
	Polycode.EventDispatcher_dispatchEventNoDelete(this.__ptr, event,eventCode)
}
