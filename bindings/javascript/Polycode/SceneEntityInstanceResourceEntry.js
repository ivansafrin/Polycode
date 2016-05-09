function SceneEntityInstanceResourceEntry() {
}

SceneEntityInstanceResourceEntry.prototype.getInstance = function() {
	var retVal = new SceneEntityInstance()
	retVal.__ptr = Polycode.SceneEntityInstanceResourceEntry_getInstance(this.__ptr)
	return retVal
}

SceneEntityInstanceResourceEntry.prototype.reloadResource = function() {
	Polycode.SceneEntityInstanceResourceEntry_reloadResource(this.__ptr)
}
