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

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyImage.h"

#include "PolyFont.h"

#include FT_GLYPH_H
#include FT_IMAGE_H

namespace Polycode {

class Font;

class GlyphData {
	public:
		GlyphData();
		~GlyphData();

		void clearData();

		FT_Glyph *glyphs;
		FT_Vector *positions;
		FT_UInt num_glyphs;

		int trailingAdvance;
};

class ColorRange {
	public:
		ColorRange(Color color, unsigned int rangeStart, unsigned int rangeEnd);
		Color color;
		unsigned int rangeStart;
		unsigned int rangeEnd;
};

class _PolyExport Label : public Image {
	public:

		Label(Font *font, const String& text, int size, int antiAliasMode, bool premultiplyAlpha = false);
		virtual ~Label();
		void setText(const String& text);
		const String& getText() const;

		int getTextWidthForString(const String& text);
		int getTextHeightForString(const String& text);

		void computeStringBbox(GlyphData *glyphData, FT_BBox *abbox);
		void precacheGlyphs(String text, GlyphData *glyphData);

		void renderGlyphs(GlyphData *glyphData);

		void drawGlyphBitmap(FT_Bitmap *bitmap, unsigned int x, unsigned int y, Color glyphColor);

		Number getTextWidth() const;
		Number getTextHeight() const;

		void clearColors();
		void setColorForRange(Color color, unsigned int rangeStart, unsigned int rangeEnd);

		Color getColorForIndex(unsigned int index);

		void setFont(Font *newFont);
		Font *getFont() const;

		void setSize(int newSize);
		unsigned int getSize() const;

		int getAntialiasMode() const;
		void setAntialiasMode(int newMode);

		bool optionsChanged();

		static const int ANTIALIAS_FULL = 0;
		static const int ANTIALIAS_NONE = 1;
		static const int ANTIALIAS_STRONG = 2;

		int getBaselineAdjust();

	protected:

		bool _optionsChanged;
		GlyphData labelData;

		std::vector<ColorRange> colorRanges;

		int baseLineOffset;
		int xAdjustOffset;
		int baseLineAdjust;
		bool premultiplyAlpha;

		int antiAliasMode;
		int size;
		String text;
		Font *font;
};

}
