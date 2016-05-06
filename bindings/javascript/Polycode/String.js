function String() {
}

String.prototype.size = function() {
	Polycode.String_size(this.__ptr)
}

String.prototype.length = function() {
	Polycode.String_length(this.__ptr)
}

String.prototype.substr = function(pos,n) {
	Polycode.String_substr(this.__ptr, pos,n)
}

String.prototype.rfind = function(str,pos) {
	Polycode.String_rfind(this.__ptr, str,pos)
}

String.prototype.find = function(str,pos) {
	Polycode.String_find(this.__ptr, str,pos)
}

String.prototype.find_last_of = function(str,pos) {
	Polycode.String_find_last_of(this.__ptr, str,pos)
}

String.prototype.find_first_of = function(str,pos) {
	Polycode.String_find_first_of(this.__ptr, str,pos)
}

String.prototype.toLowerCase = function() {
	Polycode.String_toLowerCase(this.__ptr)
}

String.prototype.toUpperCase = function() {
	Polycode.String_toUpperCase(this.__ptr)
}

String.prototype.split = function(delim) {
	Polycode.String_split(this.__ptr, delim)
}

String.prototype.replace = function(what,withWhat) {
	Polycode.String_replace(this.__ptr, what,withWhat)
}

String.prototype.toNumber = function() {
	Polycode.String_toNumber(this.__ptr)
}

String.prototype.toInteger = function() {
	Polycode.String_toInteger(this.__ptr)
}

String.prototype.c_str = function() {
	Polycode.String_c_str(this.__ptr)
}

String.prototype.getDataWithEncoding = function(encoding) {
	Polycode.String_getDataWithEncoding(this.__ptr, encoding)
}

String.prototype.getWDataWithEncoding = function(encoding) {
	Polycode.String_getWDataWithEncoding(this.__ptr, encoding)
}

String.prototype.append = function(c) {
	Polycode.String_append(this.__ptr, c)
}

String.prototype.getDataSizeWithEncoding = function(encoding) {
	Polycode.String_getDataSizeWithEncoding(this.__ptr, encoding)
}

String.prototype.setDataWithEncoding = function(data,encoding) {
	Polycode.String_setDataWithEncoding(this.__ptr, data,encoding)
}

String.prototype.isNumber = function() {
	Polycode.String_isNumber(this.__ptr)
}
