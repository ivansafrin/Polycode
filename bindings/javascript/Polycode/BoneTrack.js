function BoneTrack(bone,length) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.BoneTrack(bone,length)
	}
	Object.defineProperties(this, {
		'position': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_position, set: BoneTrack.prototype.__set_position},
		'scale': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_scale, set: BoneTrack.prototype.__set_scale},
		'boneQuat': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_boneQuat, set: BoneTrack.prototype.__set_boneQuat},
		'weight': { enumerable: true, configurable: true, get: BoneTrack.prototype.__get_weight, set: BoneTrack.prototype.__set_weight}
	})
}


BoneTrack.prototype.__get_position = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.BoneTrack__get_position(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_position = function(val) {
	Polycode.BoneTrack__set_position(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_scale = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = 	Polycode.BoneTrack__get_scale(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_scale = function(val) {
	Polycode.BoneTrack__set_scale(this.__ptr, val.__ptr)
}

BoneTrack.prototype.__get_boneQuat = function() {
	var retVal = new Quaternion("__skip_ptr__")
	retVal.__ptr = 	Polycode.BoneTrack__get_boneQuat(this.__ptr)
	return retVal
}

BoneTrack.prototype.__set_boneQuat = function(val) {
	Polycode.BoneTrack__set_boneQuat(this.__ptr, val.__ptr)
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
