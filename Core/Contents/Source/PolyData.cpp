
#include "PolyData.h"


using namespace Polycode;

Data::Data() {
	data = NULL;
	dataSize = 0;
}

Data::~Data() {
	if(data)
		free(data);
}

void Data::setFromString(String str, int encoding) {
	if(data)
		free(data);

	dataSize = str.getDataSizeWithEncoding(encoding);
	data = (char*)malloc(dataSize);
	memcpy(data, str.getDataWithEncoding(encoding), dataSize);
}

bool Data::saveToFile(String fileName) {
	
	OSFILE *file = OSBasics::open(fileName, "wb");
	
	if(!file) {
		OSBasics::close(file);		
		return false;
	}
	
	OSBasics::write(data, sizeof(char), dataSize, file);	
	OSBasics::close(file);	
	
	return true;
}

void Data::loadFromFile(String fileName) {
	OSFILE *file = OSBasics::open(fileName, "rb");
	
	OSBasics::seek(file, 0L, SEEK_END);
	dataSize = OSBasics::tell(file);
	OSBasics::seek(file, 0L, SEEK_SET);
	
	if(data)
		free(data);
	
	data = (char*)malloc(dataSize);
	if(!data) {
		OSBasics::close(file);		
		return;
	}
	
	OSBasics::read(data, sizeof(char), dataSize, file);	
	OSBasics::close(file);
		
}

String Data::getAsString(int encoding) {
	String str;
	
	char *strData = (char*)malloc(dataSize+1);
	memcpy(strData, data, dataSize);
	memset(strData+dataSize, 0, 1);
	str.setDataWithEncoding(strData, encoding);
	free(strData);
	return str;
}