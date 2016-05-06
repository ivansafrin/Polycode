function TimerManager() {
}

TimerManager.prototype.removeTimer = function(timer) {
	Polycode.TimerManager_removeTimer(this.__ptr, timer)
}

TimerManager.prototype.addTimer = function(timer) {
	Polycode.TimerManager_addTimer(this.__ptr, timer)
}

TimerManager.prototype.Update = function() {
	Polycode.TimerManager_Update(this.__ptr)
}
