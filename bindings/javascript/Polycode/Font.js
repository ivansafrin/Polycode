function Font() {
}

Font.prototype.getFace = function() {
	Polycode.Font_getFace(this.__ptr)
}

Font.prototype.isValid = function() {
	Polycode.Font_isValid(this.__ptr)
}

Font.prototype.setFontName = function(fontName) {
	Polycode.Font_setFontName(this.__ptr, fontName)
}

Font.prototype.getFontName = function() {
	Polycode.Font_getFontName(this.__ptr)
}

Font.prototype.getFontPath = function() {
	Polycode.Font_getFontPath(this.__ptr)
}
