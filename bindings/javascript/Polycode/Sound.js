function Sound() {
}

Sound.prototype.getSampleAsNumber = function(offset,channel) {
	Polycode.Sound_getSampleAsNumber(this.__ptr, offset,channel)
}

Sound.prototype.loadFile = function(fileName) {
	Polycode.Sound_loadFile(this.__ptr, fileName)
}

Sound.prototype.Play = function(loop,restartSound) {
	Polycode.Sound_Play(this.__ptr, loop,restartSound)
}

Sound.prototype.Stop = function() {
	Polycode.Sound_Stop(this.__ptr)
}

Sound.prototype.setVolume = function(newVolume) {
	Polycode.Sound_setVolume(this.__ptr, newVolume)
}

Sound.prototype.getVolume = function() {
	Polycode.Sound_getVolume(this.__ptr)
}

Sound.prototype.setPitch = function(newPitch) {
	Polycode.Sound_setPitch(this.__ptr, newPitch)
}

Sound.prototype.getPitch = function() {
	Polycode.Sound_getPitch(this.__ptr)
}

Sound.prototype.isPlaying = function() {
	Polycode.Sound_isPlaying(this.__ptr)
}

Sound.prototype.isLooped = function() {
	Polycode.Sound_isLooped(this.__ptr)
}

Sound.prototype.setIsPositional = function(isPositional) {
	Polycode.Sound_setIsPositional(this.__ptr, isPositional)
}

Sound.prototype.setSoundPosition = function(position) {
	Polycode.Sound_setSoundPosition(this.__ptr, position)
}

Sound.prototype.setSoundVelocity = function(velocity) {
	Polycode.Sound_setSoundVelocity(this.__ptr, velocity)
}

Sound.prototype.setSoundDirection = function(direction) {
	Polycode.Sound_setSoundDirection(this.__ptr, direction)
}

Sound.prototype.setOffset = function(offset) {
	Polycode.Sound_setOffset(this.__ptr, offset)
}

Sound.prototype.getFileName = function() {
	Polycode.Sound_getFileName(this.__ptr)
}

Sound.prototype.getPlaybackDuration = function() {
	Polycode.Sound_getPlaybackDuration(this.__ptr)
}

Sound.prototype.getPlaybackTime = function() {
	Polycode.Sound_getPlaybackTime(this.__ptr)
}

Sound.prototype.seekTo = function(time) {
	Polycode.Sound_seekTo(this.__ptr, time)
}

Sound.prototype.getOffset = function() {
	Polycode.Sound_getOffset(this.__ptr)
}

Sound.prototype.getSampleLength = function() {
	Polycode.Sound_getSampleLength(this.__ptr)
}

Sound.prototype.getFrequency = function() {
	Polycode.Sound_getFrequency(this.__ptr)
}

Sound.prototype.setPositionalProperties = function(referenceDistance,maxDistance) {
	Polycode.Sound_setPositionalProperties(this.__ptr, referenceDistance,maxDistance)
}

Sound.prototype.setReferenceDistance = function(referenceDistance) {
	Polycode.Sound_setReferenceDistance(this.__ptr, referenceDistance)
}

Sound.prototype.setMaxDistance = function(maxDistance) {
	Polycode.Sound_setMaxDistance(this.__ptr, maxDistance)
}

Sound.prototype.getReferenceDistance = function() {
	Polycode.Sound_getReferenceDistance(this.__ptr)
}

Sound.prototype.getMaxDistance = function() {
	Polycode.Sound_getMaxDistance(this.__ptr)
}

Sound.prototype.loadBytes = function(data,size,channels,freq,format) {
	Polycode.Sound_loadBytes(this.__ptr, data,size,channels,freq,format)
}

Sound.prototype.loadWAV = function(fileName) {
	Polycode.Sound_loadWAV(this.__ptr, fileName)
}

Sound.prototype.loadOGG = function(fileName) {
	Polycode.Sound_loadOGG(this.__ptr, fileName)
}

Sound.prototype.soundCheck = function(result,err) {
	Polycode.Sound_soundCheck(this.__ptr, result,err)
}

Sound.prototype.updateStream = function(streamCount) {
	Polycode.Sound_updateStream(this.__ptr, streamCount)
}
