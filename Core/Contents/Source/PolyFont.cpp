/*
 *  PolyFont.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyFont.h"

using namespace Polycode;

Font::Font(string fileName) {
	FT_Library FTLibrary;
	FT_Init_FreeType(&FTLibrary);
	
	OSFILE *file = OSBasics::open(fileName, "rb");
	OSBasics::seek(file, 0, SEEK_END);	
	long progsize = OSBasics::tell(file);
	OSBasics::seek(file, 0, SEEK_SET);
	buffer = (unsigned char*)malloc(progsize);
	memset(buffer, 0, progsize);
	OSBasics::read(buffer, progsize, 1, file);
	
	valid = true;
	if(FT_New_Memory_Face(FTLibrary, buffer, progsize, 0, &ftFace) != 0) {
		Logger::log("Error loading font %s\n", fileName.c_str());
		valid = false;
	}
	
	FT_Select_Charmap(ftFace, FT_ENCODING_UNICODE);	
	//FT_New_Face(FTLibrary, fileName.c_str(), 0, &ftFace);	
//	free(buffer);
}

bool Font::isValid() {
	return valid;
}

Font::~Font() {
	free(buffer);
}

FT_Face Font::getFace() {
	return ftFace;
}