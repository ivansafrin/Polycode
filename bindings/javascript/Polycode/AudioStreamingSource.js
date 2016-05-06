function AudioStreamingSource() {
}

AudioStreamingSource.prototype.getNumChannels = function() {
	Polycode.AudioStreamingSource_getNumChannels(this.__ptr)
}

AudioStreamingSource.prototype.getFrequency = function() {
	Polycode.AudioStreamingSource_getFrequency(this.__ptr)
}
