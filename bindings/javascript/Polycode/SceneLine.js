require('Polycode/SceneMesh')

function SceneLine(startp,endp) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneLine(startp,endp)
	}
}


SceneLine.prototype = Object.create(SceneMesh.prototype)


SceneLine.prototype.setStart = function(startp) {
	Polycode.SceneLine_setStart(this.__ptr, startp)
}

SceneLine.prototype.setEnd = function(endp) {
	Polycode.SceneLine_setEnd(this.__ptr, endp)
}

SceneLine.prototype.Update = function() {
	Polycode.SceneLine_Update(this.__ptr)
}
