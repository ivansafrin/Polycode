function Color(r,g,b,a) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Color(r,g,b,a)
	}
	Object.defineProperties(this, {
		'r': { enumerable: true, configurable: true, get: Color.prototype.__get_r, set: Color.prototype.__set_r},
		'g': { enumerable: true, configurable: true, get: Color.prototype.__get_g, set: Color.prototype.__set_g},
		'b': { enumerable: true, configurable: true, get: Color.prototype.__get_b, set: Color.prototype.__set_b},
		'a': { enumerable: true, configurable: true, get: Color.prototype.__get_a, set: Color.prototype.__set_a}
	})
}

Color.BLEND_NORMAL = 0
Color.BLEND_REPLACE_COLOR = 1
Color.BLEND_ADDITIVE = 2

Color.prototype.__get_r = function() {
	return Polycode.Color__get_r(this.__ptr)
}

Color.prototype.__set_r = function(val) {
	Polycode.Color__set_r(this.__ptr, val)
}

Color.prototype.__get_g = function() {
	return Polycode.Color__get_g(this.__ptr)
}

Color.prototype.__set_g = function(val) {
	Polycode.Color__set_g(this.__ptr, val)
}

Color.prototype.__get_b = function() {
	return Polycode.Color__get_b(this.__ptr)
}

Color.prototype.__set_b = function(val) {
	Polycode.Color__set_b(this.__ptr, val)
}

Color.prototype.__get_a = function() {
	return Polycode.Color__get_a(this.__ptr)
}

Color.prototype.__set_a = function(val) {
	Polycode.Color__set_a(this.__ptr, val)
}

Duktape.fin(Color.prototype, function (x) {
	if (x === Color.prototype) {
		return;
	}
	Polycode.Color__delete(x.__ptr)
})

Color.prototype.ColorWithInts = function(r,g,b,a) {
	var retVal = new Color()
	retVal.__ptr = Polycode.Color_ColorWithInts(r, g, b, a)
	return retVal
}

Color.prototype.ColorWithHex = function(hex) {
	var retVal = new Color()
	retVal.__ptr = Polycode.Color_ColorWithHex(hex)
	return retVal
}

Color.prototype.setColorHex = function(hex) {
	Polycode.Color_setColorHex(this.__ptr, hex)
}

Color.prototype.setColorHexRGB = function(hex) {
	Polycode.Color_setColorHexRGB(this.__ptr, hex)
}

Color.prototype.setColorHexFromString = function(hex) {
	Polycode.Color_setColorHexFromString(this.__ptr, hex)
}

Color.prototype.setColorHexRGBFromString = function(hex) {
	Polycode.Color_setColorHexRGBFromString(this.__ptr, hex)
}

Color.prototype.setColorHSV = function(h,s,v) {
	Polycode.Color_setColorHSV(this.__ptr, h, s, v)
}

Color.prototype.setColorRGBA = function(r,g,b,a) {
	Polycode.Color_setColorRGBA(this.__ptr, r, g, b, a)
}

Color.prototype.setColorRGB = function(r,g,b) {
	Polycode.Color_setColorRGB(this.__ptr, r, g, b)
}

Color.prototype.setColor = function(r,g,b,a) {
	Polycode.Color_setColor(this.__ptr, r, g, b, a)
}

Color.prototype.blendColor = function(c2,mode,amount,c3) {
	var retVal = new Color()
	retVal.__ptr = Polycode.Color_blendColor(this.__ptr, c2, mode, amount, c3)
	return retVal
}

Color.prototype.Random = function() {
	Polycode.Color_Random(this.__ptr)
}

Color.prototype.getBrightness = function() {
	return Polycode.Color_getBrightness(this.__ptr)
}

Color.prototype.RGBtoHSV = function(r,g,b,h,s,v) {
	Polycode.Color_RGBtoHSV(r, g, b, h, s, v)
}

Color.prototype.getHue = function() {
	return Polycode.Color_getHue(this.__ptr)
}

Color.prototype.getSaturation = function() {
	return Polycode.Color_getSaturation(this.__ptr)
}

Color.prototype.getValue = function() {
	return Polycode.Color_getValue(this.__ptr)
}

Color.prototype.getUint = function() {
	return Polycode.Color_getUint(this.__ptr)
}
