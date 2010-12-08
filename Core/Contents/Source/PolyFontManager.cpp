/*
 *  PolyFontManager.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/3/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyFontManager.h"

using namespace Polycode;

FontManager::FontManager() {
	
}

FontManager::~FontManager() {

}

void FontManager::registerFont(string fontName, string fontPath) {
	Font *font = new Font(fontPath);
	FontEntry newEntry;
	newEntry.font = font;
	newEntry.fontName = fontName;
	fonts.push_back(newEntry);
}

Font *FontManager::getFontByName(string fontName) {
	for(int i=0; i < fonts.size(); i++) {
		FontEntry entry = fonts[i];
		if(entry.fontName == fontName)
			return entry.font;
	}
	
	if(fonts.size() > 0) {
		FontEntry entry = fonts[0];
		return entry.font;		
	}
	
	return NULL;
}
