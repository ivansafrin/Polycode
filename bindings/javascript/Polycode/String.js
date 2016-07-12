function String() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.String()
	}
	Object.defineProperties(this, {
		'contents': { enumerable: true, configurable: true, get: String.prototype.__get_contents, set: String.prototype.__set_contents},
		'w_contents': { enumerable: true, configurable: true, get: String.prototype.__get_w_contents, set: String.prototype.__set_w_contents}
	})
}

String.ENCODING_UTF8 = 0

String.prototype.__get_contents = function() {
	var retVal = new string("__skip_ptr__")
	retVal.__ptr = 	Polycode.String__get_contents(this.__ptr)
	return retVal
}

String.prototype.__set_contents = function(val) {
	Polycode.String__set_contents(this.__ptr, val.__ptr)
}

String.prototype.__get_w_contents = function() {
	var retVal = new wstring("__skip_ptr__")
	retVal.__ptr = 	Polycode.String__get_w_contents(this.__ptr)
	return retVal
}

String.prototype.__set_w_contents = function(val) {
	Polycode.String__set_w_contents(this.__ptr, val.__ptr)
}

Duktape.fin(String.prototype, function (x) {
	if (x === String.prototype) {
		return;
	}
	Polycode.String__delete(x.__ptr)
})

String.prototype.size = function() {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_size(this.__ptr)
	return retVal
}

String.prototype.length = function() {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_length(this.__ptr)
	return retVal
}

String.prototype.substr = function(pos,n) {
	return Polycode.String_substr(this.__ptr, pos, n)
}

String.prototype.rfind = function(str,pos) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_rfind(this.__ptr, str, pos)
	return retVal
}

String.prototype.find = function(str,pos) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_find(this.__ptr, str, pos)
	return retVal
}

String.prototype.find_last_of = function(str,pos) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_find_last_of(this.__ptr, str, pos)
	return retVal
}

String.prototype.find_first_of = function(str,pos) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_find_first_of(this.__ptr, str, pos)
	return retVal
}

String.prototype.find_first_not_of = function(str,pos) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_find_first_not_of(this.__ptr, str, pos)
	return retVal
}

String.prototype.toLowerCase = function() {
	return Polycode.String_toLowerCase(this.__ptr)
}

String.prototype.toUpperCase = function() {
	return Polycode.String_toUpperCase(this.__ptr)
}

String.prototype.split = function(delim) {
	Polycode.String_split(this.__ptr, delim)
}

String.prototype.replace = function(what,withWhat) {
	return Polycode.String_replace(this.__ptr, what, withWhat)
}

String.prototype.NumberToString = function(value,precision) {
	return Polycode.String_NumberToString(value, precision)
}

String.prototype.toNumber = function() {
	return Polycode.String_toNumber(this.__ptr)
}

String.prototype.toInteger = function() {
	return Polycode.String_toInteger(this.__ptr)
}

String.prototype.IntToString = function(value) {
	return Polycode.String_IntToString(value)
}

String.prototype.append = function(c) {
	Polycode.String_append(this.__ptr, c)
}

String.prototype.getDataSizeWithEncoding = function(encoding) {
	var retVal = new size_t("__skip_ptr__")
	retVal.__ptr = Polycode.String_getDataSizeWithEncoding(this.__ptr, encoding)
	return retVal
}

String.prototype.isNumber = function() {
	return Polycode.String_isNumber(this.__ptr)
}

String.prototype.isInteger = function() {
	return Polycode.String_isInteger(this.__ptr)
}
