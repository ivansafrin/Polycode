function SceneCurve() {
}

SceneCurve.prototype.getWorldPointAt = function(t) {
	Polycode.SceneCurve_getWorldPointAt(this.__ptr, t)
}

SceneCurve.prototype.Update = function() {
	Polycode.SceneCurve_Update(this.__ptr)
}

SceneCurve.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneCurve_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneCurve.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneCurve_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneCurve.prototype.getCurve = function() {
	Polycode.SceneCurve_getCurve(this.__ptr)
}
