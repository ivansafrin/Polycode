function Color() {
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
	Polycode.Color_setColorHSV(this.__ptr, h,s,v)
}

Color.prototype.setColorRGBA = function(r,g,b,a) {
	Polycode.Color_setColorRGBA(this.__ptr, r,g,b,a)
}

Color.prototype.setColorRGB = function(r,g,b) {
	Polycode.Color_setColorRGB(this.__ptr, r,g,b)
}

Color.prototype.setColor = function(r,g,b,a) {
	Polycode.Color_setColor(this.__ptr, r,g,b,a)
}

Color.prototype.blendColor = function(c2,mode,amount,c3) {
	Polycode.Color_blendColor(this.__ptr, c2,mode,amount,c3)
}

Color.prototype.Random = function() {
	Polycode.Color_Random(this.__ptr)
}

Color.prototype.getBrightness = function() {
	Polycode.Color_getBrightness(this.__ptr)
}

Color.prototype.getHue = function() {
	Polycode.Color_getHue(this.__ptr)
}

Color.prototype.getSaturation = function() {
	Polycode.Color_getSaturation(this.__ptr)
}

Color.prototype.getValue = function() {
	Polycode.Color_getValue(this.__ptr)
}

Color.prototype.getUint = function() {
	Polycode.Color_getUint(this.__ptr)
}
