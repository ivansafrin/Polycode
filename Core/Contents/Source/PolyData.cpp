/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolyData.h"
#include "OSBasics.h"
#include <string.h>

using namespace Polycode;

Data::Data() {
	data = NULL;
	dataSize = 0;
}

Data::~Data() {
	if(data)
		free(data);
}

void Data::setFromString(const String& str, int encoding) {
	if(data)
		free(data);

	dataSize = str.getDataSizeWithEncoding(encoding);
	data = (char*)malloc(dataSize);
	memcpy(data, str.getDataWithEncoding(encoding), dataSize);
}

bool Data::saveToFile(const String& fileName) const {

	OSFILE *file = OSBasics::open(fileName, "wb");

	if(!file) {
		OSBasics::close(file);
		return false;
	}

	OSBasics::write(data, sizeof(char), dataSize, file);
	OSBasics::close(file);

	return true;
}

bool Data::loadFromFile(const String& fileName) {
	OSFILE *file = OSBasics::open(fileName, "rb");
	if(!file)
		return false;

	OSBasics::seek(file, 0L, SEEK_END);
	dataSize = OSBasics::tell(file);
	OSBasics::seek(file, 0L, SEEK_SET);

	if(data)
		free(data);

	data = (char*)malloc(dataSize);
	if(!data) {
		OSBasics::close(file);
		return false;
	}

	OSBasics::read(data, sizeof(char), dataSize, file);
	OSBasics::close(file);

	return true;
}

String Data::getAsString(int encoding) const {
	String str;

	char *strData = (char*)malloc(dataSize+1);
	memcpy(strData, data, dataSize);
	memset(strData+dataSize, 0, 1);
	str.setDataWithEncoding(strData, encoding);
	free(strData);
	return str;
}
