function SceneSoundListener() {
}
Duktape.fin(SceneSoundListener.prototype, function (x) {
	if (x === SceneSoundListener.prototype) {
		return;
	}
	Polycode.SceneSoundListener__delete(x.__ptr)
})

SceneSoundListener.prototype.Update = function() {
	Polycode.SceneSoundListener_Update(this.__ptr)
}
