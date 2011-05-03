/*
 *  PolyFontManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/3/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package Services

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyFont.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace Polycode {

	class FontEntry {
	public:
		String fontName;
		Font *font;
	};
	
	/**
	* Manages fonts. The font manager shoudl only be accessed via the CoreServices singleton.
	*/
	class _PolyExport FontManager {
	public:
		FontManager();
		~FontManager();

		/**
		* Loads and registers a new font for use.
		* @param fontName Name to register the font as.
		* @param fontPath Filename of the font to load.
		*/
		void registerFont(String fontName, String fontPath);		
		
		/**
		* Retuns a font based on the registerd font name.
		* @param fontName Name of registered font name.
		* @return The font instance associated with the font name or NULL if one doesn't exist.
		*/		
		Font *getFontByName(String fontName);		
		
	private:
		
		vector <FontEntry> fonts;
		
	};
	
}