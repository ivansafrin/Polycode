require('Polycode/Resource')

function SceneEntityInstanceResourceEntry(instance) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneEntityInstanceResourceEntry(instance)
	}
}

SceneEntityInstanceResourceEntry.prototype = Object.create(Resource.prototype);

Duktape.fin(SceneEntityInstanceResourceEntry.prototype, function (x) {
	if (x === SceneEntityInstanceResourceEntry.prototype) {
		return;
	}
	Polycode.SceneEntityInstanceResourceEntry__delete(x.__ptr)
})

SceneEntityInstanceResourceEntry.prototype.getInstance = function() {
	var retVal = new SceneEntityInstance()
	retVal.__ptr = Polycode.SceneEntityInstanceResourceEntry_getInstance(this.__ptr)
	return retVal
}

SceneEntityInstanceResourceEntry.prototype.reloadResource = function() {
	Polycode.SceneEntityInstanceResourceEntry_reloadResource(this.__ptr)
}
