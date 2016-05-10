function Font() {
	Object.defineProperties(this, {
		'loaded': { enumerable: true, configurable: true, get: Font.prototype.__get_loaded, set: Font.prototype.__set_loaded}
	})
}
Font.prototype.__get_loaded = function() {
	return Polycode.Font__get_loaded(this.__ptr)
}

Font.prototype.__set_loaded = function(val) {
	Polycode.Font__set_loaded(this.__ptr, val)
}

Duktape.fin(Font.prototype, function (x) {
	if (x === Font.prototype) {
		return;
	}
	Polycode.Font__delete(x.__ptr)
})

Font.prototype.getFace = function() {
	var retVal = new FT_Face()
	retVal.__ptr = Polycode.Font_getFace(this.__ptr)
	return retVal
}

Font.prototype.isValid = function() {
	return Polycode.Font_isValid(this.__ptr)
}

Font.prototype.setFontName = function(fontName) {
	Polycode.Font_setFontName(this.__ptr, fontName)
}

Font.prototype.getFontName = function() {
	return Polycode.Font_getFontName(this.__ptr)
}

Font.prototype.getFontPath = function() {
	return Polycode.Font_getFontPath(this.__ptr)
}
