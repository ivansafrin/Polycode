function Label() {
}

Label.prototype.setText = function(text) {
	Polycode.Label_setText(this.__ptr, text)
}

Label.prototype.getText = function() {
	Polycode.Label_getText(this.__ptr)
}

Label.prototype.getTextWidthForString = function(text) {
	Polycode.Label_getTextWidthForString(this.__ptr, text)
}

Label.prototype.getTextHeightForString = function(text) {
	Polycode.Label_getTextHeightForString(this.__ptr, text)
}

Label.prototype.getTextWidth = function() {
	Polycode.Label_getTextWidth(this.__ptr)
}

Label.prototype.getTextHeight = function() {
	Polycode.Label_getTextHeight(this.__ptr)
}

Label.prototype.setColorForRange = function(color,rangeStart,rangeEnd) {
	Polycode.Label_setColorForRange(this.__ptr, color,rangeStart,rangeEnd)
}

Label.prototype.clearColors = function() {
	Polycode.Label_clearColors(this.__ptr)
}

Label.prototype.getColorForIndex = function(index) {
	Polycode.Label_getColorForIndex(this.__ptr, index)
}

Label.prototype.getPremultiplyAlpha = function() {
	Polycode.Label_getPremultiplyAlpha(this.__ptr)
}

Label.prototype.setPremultiplyAlpha = function(val) {
	Polycode.Label_setPremultiplyAlpha(this.__ptr, val)
}

Label.prototype.setFont = function(newFont) {
	Polycode.Label_setFont(this.__ptr, newFont)
}

Label.prototype.getFont = function() {
	Polycode.Label_getFont(this.__ptr)
}

Label.prototype.setSize = function(newSize) {
	Polycode.Label_setSize(this.__ptr, newSize)
}

Label.prototype.getSize = function() {
	Polycode.Label_getSize(this.__ptr)
}

Label.prototype.getAntialiasMode = function() {
	Polycode.Label_getAntialiasMode(this.__ptr)
}

Label.prototype.setAntialiasMode = function(newMode) {
	Polycode.Label_setAntialiasMode(this.__ptr, newMode)
}

Label.prototype.getBaselineAdjust = function() {
	Polycode.Label_getBaselineAdjust(this.__ptr)
}

Label.prototype.setBackgroundColor = function(color) {
	Polycode.Label_setBackgroundColor(this.__ptr, color)
}

Label.prototype.setForegroundColor = function(color) {
	Polycode.Label_setForegroundColor(this.__ptr, color)
}

Label.prototype.setColors = function(backgroundColor,foregroundColor) {
	Polycode.Label_setColors(this.__ptr, backgroundColor,foregroundColor)
}

Label.prototype.getBackgroundColor = function() {
	Polycode.Label_getBackgroundColor(this.__ptr)
}

Label.prototype.getForegroundColor = function() {
	Polycode.Label_getForegroundColor(this.__ptr)
}

Label.prototype.optionsChanged = function() {
	Polycode.Label_optionsChanged(this.__ptr)
}
