require('Polycode/ScenePrimitive')

function SceneLabel(text,size,fontName,amode,actualHeight) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneLabel(text,size,fontName,amode,actualHeight)
	}
	Object.defineProperties(this, {
		'positionAtBaseline': { enumerable: true, configurable: true, get: SceneLabel.prototype.__get_positionAtBaseline, set: SceneLabel.prototype.__set_positionAtBaseline}
	})
}


SceneLabel.prototype = Object.create(ScenePrimitive.prototype)

SceneLabel.prototype.__get_positionAtBaseline = function() {
	return Polycode.SceneLabel__get_positionAtBaseline(this.__ptr)
}

SceneLabel.prototype.__set_positionAtBaseline = function(val) {
	Polycode.SceneLabel__set_positionAtBaseline(this.__ptr, val)
}


SceneLabel.prototype.getText = function() {
	return Polycode.SceneLabel_getText(this.__ptr)
}

SceneLabel.prototype.setLabelActualHeight = function(actualHeight) {
	Polycode.SceneLabel_setLabelActualHeight(this.__ptr, actualHeight)
}

SceneLabel.prototype.getLabelActualHeight = function() {
	return Polycode.SceneLabel_getLabelActualHeight(this.__ptr)
}

SceneLabel.prototype.getTextWidthForString = function(text) {
	return Polycode.SceneLabel_getTextWidthForString(this.__ptr, text)
}

SceneLabel.prototype.setText = function(newText) {
	Polycode.SceneLabel_setText(this.__ptr, newText)
}

SceneLabel.prototype.updateFromLabel = function() {
	Polycode.SceneLabel_updateFromLabel(this.__ptr)
}
