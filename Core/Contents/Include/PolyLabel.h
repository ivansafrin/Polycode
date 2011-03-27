/*
 *  PolyLabel.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyFont.h"
#include "PolyImage.h"
#include "PolyUtil.h"

#include <string>
using namespace std;

using std::wstring;

#define TAB_REPLACE "    "

namespace Polycode {

	class _PolyExport Label : public Image {
		public:
			
			Label(Font *font, String text, int size, int antiAliasMode);
			~Label();
			void setText(String text);
			String getText();
			int getTextWidth(Font *font, String text, int size);
			int getTextHeight(Font *font, String text, int size);
					
			Number getTextWidth();		
			Number getTextHeight();
		
			Font *getFont();
					
			static const int ANTIALIAS_FULL = 0;
			static const int ANTIALIAS_NONE = 1;
			
		private:

			Number currentTextWidth;
			Number currentTextHeight;
			int antiAliasMode;
			int size;
			String text;
			Font *font;
	};

}