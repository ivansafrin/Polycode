/*
 *  PolyFont.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "OSBasics.h"

using namespace std;

namespace Polycode {
	
	class _PolyExport Font {
		public:
			Font(string fileName);
			~Font();
			
			FT_Face getFace();
			bool isValid();
		private:
			unsigned char *buffer;
			bool valid;
			FT_Face ftFace;
	};
}