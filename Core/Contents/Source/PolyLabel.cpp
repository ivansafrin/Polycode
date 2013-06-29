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
  
using namespace Polycode;

//#define NORMAL_FT_FLAGS FT_LOAD_TARGET_LIGHT
//#define NORMAL_FT_FLAGS FT_LOAD_TARGET_LCD

GlyphData::GlyphData() {
	glyphs = NULL;
	positions = NULL;
	num_glyphs = 0;	
	trailingAdvance = 0;
}

GlyphData::~GlyphData() {
	clearData();
}

void GlyphData::clearData() {
	for(int i=0; i < num_glyphs; i++) {
		FT_Done_Glyph(glyphs[i]);
	}
	free(glyphs);
	free(positions);
	glyphs = NULL;
	positions = NULL;
	num_glyphs = 0;
	trailingAdvance = 0;
}


ColorRange::ColorRange(Color color, unsigned int rangeStart, unsigned int rangeEnd) {
	this->color = color;
	this->rangeStart = rangeStart;
	this->rangeEnd = rangeEnd;
}


Label::Label(Font *font, const String& text, int size, int antiAliasMode, bool premultiplyAlpha) : Image(), _optionsChanged(false) {
	setPixelType(Image::IMAGE_RGBA);
	this->font = font;
	this->size = size;
	this->premultiplyAlpha = premultiplyAlpha;
	imageData = NULL;
	this->antiAliasMode = antiAliasMode;
	setText(text);
}

Label::~Label() {

}

unsigned int Label::getSize() const {
	return size;
}

void Label::setSize(int newSize) {
	size = newSize;
	_optionsChanged	= true;
}

int Label::getAntialiasMode() const {
	return antiAliasMode;
}

void Label::setAntialiasMode(int newMode) {
	antiAliasMode = newMode;
	_optionsChanged	= true;	
}

int Label::getTextWidthForString(const String& text) {
	if(!font || !font->isValid())
		return 0;

	GlyphData data;
	precacheGlyphs(text, &data);

	FT_BBox bbox;
	computeStringBbox(&data, &bbox);

	return (bbox.xMax -  bbox.xMin);

}

int Label::getTextHeightForString(const String& text) {
	if(!font || !font->isValid())
		return 0;

	GlyphData data;
	precacheGlyphs(text, &data);

	FT_BBox bbox;
	computeStringBbox(&data, &bbox);

	return (bbox.yMax -  bbox.yMin);
}

void Label::computeStringBbox(GlyphData *glyphData, FT_BBox *abbox) {

	FT_BBox  bbox;
	/* initialize string bbox to "empty" values */
	bbox.xMin = bbox.yMin =  32000;
	bbox.xMax = bbox.yMax = -32000;

	/* for each glyph image, compute its bounding box, */
	/* translate it, and grow the string bbox          */
	for (int n = 0; n < glyphData->num_glyphs; n++ ) {
		FT_BBox  glyph_bbox;


		FT_Glyph_Get_CBox( glyphData->glyphs[n], ft_glyph_bbox_pixels, &glyph_bbox );

		glyph_bbox.xMin += glyphData->positions[n].x;
		glyph_bbox.xMax += glyphData->positions[n].x;
		glyph_bbox.yMin += glyphData->positions[n].y;
		glyph_bbox.yMax += glyphData->positions[n].y;

		if ( glyph_bbox.xMin < bbox.xMin )
			bbox.xMin = glyph_bbox.xMin;

		if ( glyph_bbox.yMin < bbox.yMin )
			bbox.yMin = glyph_bbox.yMin;

		if ( glyph_bbox.xMax > bbox.xMax )
			bbox.xMax = glyph_bbox.xMax;

		if ( glyph_bbox.yMax > bbox.yMax )
			bbox.yMax = glyph_bbox.yMax;
	}

	/* check that we really grew the string bbox */
	if ( bbox.xMin > bbox.xMax ) {
		bbox.xMin = 0;
		bbox.yMin = 0;
		bbox.xMax = 0;
		bbox.yMax = 0;
	}

	bbox.xMax += glyphData->trailingAdvance;

	/* return string bbox */
	*abbox = bbox;
}

Number Label::getTextWidth() const {
	return width;
}

Number Label::getTextHeight() const {
	return height;
}

Font *Label::getFont() const {
	return font;
}

void Label::setFont(Font *newFont) {
	if(!newFont)
		return;
	font = newFont;
	_optionsChanged	= true;
}

const String& Label::getText() const {
	return text;
}

void Label::clearColors() {
	colorRanges.clear();
	_optionsChanged = true;
}

void Label::setColorForRange(Color color, unsigned int rangeStart, unsigned int rangeEnd) {
	colorRanges.push_back(ColorRange(color, rangeStart, rangeEnd));
	_optionsChanged = true;	
}

Color Label::getColorForIndex(unsigned int index) {
	for(int i=0; i < colorRanges.size(); i++) {
		if(index >= colorRanges[i].rangeStart && index <= colorRanges[i].rangeEnd) {
			return colorRanges[i].color;
		}
	}
	return Color(1.0,1.0,1.0,1.0);
}

void Label::precacheGlyphs(String text, GlyphData *glyphData) {
	glyphData->clearData();

	std::wstring wstr = std::wstring(text.getWDataWithEncoding(String::ENCODING_UTF8));

	int num_chars = wstr.length();


	glyphData->glyphs = (FT_Glyph*) malloc(sizeof(FT_Glyph) * num_chars);
	glyphData->positions = (FT_Vector*) malloc(sizeof(FT_Vector) * num_chars);
	memset(glyphData->positions, 0, sizeof(FT_Vector) * num_chars);

	FT_Face face = font->getFace();
	FT_GlyphSlot  slot = face->glyph;
	FT_UInt       glyph_index;
	FT_Bool       use_kerning;
	FT_UInt       previous;

	FT_Error error;

	int pen_x = 0;
	int pen_y = 0;

	glyphData->num_glyphs  = 0;
	use_kerning = FT_HAS_KERNING(font->getFace());
	previous    = 0;

	FT_Set_Pixel_Sizes(face, 0,  size);

	int advanceMultiplier;
	for(int n = 0; n < num_chars; n++ ) {
		if(wstr[n] == '\t') {
			glyph_index = FT_Get_Char_Index(face, ' ');
			advanceMultiplier = 4;
		} else {
			glyph_index = FT_Get_Char_Index(face, (FT_ULong)wstr[n]);
			advanceMultiplier = 1;
		}


		if(use_kerning && previous && glyph_index) {
			FT_Vector delta;
			FT_Get_Kerning( face, previous, glyph_index, FT_KERNING_DEFAULT, &delta);
			pen_x += delta.x >> 6;
		}

		glyphData->positions[glyphData->num_glyphs].x = pen_x;
		glyphData->positions[glyphData->num_glyphs].y = pen_y;

		switch(antiAliasMode) {
			case ANTIALIAS_FULL:
			case ANTIALIAS_STRONG:
				error = FT_Load_Glyph( face, glyph_index, FT_LOAD_TARGET_LIGHT);
			break;
			default:
				error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT);
			break;
		}

		if (error) {
			continue;
		}

		error = FT_Get_Glyph( face->glyph, &glyphData->glyphs[glyphData->num_glyphs] );
		if ( error ) {
			continue;
		}

		if(n == num_chars-1 && (wstr[n] == ' ' || wstr[n] == '\t')) {
			glyphData->trailingAdvance = (slot->advance.x >> 6) * advanceMultiplier;
		}

		pen_x += (slot->advance.x >> 6) * advanceMultiplier;
		previous = glyph_index;
		glyphData->num_glyphs++;

	}
}

int Label::getBaselineAdjust() {
	return baseLineAdjust;
}

void Label::drawGlyphBitmap(FT_Bitmap *bitmap, unsigned int x, unsigned int y, Color glyphColor) {

	int lineoffset = (height-y) * (width*4);
	int xoff = (x*4);

	Number alphaMultiplier = 1.0;
	if(antiAliasMode == ANTIALIAS_STRONG) {
		alphaMultiplier = 1.2;
	}

	switch(antiAliasMode) {
			case ANTIALIAS_FULL:
			case ANTIALIAS_STRONG:
				for(int j = 0; j < ((bitmap->width * bitmap->rows)); j++) {
					if(!(j % bitmap->width) && j !=0)
						lineoffset -= ((width*4)+(bitmap->width * 4));

					int newVal = imageData[xoff+lineoffset+3] + (bitmap->buffer[j] * alphaMultiplier);
					if(newVal > 255)
						newVal = 255;

//					newVal = (int)(((Number)newVal) * glyphColor.a);

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
				unsigned char *src = bitmap->buffer;
				for(int j=0; j < bitmap->rows;j++) {
					unsigned char b;
					unsigned char *bptr =  src;
					for(int k=0; k < bitmap->width ; k++){
						if (k%8==0)
							b = (*bptr++);
						imageData[xoff+lineoffset] = (int)(255.0 * glyphColor.r);
						imageData[xoff+lineoffset+1] =  (int)(255.0 * glyphColor.g);
						imageData[xoff+lineoffset+2] =  (int)(255.0 * glyphColor.b);
						imageData[xoff+lineoffset+3] =  b&0x80 ? 255 : 0;
						xoff += 4;
						b <<= 1;
					}
					lineoffset -= ((width*4)+(bitmap->width * 4));
					src += bitmap->pitch;
				}
			break;
		}

}

void Label::renderGlyphs(GlyphData *glyphData) {

	bool useColorRanges = false;
	if(colorRanges.size() > 0) {
		useColorRanges = true;
	}

	Color glyphColor = Color(1.0, 1.0, 1.0, 1.0);

	int start_x = 0; //( ( my_target_width  - string_width  ) / 2 ) * 64;
	int start_y = 0; //( ( my_target_height - string_height ) / 2 ) * 64;

	FT_Error error;

	for (int n = 0; n < glyphData->num_glyphs; n++ ) {
		FT_Glyph   image;
		FT_Vector  pen;

		image = glyphData->glyphs[n];

		pen.x = (start_x + glyphData->positions[n].x) * 64;
		pen.y = (start_y + glyphData->positions[n].y) * 64;

		if(antiAliasMode == ANTIALIAS_FULL || antiAliasMode == ANTIALIAS_STRONG) {
			error = FT_Glyph_To_Bitmap( &image, FT_RENDER_MODE_LIGHT, &pen, 0 );
		} else {
			error = FT_Glyph_To_Bitmap( &image, FT_RENDER_MODE_MONO, &pen, 0 );
		}

		if(!error ) {
			if(useColorRanges) {
				glyphColor = getColorForIndex(n);
			}

			FT_BitmapGlyph  bit = (FT_BitmapGlyph)image;
			drawGlyphBitmap(&bit->bitmap,
					bit->left - xAdjustOffset,
					height - bit->top + baseLineOffset, glyphColor);

			FT_Done_Glyph( image );
		}
	}
}

bool Label::optionsChanged() {
	return _optionsChanged;
}

void Label::setText(const String& text) {

	if(!font || !font->isValid())
		return;

	this->text = text;

	precacheGlyphs(text, &labelData);

	FT_BBox bbox;
	computeStringBbox(&labelData, &bbox);

	unsigned int textWidth = (bbox.xMax -  bbox.xMin)+1;
	unsigned int textHeight = (bbox.yMax -  bbox.yMin)+1;

	baseLineOffset = bbox.yMin;
	xAdjustOffset = bbox.xMin;
	baseLineAdjust = bbox.yMax;

	createEmpty(textWidth,textHeight);
	renderGlyphs(&labelData);
	_optionsChanged = false;
}
