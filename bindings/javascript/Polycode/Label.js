require('Polycode/Image')

function Label(font,text,size,antiAliasMode,premultiplyAlpha,backgroundColor,foregroundColor) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Label(font,text,size,antiAliasMode,premultiplyAlpha,backgroundColor,foregroundColor)
	}
}

Label.ANTIALIAS_FULL = 0
Label.ANTIALIAS_NONE = 1
Label.ANTIALIAS_STRONG = 2
Label.ANTIALIAS_LCD = 3
Label.ANTIALIAS_LCD_HINT = 4
Label.ANTIALIAS_FULL_HINT = 5

Label.prototype = Object.create(Image.prototype)

Duktape.fin(Label.prototype, function (x) {
	if (x === Label.prototype) {
		return;
	}
	Polycode.Label__delete(x.__ptr)
})

Label.prototype.setText = function(text) {
	Polycode.Label_setText(this.__ptr, text)
}

Label.prototype.getText = function() {
	return Polycode.Label_getText(this.__ptr)
}

Label.prototype.getTextWidthForString = function(text) {
	return Polycode.Label_getTextWidthForString(this.__ptr, text)
}

Label.prototype.getTextHeightForString = function(text) {
	return Polycode.Label_getTextHeightForString(this.__ptr, text)
}

Label.prototype.getTextWidth = function() {
	return Polycode.Label_getTextWidth(this.__ptr)
}

Label.prototype.getTextHeight = function() {
	return Polycode.Label_getTextHeight(this.__ptr)
}

Label.prototype.setColorForRange = function(color,rangeStart,rangeEnd) {
	Polycode.Label_setColorForRange(this.__ptr, color, rangeStart, rangeEnd)
}

Label.prototype.clearColors = function() {
	Polycode.Label_clearColors(this.__ptr)
}

Label.prototype.getColorForIndex = function(index) {
	var retVal = new Color()
	retVal.__ptr = Polycode.Label_getColorForIndex(this.__ptr, index)
	return retVal
}

Label.prototype.getPremultiplyAlpha = function() {
	return Polycode.Label_getPremultiplyAlpha(this.__ptr)
}

Label.prototype.setPremultiplyAlpha = function(val) {
	Polycode.Label_setPremultiplyAlpha(this.__ptr, val)
}

Label.prototype.setFont = function(newFont) {
	Polycode.Label_setFont(this.__ptr, newFont)
}

Label.prototype.getFont = function() {
	var retVal = new Font()
	retVal.__ptr = Polycode.Label_getFont(this.__ptr)
	return retVal
}

Label.prototype.setSize = function(newSize) {
	Polycode.Label_setSize(this.__ptr, newSize)
}

Label.prototype.getSize = function() {
	return Polycode.Label_getSize(this.__ptr)
}

Label.prototype.getAntialiasMode = function() {
	return Polycode.Label_getAntialiasMode(this.__ptr)
}

Label.prototype.setAntialiasMode = function(newMode) {
	Polycode.Label_setAntialiasMode(this.__ptr, newMode)
}

Label.prototype.getBaselineAdjust = function() {
	return Polycode.Label_getBaselineAdjust(this.__ptr)
}

Label.prototype.setBackgroundColor = function(color) {
	Polycode.Label_setBackgroundColor(this.__ptr, color)
}

Label.prototype.setForegroundColor = function(color) {
	Polycode.Label_setForegroundColor(this.__ptr, color)
}

Label.prototype.setColors = function(backgroundColor,foregroundColor) {
	Polycode.Label_setColors(this.__ptr, backgroundColor, foregroundColor)
}

Label.prototype.getBackgroundColor = function() {
	var retVal = new Color()
	retVal.__ptr = Polycode.Label_getBackgroundColor(this.__ptr)
	return retVal
}

Label.prototype.getForegroundColor = function() {
	var retVal = new Color()
	retVal.__ptr = Polycode.Label_getForegroundColor(this.__ptr)
	return retVal
}

Label.prototype.optionsChanged = function() {
	return Polycode.Label_optionsChanged(this.__ptr)
}
