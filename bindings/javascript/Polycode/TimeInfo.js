function TimeInfo() {
	Object.defineProperties(this, {
		'seconds': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_seconds, set: TimeInfo.prototype.__set_seconds},
		'minutes': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_minutes, set: TimeInfo.prototype.__set_minutes},
		'hours': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_hours, set: TimeInfo.prototype.__set_hours},
		'month': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_month, set: TimeInfo.prototype.__set_month},
		'monthDay': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_monthDay, set: TimeInfo.prototype.__set_monthDay},
		'weekDay': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_weekDay, set: TimeInfo.prototype.__set_weekDay},
		'year': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_year, set: TimeInfo.prototype.__set_year},
		'yearDay': { enumerable: true, configurable: true, get: TimeInfo.prototype.__get_yearDay, set: TimeInfo.prototype.__set_yearDay}
	})
}
TimeInfo.prototype.__get_seconds = function() {
	return Polycode.TimeInfo__get_seconds(this.__ptr)
}

TimeInfo.prototype.__set_seconds = function(val) {
	Polycode.TimeInfo__set_seconds(this.__ptr, val)
}

TimeInfo.prototype.__get_minutes = function() {
	return Polycode.TimeInfo__get_minutes(this.__ptr)
}

TimeInfo.prototype.__set_minutes = function(val) {
	Polycode.TimeInfo__set_minutes(this.__ptr, val)
}

TimeInfo.prototype.__get_hours = function() {
	return Polycode.TimeInfo__get_hours(this.__ptr)
}

TimeInfo.prototype.__set_hours = function(val) {
	Polycode.TimeInfo__set_hours(this.__ptr, val)
}

TimeInfo.prototype.__get_month = function() {
	return Polycode.TimeInfo__get_month(this.__ptr)
}

TimeInfo.prototype.__set_month = function(val) {
	Polycode.TimeInfo__set_month(this.__ptr, val)
}

TimeInfo.prototype.__get_monthDay = function() {
	return Polycode.TimeInfo__get_monthDay(this.__ptr)
}

TimeInfo.prototype.__set_monthDay = function(val) {
	Polycode.TimeInfo__set_monthDay(this.__ptr, val)
}

TimeInfo.prototype.__get_weekDay = function() {
	return Polycode.TimeInfo__get_weekDay(this.__ptr)
}

TimeInfo.prototype.__set_weekDay = function(val) {
	Polycode.TimeInfo__set_weekDay(this.__ptr, val)
}

TimeInfo.prototype.__get_year = function() {
	return Polycode.TimeInfo__get_year(this.__ptr)
}

TimeInfo.prototype.__set_year = function(val) {
	Polycode.TimeInfo__set_year(this.__ptr, val)
}

TimeInfo.prototype.__get_yearDay = function() {
	return Polycode.TimeInfo__get_yearDay(this.__ptr)
}

TimeInfo.prototype.__set_yearDay = function(val) {
	Polycode.TimeInfo__set_yearDay(this.__ptr, val)
}

Duktape.fin(TimeInfo.prototype, function (x) {
	if (x === TimeInfo.prototype) {
		return;
	}
	Polycode.TimeInfo__delete(x.__ptr)
})
