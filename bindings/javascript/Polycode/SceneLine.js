function SceneLine() {
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
