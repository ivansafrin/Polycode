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
	
	class _PolyExport FontManager {
	public:
		FontManager();
		~FontManager();

		void registerFont(String fontName, String fontPath);		
		Font *getFontByName(String fontName);		
		
	private:
		
		vector <FontEntry> fonts;
		
	};
	
}