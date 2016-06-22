require('Polycode/Entity')

function SceneSoundListener() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneSoundListener()
	}
}

SceneSoundListener.prototype = Object.create(Entity.prototype);

Duktape.fin(SceneSoundListener.prototype, function (x) {
	if (x === SceneSoundListener.prototype) {
		return;
	}
	Polycode.SceneSoundListener__delete(x.__ptr)
})

SceneSoundListener.prototype.Update = function() {
	Polycode.SceneSoundListener_Update(this.__ptr)
}
