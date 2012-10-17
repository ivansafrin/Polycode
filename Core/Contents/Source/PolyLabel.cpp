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

#include "PolyLabel.h"
#include "PolyFont.h"

using namespace Polycode;

#define NORMAL_FT_FLAGS FT_LOAD_TARGET_LIGHT

ColorRange::ColorRange(Color color, unsigned int rangeStart, unsigned int rangeEnd) {
	this->color = color;
	this->rangeStart = rangeStart;
	this->rangeEnd = rangeEnd;	
}


Label::Label(Font *font, const String& text, int size, int antiAliasMode, bool premultiplyAlpha) : Image() {
		setPixelType(Image::IMAGE_RGBA);
		this->font = font;
		this->size = size;
		this->premultiplyAlpha = premultiplyAlpha;
		imageData = NULL;
		this->antiAliasMode = antiAliasMode;
		currentTextWidth = 0;
		currentTextHeight = 0;
		setText(text);
}

Label::~Label() {

}

int Label::getTextWidth(Font *font, const String& text, int size) {
	FT_Vector delta;
	FT_UInt previous = 0;
	FT_UInt glyph_index;
	FT_GlyphSlot slot = font->getFace()->glyph;
	FT_Set_Pixel_Sizes(font->getFace(), 0,  size);
	int width = 0;
	
	String actualString = text; //StringUtil::replace(text, "\t", TAB_REPLACE);
	
	for(int i=0; i< actualString.length();i++)
	{
		if(actualString[i] == '\t') {
			glyph_index = FT_Get_Char_Index( font->getFace(), ' ');			
			FT_Load_Glyph( font->getFace(), glyph_index, NORMAL_FT_FLAGS );
			for(int k=0 ; k < 4; k++) {
					FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);		
					width += slot->advance.x >> 6;				
			}
			
		} else {
			glyph_index = FT_Get_Char_Index( font->getFace(), actualString[i] );
			if(previous && glyph_index) {
				FT_Get_Kerning(font->getFace(), previous, glyph_index, FT_KERNING_DEFAULT, &delta);
				width += delta.x >> 6;
			}
			FT_Load_Glyph( font->getFace(), glyph_index, NORMAL_FT_FLAGS );
			
			FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);

		width += slot->advance.x >> 6;
		}
	}

	// +5 pixels safety zone :)
	return width+5;
}

int Label::getTextHeight(Font *font, const String& text, int size) {
	
	String actualString = text; //StringUtil::replace(text, "\t", TAB_REPLACE);
	
	int height = 0;
	
	FT_UInt glyph_index;
	FT_GlyphSlot slot = font->getFace()->glyph;
	FT_Set_Pixel_Sizes(font->getFace(), 0,  size);
	
	for(int i=0; i< actualString.length();i++)
	{
		glyph_index = FT_Get_Char_Index( font->getFace(), actualString[i] );
		FT_Load_Glyph(font->getFace(), glyph_index, NORMAL_FT_FLAGS );
		FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);
		
		if(slot->bitmap_top > height)
			height = slot->bitmap_top;
	}
		
	return height;
}

Number Label::getTextWidth() const {
	return currentTextWidth;
}

Number Label::getTextHeight() const {
	return currentTextHeight;
}

Font *Label::getFont() const {
	return font;
}

const String& Label::getText() const {
	return text;
}

void Label::clearColors() {
	colorRanges.clear();
}

void Label::setColorForRange(Color color, unsigned int rangeStart, unsigned int rangeEnd) {
	colorRanges.push_back(ColorRange(color, rangeStart, rangeEnd));
}

Color Label::getColorForIndex(unsigned int index) {
	for(int i=0; i < colorRanges.size(); i++) {
		if(index >= colorRanges[i].rangeStart && index <= colorRanges[i].rangeEnd) {
			return colorRanges[i].color;
		}
	}
	return Color(1.0,1.0,1.0,1.0);
}

void Label::setText(const String& text) {
//	Logger::logw((char*)text.c_str());
	
	this->text = text;
	
	if(!font)
		return;
	
	if(!font->isValid())
		return;
	
	String actualString = text; //StringUtil::replace(text, "\t", TAB_REPLACE);
	
	int textWidth = getTextWidth(font, actualString, size);
	int textHeight = size+getTextHeight(font, actualString, size);
	currentTextHeight = 0;
	
	createEmpty(textWidth,textHeight);
	
	int penX = 0;
	int xoff = 0;
//	int x,y;
	FT_Vector delta;
	FT_UInt previous = 0;
	FT_UInt glyph_index;
	FT_GlyphSlot slot = font->getFace()->glyph;
	FT_Set_Pixel_Sizes(font->getFace(), 0,  size);

	// copy the freetype data into the texture
	for(int i=0; i< actualString.length();i++)
	{
		if(actualString[i] == (wchar_t)'\t') {
			glyph_index = FT_Get_Char_Index( font->getFace(), ' ');			
			FT_Load_Glyph( font->getFace(), glyph_index, NORMAL_FT_FLAGS );
			for(int k=0 ; k < 4; k++) {
				FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);		
				penX += slot->advance.x >> 6;
				currentTextWidth = penX;
				previous = glyph_index;				
			}
			
		} else {	
		glyph_index = FT_Get_Char_Index( font->getFace(), (FT_ULong)actualString[i]);
		if(previous && glyph_index) {
			FT_Get_Kerning(font->getFace(), previous, glyph_index, FT_KERNING_DEFAULT, &delta);
			penX += delta.x >> 6;
		}
		FT_Load_Glyph(font->getFace(), glyph_index, NORMAL_FT_FLAGS);
		switch(antiAliasMode) {
			case ANTIALIAS_FULL:
				FT_Render_Glyph(slot, FT_RENDER_MODE_LIGHT );			
			break;
			case ANTIALIAS_NONE:
				FT_Render_Glyph(slot, FT_RENDER_MODE_MONO);
			break;
		}
		
		Color glyphColor = getColorForIndex(i);

		int lineoffset = ((size-slot->bitmap_top) * (textWidth*4));
		xoff = ((penX + slot->bitmap_left)*4);
		
		switch(antiAliasMode) {
			case ANTIALIAS_FULL:
				for(int j = 0; j < ((slot->bitmap.width * slot->bitmap.rows)); j++) {
					if(!(j%slot->bitmap.width) && j !=0)
						lineoffset += (textWidth*4)-(slot->bitmap.width * 4);

						int newVal = imageData[xoff+lineoffset+3] + slot->bitmap.buffer[j];
						if(newVal > 255)
							newVal = 255;
							
						newVal = (int)(((Number)newVal) * glyphColor.a);
						
						imageData[xoff+lineoffset+3] = newVal;
													
						if(premultiplyAlpha) {
							imageData[xoff+lineoffset] = (int)((255.0 * glyphColor.r) * ((Number)imageData[xoff+lineoffset+3])/255.0);
							imageData[xoff+lineoffset+1] =  (int)((255.0 * glyphColor.g) * ((Number)imageData[xoff+lineoffset+3])/255.0);
							imageData[xoff+lineoffset+2] =  (int)((255.0 * glyphColor.b) * ((Number)imageData[xoff+lineoffset+3])/255.0);
						} else {
							imageData[xoff+lineoffset] = (int)(255.0 * glyphColor.r);
							imageData[xoff+lineoffset+1] =  (int)(255.0 * glyphColor.g);
							imageData[xoff+lineoffset+2] =  (int)(255.0 * glyphColor.b);						
						} 	
							
						xoff += 4;
				}
			break;
			case ANTIALIAS_NONE:
				unsigned char *src =  slot->bitmap.buffer;
				for(int j=0; j <slot->bitmap.rows;j++) {
					unsigned char b;
					unsigned char *bptr =  src;
					for(int k=0; k < slot->bitmap.width ; k++){					
						if (k%8==0){ b = (*bptr++);}
						imageData[xoff+lineoffset] = (int)(255.0 * glyphColor.r);
						imageData[xoff+lineoffset+1] =  (int)(255.0 * glyphColor.g);
						imageData[xoff+lineoffset+2] =  (int)(255.0 * glyphColor.b);
						imageData[xoff+lineoffset+3] =  b&0x80 ? 255 : 0;
						xoff += 4;
						b <<= 1;
					}
					lineoffset += (textWidth*4)-(slot->bitmap.width * 4);
					src += slot->bitmap.pitch;
				}
			break;
		}
		
		if(slot->bitmap_top > currentTextHeight)
			currentTextHeight = slot->bitmap_top;
		
		penX += slot->advance.x >> 6;
		currentTextWidth = penX;
		previous = glyph_index;
		}
	}

}
