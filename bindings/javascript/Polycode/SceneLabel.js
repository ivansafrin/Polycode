function SceneLabel() {
}

SceneLabel.prototype.getText = function() {
	Polycode.SceneLabel_getText(this.__ptr)
}

SceneLabel.prototype.setLabelActualHeight = function(actualHeight) {
	Polycode.SceneLabel_setLabelActualHeight(this.__ptr, actualHeight)
}

SceneLabel.prototype.getLabelActualHeight = function() {
	Polycode.SceneLabel_getLabelActualHeight(this.__ptr)
}

SceneLabel.prototype.Render = function(buffer) {
	Polycode.SceneLabel_Render(this.__ptr, buffer)
}

SceneLabel.prototype.getTextWidthForString = function(text) {
	Polycode.SceneLabel_getTextWidthForString(this.__ptr, text)
}

SceneLabel.prototype.setText = function(newText) {
	Polycode.SceneLabel_setText(this.__ptr, newText)
}

SceneLabel.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneLabel_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneLabel.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneLabel_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneLabel.prototype.updateFromLabel = function() {
	Polycode.SceneLabel_updateFromLabel(this.__ptr)
}

SceneLabel.prototype.getLabel = function() {
	Polycode.SceneLabel_getLabel(this.__ptr)
}
