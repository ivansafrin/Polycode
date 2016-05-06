function Skeleton() {
}

Skeleton.prototype.loadSkeleton = function(fileName) {
	Polycode.Skeleton_loadSkeleton(this.__ptr, fileName)
}

Skeleton.prototype.playAnimationByName = function(animName,weight,once,restartIfPlaying) {
	Polycode.Skeleton_playAnimationByName(this.__ptr, animName,weight,once,restartIfPlaying)
}

Skeleton.prototype.playAnimation = function(animation,weight,once,restartIfPlaying) {
	Polycode.Skeleton_playAnimation(this.__ptr, animation,weight,once,restartIfPlaying)
}

Skeleton.prototype.setBaseAnimationByName = function(animName) {
	Polycode.Skeleton_setBaseAnimationByName(this.__ptr, animName)
}

Skeleton.prototype.setBaseAnimation = function(animation) {
	Polycode.Skeleton_setBaseAnimation(this.__ptr, animation)
}

Skeleton.prototype.stopAllAnimations = function() {
	Polycode.Skeleton_stopAllAnimations(this.__ptr)
}

Skeleton.prototype.getBaseAnimation = function() {
	Polycode.Skeleton_getBaseAnimation(this.__ptr)
}

Skeleton.prototype.addAnimation = function(name,fileName) {
	Polycode.Skeleton_addAnimation(this.__ptr, name,fileName)
}

Skeleton.prototype.getAnimation = function(name) {
	Polycode.Skeleton_getAnimation(this.__ptr, name)
}

Skeleton.prototype.stopAnimationByName = function(name) {
	Polycode.Skeleton_stopAnimationByName(this.__ptr, name)
}

Skeleton.prototype.stopAnimation = function(animation) {
	Polycode.Skeleton_stopAnimation(this.__ptr, animation)
}

Skeleton.prototype.Update = function() {
	Polycode.Skeleton_Update(this.__ptr)
}

Skeleton.prototype.getBoneByName = function(name) {
	Polycode.Skeleton_getBoneByName(this.__ptr, name)
}

Skeleton.prototype.bonesVisible = function(val) {
	Polycode.Skeleton_bonesVisible(this.__ptr, val)
}

Skeleton.prototype.getNumBones = function() {
	Polycode.Skeleton_getNumBones(this.__ptr)
}

Skeleton.prototype.getBone = function(index) {
	Polycode.Skeleton_getBone(this.__ptr, index)
}

Skeleton.prototype.addBone = function(bone) {
	Polycode.Skeleton_addBone(this.__ptr, bone)
}

Skeleton.prototype.removeBone = function(bone) {
	Polycode.Skeleton_removeBone(this.__ptr, bone)
}

Skeleton.prototype.getBoneIndexByBone = function(bone) {
	Polycode.Skeleton_getBoneIndexByBone(this.__ptr, bone)
}
