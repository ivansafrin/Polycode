function SkeletonAnimation(name,duration) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SkeletonAnimation(name,duration)
	}
}


Duktape.fin(SkeletonAnimation.prototype, function (x) {
	if (x === SkeletonAnimation.prototype) {
		return;
	}
	Polycode.SkeletonAnimation__delete(x.__ptr)
})

SkeletonAnimation.prototype.addBoneTrack = function(boneTrack) {
	Polycode.SkeletonAnimation_addBoneTrack(this.__ptr, boneTrack.__ptr)
}

SkeletonAnimation.prototype.getName = function() {
	return Polycode.SkeletonAnimation_getName(this.__ptr)
}

SkeletonAnimation.prototype.Play = function(once) {
	Polycode.SkeletonAnimation_Play(this.__ptr, once)
}

SkeletonAnimation.prototype.Stop = function() {
	Polycode.SkeletonAnimation_Stop(this.__ptr)
}

SkeletonAnimation.prototype.Reset = function() {
	Polycode.SkeletonAnimation_Reset(this.__ptr)
}

SkeletonAnimation.prototype.Update = function() {
	Polycode.SkeletonAnimation_Update(this.__ptr)
}

SkeletonAnimation.prototype.setSpeed = function(speed) {
	Polycode.SkeletonAnimation_setSpeed(this.__ptr, speed)
}

SkeletonAnimation.prototype.setWeight = function(newWeight) {
	Polycode.SkeletonAnimation_setWeight(this.__ptr, newWeight)
}

SkeletonAnimation.prototype.getWeight = function() {
	return Polycode.SkeletonAnimation_getWeight(this.__ptr)
}

SkeletonAnimation.prototype.isPlaying = function() {
	return Polycode.SkeletonAnimation_isPlaying(this.__ptr)
}
