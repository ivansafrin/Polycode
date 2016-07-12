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
