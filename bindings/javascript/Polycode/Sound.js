function Sound(fileName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Sound(fileName)
	}
}

Duktape.fin(Sound.prototype, function (x) {
	if (x === Sound.prototype) {
		return;
	}
	Polycode.Sound__delete(x.__ptr)
})

Sound.prototype.getSampleAsNumber = function(offset,channel,position,orientation) {
	return Polycode.Sound_getSampleAsNumber(this.__ptr, offset, channel, position, orientation)
}

Sound.prototype.loadFile = function(fileName) {
	Polycode.Sound_loadFile(this.__ptr, fileName)
}

Sound.prototype.Play = function(loop,restartSound) {
	Polycode.Sound_Play(this.__ptr, loop, restartSound)
}

Sound.prototype.Stop = function() {
	Polycode.Sound_Stop(this.__ptr)
}

Sound.prototype.setVolume = function(newVolume) {
	Polycode.Sound_setVolume(this.__ptr, newVolume)
}

Sound.prototype.getVolume = function() {
	return Polycode.Sound_getVolume(this.__ptr)
}

Sound.prototype.setPitch = function(newPitch) {
	Polycode.Sound_setPitch(this.__ptr, newPitch)
}

Sound.prototype.getPitch = function() {
	return Polycode.Sound_getPitch(this.__ptr)
}

Sound.prototype.isPlaying = function() {
	return Polycode.Sound_isPlaying(this.__ptr)
}

Sound.prototype.isLooped = function() {
	return Polycode.Sound_isLooped(this.__ptr)
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
	return Polycode.Sound_getFileName(this.__ptr)
}

Sound.prototype.getPlaybackDuration = function() {
	return Polycode.Sound_getPlaybackDuration(this.__ptr)
}

Sound.prototype.getPlaybackTime = function() {
	return Polycode.Sound_getPlaybackTime(this.__ptr)
}

Sound.prototype.seekTo = function(time) {
	Polycode.Sound_seekTo(this.__ptr, time)
}

Sound.prototype.getOffset = function() {
	return Polycode.Sound_getOffset(this.__ptr)
}

Sound.prototype.getSampleLength = function() {
	return Polycode.Sound_getSampleLength(this.__ptr)
}

Sound.prototype.getFrequency = function() {
	return Polycode.Sound_getFrequency(this.__ptr)
}

Sound.prototype.setPositionalProperties = function(referenceDistance,maxDistance) {
	Polycode.Sound_setPositionalProperties(this.__ptr, referenceDistance, maxDistance)
}

Sound.prototype.setReferenceDistance = function(referenceDistance) {
	Polycode.Sound_setReferenceDistance(this.__ptr, referenceDistance)
}

Sound.prototype.setMaxDistance = function(maxDistance) {
	Polycode.Sound_setMaxDistance(this.__ptr, maxDistance)
}

Sound.prototype.getReferenceDistance = function() {
	return Polycode.Sound_getReferenceDistance(this.__ptr)
}

Sound.prototype.getMaxDistance = function() {
	return Polycode.Sound_getMaxDistance(this.__ptr)
}

Sound.prototype.loadBytes = function(data,size,channels,freq,format) {
	return Polycode.Sound_loadBytes(this.__ptr, data.__ptr, size, channels, freq, format)
}

Sound.prototype.loadWAV = function(fileName) {
	return Polycode.Sound_loadWAV(this.__ptr, fileName)
}

Sound.prototype.loadOGG = function(fileName) {
	return Polycode.Sound_loadOGG(this.__ptr, fileName)
}

Sound.prototype.soundCheck = function(result,err) {
	Polycode.Sound_soundCheck(this.__ptr, result, err)
}

Sound.prototype.updateStream = function(streamCount) {
	Polycode.Sound_updateStream(this.__ptr, streamCount)
}
