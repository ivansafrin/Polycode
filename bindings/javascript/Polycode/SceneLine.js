require('Polycode/SceneMesh')

function SceneLine(ent1,ent2) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneLine(ent1,ent2)
	}
}

SceneLine.prototype = Object.create(SceneMesh.prototype);


SceneLine.prototype.SceneLineWithPositions = function(startp,endp) {
	var retVal = new SceneLine()
	retVal.__ptr = Polycode.SceneLine_SceneLineWithPositions(startp, endp)
	return retVal
}

SceneLine.prototype.setStart = function(startp) {
	Polycode.SceneLine_setStart(this.__ptr, startp)
}

SceneLine.prototype.setEnd = function(endp) {
	Polycode.SceneLine_setEnd(this.__ptr, endp)
}

SceneLine.prototype.Update = function() {
	Polycode.SceneLine_Update(this.__ptr)
}
