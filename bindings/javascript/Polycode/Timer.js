function Timer() {
}

Timer.prototype.Pause = function(paused) {
	Polycode.Timer_Pause(this.__ptr, paused)
}

Timer.prototype.isPaused = function() {
	return Polycode.Timer_isPaused(this.__ptr)
}

Timer.prototype.getTicks = function() {
	return Polycode.Timer_getTicks(this.__ptr)
}

Timer.prototype.Update = function(ticks) {
	Polycode.Timer_Update(this.__ptr, ticks)
}

Timer.prototype.Reset = function() {
	Polycode.Timer_Reset(this.__ptr)
}

Timer.prototype.hasElapsed = function() {
	return Polycode.Timer_hasElapsed(this.__ptr)
}

Timer.prototype.getElapsedf = function() {
	return Polycode.Timer_getElapsedf(this.__ptr)
}

Timer.prototype.setTimerInterval = function(msecs) {
	Polycode.Timer_setTimerInterval(this.__ptr, msecs)
}
