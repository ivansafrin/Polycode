require('Polycode/EventDispatcher')

function CoreServices() {
}


CoreServices.prototype = Object.create(EventDispatcher.prototype)

Duktape.fin(CoreServices.prototype, function (x) {
	if (x === CoreServices.prototype) {
		return;
	}
	Polycode.CoreServices__delete(x.__ptr)
})

CoreServices.prototype.createInstance = function() {
	Polycode.CoreServices_createInstance()
}

CoreServices.prototype.Update = function(elapsed) {
	Polycode.CoreServices_Update(this.__ptr, elapsed)
}

CoreServices.prototype.fixedUpdate = function() {
	Polycode.CoreServices_fixedUpdate(this.__ptr)
}
