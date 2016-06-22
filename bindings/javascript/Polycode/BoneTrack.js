function BoneTrack(bone,length) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BoneTrack(bone,length)
	}
	Object.defineProperties(this, {
		'scaleX': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_scaleX, set: BoneTrack.prototype.__set_scaleX},
		'scaleY': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_scaleY, set: BoneTrack.prototype.__set_scaleY},
		'scaleZ': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_scaleZ, set: BoneTrack.prototype.__set_scaleZ},
		'QuatW': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_QuatW, set: BoneTrack.prototype.__set_QuatW},
		'QuatX': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_QuatX, set: BoneTrack.prototype.__set_QuatX},
		'QuatY': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_QuatY, set: BoneTrack.prototype.__set_QuatY},
		'QuatZ': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_QuatZ, set: BoneTrack.prototype.__set_QuatZ},
		'LocX': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_LocX, set: BoneTrack.prototype.__set_LocX},
		'LocY': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_LocY, set: BoneTrack.prototype.__set_LocY},
		'LocZ': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_LocZ, set: BoneTrack.prototype.__set_LocZ},
		'position': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_position, set: BoneTrack.prototype.__set_position},
		'scale': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_scale, set: BoneTrack.prototype.__set_scale},
		'boneQuat': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_boneQuat, set: BoneTrack.prototype.__set_boneQuat},
		'quatCurve': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_quatCurve, set: BoneTrack.prototype.__set_quatCurve},
		'weight': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_weight, set: BoneTrack.prototype.__set_weight}
	})
}

BoneTrack.prototype.__get_scaleX = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_scaleX(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_scaleX = function(val) {
	Polycode.BoneTrack__set_scaleX(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_scaleY = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_scaleY(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_scaleY = function(val) {
	Polycode.BoneTrack__set_scaleY(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_scaleZ = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_scaleZ(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_scaleZ = function(val) {
	Polycode.BoneTrack__set_scaleZ(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_QuatW = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_QuatW(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_QuatW = function(val) {
	Polycode.BoneTrack__set_QuatW(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_QuatX = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_QuatX(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_QuatX = function(val) {
	Polycode.BoneTrack__set_QuatX(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_QuatY = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_QuatY(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_QuatY = function(val) {
	Polycode.BoneTrack__set_QuatY(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_QuatZ = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_QuatZ(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_QuatZ = function(val) {
	Polycode.BoneTrack__set_QuatZ(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_LocX = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_LocX(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_LocX = function(val) {
	Polycode.BoneTrack__set_LocX(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_LocY = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_LocY(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_LocY = function(val) {
	Polycode.BoneTrack__set_LocY(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_LocZ = function() {
	var retVal = new BezierCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_LocZ(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_LocZ = function(val) {
	Polycode.BoneTrack__set_LocZ(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_position = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.BoneTrack__get_position(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_position = function(val) {
	Polycode.BoneTrack__set_position(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_scale = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.BoneTrack__get_scale(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_scale = function(val) {
	Polycode.BoneTrack__set_scale(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_boneQuat = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.BoneTrack__get_boneQuat(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_boneQuat = function(val) {
	Polycode.BoneTrack__set_boneQuat(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_quatCurve = function() {
	var retVal = new QuaternionCurve()
	retVal.__ptr = 	Polycode.BoneTrack__get_quatCurve(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_quatCurve = function(val) {
	Polycode.BoneTrack__set_quatCurve(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_weight = function() {
	return Polycode.BoneTrack__get_weight(this.__ptr)
}

BoneTrack.prototype.__set_weight = function(val) {
	Polycode.BoneTrack__set_weight(this.__ptr, val)
}

Duktape.fin(BoneTrack.prototype, function (x) {
	if (x === BoneTrack.prototype) {
		return;
	}
	Polycode.BoneTrack__delete(x.__ptr)
})

BoneTrack.prototype.Play = function(once) {
	Polycode.BoneTrack_Play(this.__ptr, once)
}

BoneTrack.prototype.Stop = function() {
	Polycode.BoneTrack_Stop(this.__ptr)
}

BoneTrack.prototype.Update = function(elapsed) {
	Polycode.BoneTrack_Update(this.__ptr, elapsed)
}

BoneTrack.prototype.Reset = function() {
	Polycode.BoneTrack_Reset(this.__ptr)
}

BoneTrack.prototype.setSpeed = function(speed) {
	Polycode.BoneTrack_setSpeed(this.__ptr, speed)
}
