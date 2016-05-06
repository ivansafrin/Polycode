function BasicFile() {
}

BasicFile.prototype.read = function(ptr,size,count) {
	Polycode.BasicFile_read(this.__ptr, ptr,size,count)
}

BasicFile.prototype.write = function(ptr,size,count) {
	Polycode.BasicFile_write(this.__ptr, ptr,size,count)
}

BasicFile.prototype.seek = function(offset,origin) {
	Polycode.BasicFile_seek(this.__ptr, offset,origin)
}

BasicFile.prototype.tell = function() {
	Polycode.BasicFile_tell(this.__ptr)
}
