function DebugBackTraceEntry() {
	Object.defineProperties(this, {
		'fileName': { enumerable: true, configurable: true, get: DebugBackTraceEntry.prototype.__get_fileName, set: DebugBackTraceEntry.prototype.__set_fileName},
		'lineNumber': { enumerable: true, configurable: true, get: DebugBackTraceEntry.prototype.__get_lineNumber, set: DebugBackTraceEntry.prototype.__set_lineNumber}
	})
}
DebugBackTraceEntry.prototype.__get_fileName = function() {
	return Polycode.DebugBackTraceEntry__get_fileName(this.__ptr)
}

DebugBackTraceEntry.prototype.__set_fileName = function(val) {
	Polycode.DebugBackTraceEntry__set_fileName(this.__ptr, val)
}

DebugBackTraceEntry.prototype.__get_lineNumber = function() {
	return Polycode.DebugBackTraceEntry__get_lineNumber(this.__ptr)
}

DebugBackTraceEntry.prototype.__set_lineNumber = function(val) {
	Polycode.DebugBackTraceEntry__set_lineNumber(this.__ptr, val)
}

