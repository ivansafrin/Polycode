require('Polycode/SceneMesh')

function SceneCurve() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneCurve()
	}
	Object.defineProperties(this, {
		'renderCurve': { enumerable: true, configurable: true, get: SceneCurve.prototype.__get_renderCurve, set: SceneCurve.prototype.__set_renderCurve},
		'curveResolution': { enumerable: true, configurable: true, get: SceneCurve.prototype.__get_curveResolution, set: SceneCurve.prototype.__set_curveResolution}
	})
}


SceneCurve.prototype = Object.create(SceneMesh.prototype)

SceneCurve.prototype.__get_renderCurve = function() {
	return Polycode.SceneCurve__get_renderCurve(this.__ptr)
}

SceneCurve.prototype.__set_renderCurve = function(val) {
	Polycode.SceneCurve__set_renderCurve(this.__ptr, val)
}

SceneCurve.prototype.__get_curveResolution = function() {
	return Polycode.SceneCurve__get_curveResolution(this.__ptr)
}

SceneCurve.prototype.__set_curveResolution = function(val) {
	Polycode.SceneCurve__set_curveResolution(this.__ptr, val)
}

Duktape.fin(SceneCurve.prototype, function (x) {
	if (x === SceneCurve.prototype) {
		return;
	}
	Polycode.SceneCurve__delete(x.__ptr)
})

SceneCurve.prototype.getWorldPointAt = function(t) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.SceneCurve_getWorldPointAt(this.__ptr, t)
	return retVal
}

SceneCurve.prototype.Update = function() {
	Polycode.SceneCurve_Update(this.__ptr)
}
