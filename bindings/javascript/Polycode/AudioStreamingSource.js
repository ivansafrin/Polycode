function AudioStreamingSource() {
}

AudioStreamingSource.prototype.getNumChannels = function() {
	return Polycode.AudioStreamingSource_getNumChannels(this.__ptr)
}

AudioStreamingSource.prototype.getFrequency = function() {
	return Polycode.AudioStreamingSource_getFrequency(this.__ptr)
}
