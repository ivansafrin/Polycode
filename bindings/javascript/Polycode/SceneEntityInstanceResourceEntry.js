require('Polycode/Resource')

function SceneEntityInstanceResourceEntry() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneEntityInstanceResourceEntry()
	}
}


SceneEntityInstanceResourceEntry.prototype = Object.create(Resource.prototype)

Duktape.fin(SceneEntityInstanceResourceEntry.prototype, function (x) {
	if (x === SceneEntityInstanceResourceEntry.prototype) {
		return;
	}
	Polycode.SceneEntityInstanceResourceEntry__delete(x.__ptr)
})
