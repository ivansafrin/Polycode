function LightShadowInfoBinding() {
	Object.defineProperties(this, {
		'shadowMatrix': { enumerable: true, configurable: true, get: LightShadowInfoBinding.prototype.__get_shadowMatrix, set: LightShadowInfoBinding.prototype.__set_shadowMatrix},
		'shadowBuffer': { enumerable: true, configurable: true, get: LightShadowInfoBinding.prototype.__get_shadowBuffer, set: LightShadowInfoBinding.prototype.__set_shadowBuffer}
	})
}
LightShadowInfoBinding.prototype.__get_shadowMatrix = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightShadowInfoBinding__get_shadowMatrix(this.__ptr)
	return retVal
}

LightShadowInfoBinding.prototype.__set_shadowMatrix = function(val) {
	Polycode.LightShadowInfoBinding__set_shadowMatrix(this.__ptr, val.__ptr)
}

LightShadowInfoBinding.prototype.__get_shadowBuffer = function() {
	var retVal = new LocalShaderParam()
	retVal.__ptr = 	Polycode.LightShadowInfoBinding__get_shadowBuffer(this.__ptr)
	return retVal
}

LightShadowInfoBinding.prototype.__set_shadowBuffer = function(val) {
	Polycode.LightShadowInfoBinding__set_shadowBuffer(this.__ptr, val.__ptr)
}

Duktape.fin(LightShadowInfoBinding.prototype, function (x) {
	if (x === LightShadowInfoBinding.prototype) {
		return;
	}
	Polycode.LightShadowInfoBinding__delete(x.__ptr)
})
