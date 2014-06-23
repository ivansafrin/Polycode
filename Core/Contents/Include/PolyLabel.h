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

	/**
     * An image that can render text into itself. This class is mostly used internally in SceneLabel, but can be used by itself to manually create text-based textures.
     */
	class _PolyExport Label : public Image {
		public:
			
            /**
             * Create a text label.
             * @param font Font to use for this label.
             * @param text Initial text to render.
             * @param size Pixel size of the text to render.
             * @param antiAliasMode Antialiasing mode. Can be ANTIALIAS_FULL, ANTIALIAS_NONE or ANTIALIAS_STRONG.
             * @param premultiplyAlpha If set to true, will premultiply alpha in the label image.
             * @see Font
             */
			Label(Font *font, const String& text, int size, int antiAliasMode, bool premultiplyAlpha = false);
			virtual ~Label();
        
            /**
             * Sets the text of the label.
             * @param text Text to set.
             */
			void setText(const String& text);
        
            /**
             * Returns the current text of the label.
             * @return Current text.
             */
			const String& getText() const;
			
            /**
             * Returns the pixel width for the specified string based on the current label font and size settings.
             * @param text Text to return width for.
             * @return Pixel width of specified text.
             */
			int getTextWidthForString(const String& text);
        
            /**
             * Returns the pixel height for the specified string based on the current label font and size settings.
             * @param text Text to return height for.
             * @return Pixel height of specified text.
             */
			int getTextHeightForString(const String& text);

            /**
             * Returns the width of the current text.
             * @return Width of the current text.
             */
			Number getTextWidth() const;
        
            /**
             * Returns the height of the current text.
             * @return Height of the current text.
             */
			Number getTextHeight() const;
		
            /**
             * Sets the color for a range of characters in the label. The colors are only applied upon the next call to setText, not the currently rendered text. This call appends the color range to a list of color ranges, so if you are calling this multiple times for the same ranges, you must call clearColors.
             * @param color The color to set for the specified range.
             * @param rangeStart Starting index of the specified range.
             * @param rangeEnd Ending index of the specified range.
             * @see clearColors
             */
			void setColorForRange(Color color, unsigned int rangeStart, unsigned int rangeEnd);
        
            /**
             * Clears the current label colors.
             * @see setColorForRange
             */
            void clearColors();
		
            /**
             * Returns the text color for specified character index.
             */
			Color getColorForIndex(unsigned int index);
        
            /**
             * Returns the premultiply alpha setting.
             */
            bool getPremultiplyAlpha() const;
        
            /**
             * If set to true, will premultiply alpha when text is set to the label.
             */
            void setPremultiplyAlpha(bool val);
		
            /**
             * Sets the Font used to render text in the label.
             * @see Font
             */
			void setFont(Font *newFont);
        
            /**
             * Returns the Font currently used to render text in the label.
             * @see Font
             */
			Font *getFont() const;
			
            /**
             * Sets the vertical pixel size of text rendered in the label.
             */
			void setSize(int newSize);
        
            /**
             * Return the current vertical pixel size of text rendered in the label.
             */
			unsigned int getSize() const;
			
            /**
             * Returns the current antialasing mode.
             */
			int getAntialiasMode() const;
        
            /**
             * Sets the antialiasing mode used to render text.
             * @param newMode Antialiasing mode. Can be ANTIALIAS_FULL, ANTIALIAS_NONE or ANTIALIAS_STRONG.
             */
			void setAntialiasMode(int newMode);
					
			static const int ANTIALIAS_FULL = 0;
			static const int ANTIALIAS_NONE = 1;
			static const int ANTIALIAS_STRONG = 2;			
			
            /**
             * Returns the pixel distance from top of image to the baseline of the rendered text.
             */
			int getBaselineAdjust();
        
			bool optionsChanged();
			
		protected:
        
            void computeStringBbox(GlyphData *glyphData, FT_BBox *abbox);
            void precacheGlyphs(String text, GlyphData *glyphData);
            void renderGlyphs(GlyphData *glyphData);
            void drawGlyphBitmap(FT_Bitmap *bitmap, unsigned int x, unsigned int y, Color glyphColor);
		
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
