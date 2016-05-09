function SceneLabel() {
	Object.defineProperties(this, {
		'positionAtBaseline': { enumerable: true, configurable: true, get: SceneLabel.prototype.__get_positionAtBaseline, set: SceneLabel.prototype.__set_positionAtBaseline}
	})
}
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

SceneLabel.prototype.Render = function(buffer) {
	Polycode.SceneLabel_Render(this.__ptr, buffer)
}

SceneLabel.prototype.getTextWidthForString = function(text) {
	return Polycode.SceneLabel_getTextWidthForString(this.__ptr, text)
}

SceneLabel.prototype.setText = function(newText) {
	Polycode.SceneLabel_setText(this.__ptr, newText)
}

SceneLabel.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneLabel_Clone(this.__ptr, deepClone,ignoreEditorOnly)
	return retVal
}

SceneLabel.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneLabel_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneLabel.prototype.updateFromLabel = function() {
	Polycode.SceneLabel_updateFromLabel(this.__ptr)
}

SceneLabel.prototype.getLabel = function() {
	var retVal = new Label()
	retVal.__ptr = Polycode.SceneLabel_getLabel(this.__ptr)
	return retVal
}
