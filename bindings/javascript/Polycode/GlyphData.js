function GlyphData() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.GlyphData()
	}
	Object.defineProperties(this, {
		'glyphs': { enumerable: true, configurable: true, get: GlyphData.prototype.__get_glyphs, set: GlyphData.prototype.__set_glyphs},
		'positions': { enumerable: true, configurable: true, get: GlyphData.prototype.__get_positions, set: GlyphData.prototype.__set_positions},
		'num_glyphs': { enumerable: true, configurable: true, get: GlyphData.prototype.__get_num_glyphs, set: GlyphData.prototype.__set_num_glyphs},
		'trailingAdvance': { enumerable: true, configurable: true, get: GlyphData.prototype.__get_trailingAdvance, set: GlyphData.prototype.__set_trailingAdvance}
	})
}


GlyphData.prototype.__get_glyphs = function() {
	var retVal = new FT_Glyph()
	retVal.__ptr = 	Polycode.GlyphData__get_glyphs(this.__ptr)
	return retVal
}

GlyphData.prototype.__set_glyphs = function(val) {
	Polycode.GlyphData__set_glyphs(this.__ptr, val.__ptr)
}

GlyphData.prototype.__get_positions = function() {
	var retVal = new FT_Vector()
	retVal.__ptr = 	Polycode.GlyphData__get_positions(this.__ptr)
	return retVal
}

GlyphData.prototype.__set_positions = function(val) {
	Polycode.GlyphData__set_positions(this.__ptr, val.__ptr)
}

GlyphData.prototype.__get_num_glyphs = function() {
	var retVal = new FT_UInt()
	retVal.__ptr = 	Polycode.GlyphData__get_num_glyphs(this.__ptr)
	return retVal
}

GlyphData.prototype.__set_num_glyphs = function(val) {
	Polycode.GlyphData__set_num_glyphs(this.__ptr, val.__ptr)
}

GlyphData.prototype.__get_trailingAdvance = function() {
	return Polycode.GlyphData__get_trailingAdvance(this.__ptr)
}

GlyphData.prototype.__set_trailingAdvance = function(val) {
	Polycode.GlyphData__set_trailingAdvance(this.__ptr, val)
}

Duktape.fin(GlyphData.prototype, function (x) {
	if (x === GlyphData.prototype) {
		return;
	}
	Polycode.GlyphData__delete(x.__ptr)
})

GlyphData.prototype.clearData = function() {
	Polycode.GlyphData_clearData(this.__ptr)
}
