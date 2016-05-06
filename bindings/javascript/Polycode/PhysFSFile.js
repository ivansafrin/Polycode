function PhysFSFile() {
}

PhysFSFile.prototype.read = function(ptr,size,count) {
	Polycode.PhysFSFile_read(this.__ptr, ptr,size,count)
}

PhysFSFile.prototype.write = function(ptr,size,count) {
	Polycode.PhysFSFile_write(this.__ptr, ptr,size,count)
}

PhysFSFile.prototype.seek = function(offset,origin) {
	Polycode.PhysFSFile_seek(this.__ptr, offset,origin)
}

PhysFSFile.prototype.tell = function() {
	Polycode.PhysFSFile_tell(this.__ptr)
}
