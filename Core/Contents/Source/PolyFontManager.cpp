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

#include "PolyFontManager.h"
#include "PolyFont.h"

using namespace Polycode;

FontManager::FontManager() {

}

FontManager::~FontManager() {
	for(int i=0; i < fonts.size(); i++) {
		FontEntry entry = fonts[i];
		delete entry.font;
	}
	fonts.clear();
}

unsigned int FontManager::getNumFonts() const {
	return fonts.size();
}

FontEntry *FontManager::getFontEntryByIndex(const unsigned int index) {
	if(index < fonts.size()) {
		return &fonts[index];
	} else {
		return NULL;
	}
}

void FontManager::removeFontEntry(FontEntry *entry, bool deleteFont) {
	for(int i=0; i < fonts.size(); i++) {
		FontEntry *listEntry = &fonts[i];
		if(listEntry == entry) {
			if(deleteFont) {
				delete listEntry->font;
			}
			fonts.erase(fonts.begin()+i);
			return;
		}
	}
}

void FontManager::registerFont(const String& fontName, const String& fontPath) {
	Font *font = new Font(fontPath);
	if(font->loaded) {
		FontEntry newEntry;
		newEntry.font = font;
		newEntry.fontName = fontName;
		font->setFontName(fontName);
		fonts.push_back(newEntry);
	} else {
		delete font;
	}
}

FontEntry *FontManager::getFontEntryByFontPath(const String &fontPath) {
	for(int i=0; i < fonts.size(); i++) {
		FontEntry *entry = &fonts[i];
		if(entry->font->getFontPath() == fontPath) {
			return entry;
		}
	}
	return NULL;
}

Font *FontManager::getFontByName(const String& fontName) {
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
