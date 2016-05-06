function BoneTrack() {
}

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
