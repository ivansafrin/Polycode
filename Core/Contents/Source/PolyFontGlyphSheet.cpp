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

#include "PolyFont.h"
#include "PolyFontGlyphSheet.h"
#include "OSBasics.h"
#include "PolyLogger.h"
#include "PolyRenderer.h"
#include "PolyImage.h"
#include "PolyTexture.h"
#include "PolyCoreServices.h"
#include <algorithm>
#include <set>
#include <vector>

using namespace Polycode;

FontGlyphSheet::FontGlyphSheet(Font* font, int size, FontTextureGlyphMode mode)
:	font(font)
,	size(size)
,	mode(mode)
,	tabWidth(100)
{
}

FontGlyphSheet::~FontGlyphSheet() {
  Services()->getRenderer()->destroyTexture(texture);
}

struct GlyphData {
	wchar_t character;
	short off_x,off_y;
	short size_x,size_y;
	short pitch;
	Vector2 advance;
	unsigned char* data;
	int texture_u,texture_v;

	GlyphData()
	:	data(NULL)
	{
	}

	~GlyphData() {
		delete data;
	}
};

bool fontGlyphSorter(GlyphData* a, GlyphData* b) {
	return a->size_y > b->size_y;
}

inline int pot_ceil(int x) {
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x+1;
}

std::set<wchar_t> FontGlyphSheet::getCharacters() const {
	std::set<wchar_t> set;
	for (std::map<wchar_t,FontTextureGlyph>::const_iterator it = locations.begin(); it != locations.end(); it++) {
		set.insert(it->first);
	}
	return set;
}

void FontGlyphSheet::buildVisibleAscii() {
	std::set<wchar_t> chars;
	for (wchar_t i = 32; i < 127; i++) {
		chars.insert(i);
	}
	buildGlyphs(chars);
}

void FontGlyphSheet::addGlyphs(String extraCharacters) {
	extraCharacters.getWDataWithEncoding(String::ENCODING_UTF8);
	std::wstring& str = extraCharacters.w_contents;
	for (std::wstring::iterator it = str.begin(); it != str.end(); it++ ) {
		if (locations.find(*it) == locations.end()) {
			std::set<wchar_t> characterSet = getCharacters();
			characterSet.insert(str.begin(), str.end());
			buildGlyphs(characterSet);
			break;
		}
	}
}

void FontGlyphSheet::setSize(int size) {
	if (this->size == size) return;
	this->size = size;
	buildGlyphs(getCharacters());
}

void FontGlyphSheet::buildGlyphs(String charactersIn) {
	charactersIn.getWDataWithEncoding(String::ENCODING_UTF8);
	buildGlyphs(std::set<wchar_t>(charactersIn.w_contents.begin(), charactersIn.w_contents.end()));
}

void FontGlyphSheet::buildGlyphs(std::set<wchar_t> characters) {

	typedef std::set<wchar_t> character_container_t;
	typedef std::vector<GlyphData*> glyph_list_t;
	glyph_list_t glyphData;
	characters.insert('?');//Good backup character - make sure it's always present

	int shift = 0;
	Number scaleDown = 1.0f;
	FT_UInt height = size;
	if (mode == ALPHA_TEST) {
		shift = 2;
		scaleDown /= (1<<shift);
		height <<= shift;
	}
	FT_Face ftFace = font->getFace();
	FT_Set_Pixel_Sizes(ftFace, 0, height);

	//Get all the glyph data from freetype
	for (character_container_t::iterator it = characters.begin(); it != characters.end(); it++) {
		FT_Int32 load_flags = FT_LOAD_RENDER;
//		if (glyphMode == ALPHA_TEST) {
//			load_flags |= FT_LOAD_MONOCHROME;
//		}
		int error = FT_Load_Char(ftFace, *it,  load_flags);
		if (error) {
			Logger::log("Failed to load glyph for codepoint %d '%lc' error %#x\n",*it,*it,error);
		}
		else {
			glyphData.push_back(new GlyphData());
			GlyphData& gd = *glyphData.back();
			FT_GlyphSlot slot = ftFace->glyph;
			gd.character = *it;
			gd.off_x = slot->bitmap_left;
			gd.off_y = slot->bitmap_top;
			gd.size_x = slot->bitmap.width;
			gd.size_y = slot->bitmap.rows;
			gd.advance.set(Number(slot->advance.x)/(64<<shift), Number(slot->advance.y)/(64<<shift));
			gd.pitch = slot->bitmap.pitch;
			int dataLength = slot->bitmap.pitch * gd.size_y;
			if (dataLength) {
				gd.data = new unsigned char[dataLength];
				memcpy(gd.data, slot->bitmap.buffer, dataLength);
			}
		}
	}

	std::sort(glyphData.begin(), glyphData.end(), fontGlyphSorter);

	//Compute the layout for the glyphs on the texture
	const int padding = 1;
	int sheet_width = 512, sheet_height;
	{
		int sheet_y = padding, sheet_x = padding;
		int row_size_y = 0;
		for (glyph_list_t::iterator it = glyphData.begin(); it != glyphData.end(); it++) {
			GlyphData& gd = **it;
			int size_x = gd.size_x + ((1<<shift)-1) >> shift;
			int size_y = gd.size_y + ((1<<shift)-1) >> shift;
			if (sheet_x + size_x + padding >= sheet_width) {
				sheet_x = padding;
				sheet_y += row_size_y + padding;
				row_size_y = 0;
			}
			if (size_y > row_size_y) {
				row_size_y = size_y;
			}
			gd.texture_u = sheet_x;
			gd.texture_v = sheet_y;
			sheet_x += size_x + padding;
		}
		sheet_y += row_size_y;
		sheet_height = pot_ceil(sheet_y);
	}

	//Paste all the glyphs onto the texture and calculate the render data
	locations.clear();
	Image* glyphsImage = new Image(sheet_width, sheet_height);
	for (glyph_list_t::iterator it = glyphData.begin(); it != glyphData.end(); it++) {
		GlyphData& gd = **it;
		int size_x = gd.size_x + ((1<<shift)-1) >> shift;
		int size_y = gd.size_y + ((1<<shift)-1) >> shift;
		for (int glyph_y = 0, i = 0; glyph_y < size_y; glyph_y++) {
			for (int glyph_x = 0; glyph_x < size_x; glyph_x++, i++) {
				unsigned char value = gd.data[i];
				int x = gd.texture_u + glyph_x;
				int y = gd.texture_v + glyph_y;
				if (mode == ALPHA_TEST) {
					const int SEARCH_RANGE = 2;
					//Don't quite use the full range of 128 either side
					const Number ALPHA_SCALE = 112.0f / (SEARCH_RANGE << shift);
					int scan_x0 = glyph_x - SEARCH_RANGE << shift;
					int scan_x1 = glyph_x + SEARCH_RANGE << shift;
					int scan_y0 = glyph_y - SEARCH_RANGE << shift;
					int scan_y1 = glyph_y + SEARCH_RANGE << shift;
					if (scan_x0 < 0) scan_x0 = 0;
					if (scan_y0 < 0) scan_y0 = 0;
					if (scan_x1 >= gd.size_x) scan_x1 = gd.size_x - 1;
					if (scan_y1 >= gd.size_y) scan_y1 = gd.size_y - 1;

//					value = (gd.data[glyph_y * gd.pitch + (glyph_x>>3)] >> (7-(glyph_x&7))) & 1;
					value = (gd.data[(glyph_y<<shift) * gd.pitch + (glyph_x<<shift)]>>7) & 1;
					Number dist = SEARCH_RANGE << shift;
					for (int scan_y = scan_y0; scan_y <= scan_y1; scan_y++) {
						int dy = (glyph_y<<shift) - scan_y;
						int dy2 = dy*dy;
						for (int scan_x = scan_x0; scan_x <= scan_x1; scan_x++) {
							int dx = (glyph_x<<shift) - scan_x;
//							int v = (gd.data[scan_y * gd.pitch + (scan_x>>3)] >> (7-(scan_x&7))) & 1;
							int v = (gd.data[scan_y * gd.pitch + scan_x] >> 7) & 1;
							if (v != value) {
								int dx2 = dx*dx;
								Number d(sqrt((Number)(dx2+dy2)));
								if (d < dist) {
									dist = d;
								}
							}
						}
					}
					value = (int)round(128 + ((value+value)-1) * (dist * ALPHA_SCALE));
//					value *= 255;
				}
				glyphsImage->setPixel(x, y, Color(255, 255, 255, value));
			}
		}
		Number x0 = gd.off_x * scaleDown;
		Number y0 = gd.off_y * scaleDown;
		Number x1 = x0 + gd.size_x * scaleDown;
		Number y1 = y0 - gd.size_y * scaleDown;
		Number u0 = Number(gd.texture_u) / sheet_width;
		Number v0 = 1.0f - Number(gd.texture_v) / sheet_height;
		Number u1 = Number(gd.texture_u + size_x) / sheet_width;
		Number v1 = 1.0f - Number(gd.texture_v + size_y) / sheet_height;
		FontTextureGlyph& glyph = locations[gd.character];
		glyph.offset[0].set(x0, y0);
		glyph.offset[1].set(x0, y1);
		glyph.offset[2].set(x1, y1);
		glyph.offset[3].set(x1, y0);
		glyph.texCoord[0].set(u0, v0);
		glyph.texCoord[1].set(u0, v1);
		glyph.texCoord[2].set(u1, v1);
		glyph.texCoord[3].set(u1, v0);
		glyph.advance = gd.advance;
	}

	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
    Services()->getRenderer()->destroyTexture(texture);

	texture = materialManager->createTextureFromImage(glyphsImage, true, materialManager->mipmapsDefault);
	delete glyphsImage;
	for (glyph_list_t::iterator it = glyphData.begin(); it != glyphData.end(); it++) delete *it;
}

/*
int FontGlyphSheet::renderStringVertices(String textIn, std::vector<Vertex*>& vertices, int index) {
	textIn.getWDataWithEncoding(String::ENCODING_UTF8);
	std::wstring& text = textIn.w_contents;

	Vector2 cursor;
	wchar_t prevChar = -1;
	for (std::wstring::const_iterator it = text.begin(); it != text.end(); it++) {

		switch(*it) {
		case '\t':
			cursor.x = (int(cursor.x / tabWidth) + 1) * tabWidth;
			break;
		case '\n':
			cursor.x = 0;
			cursor.y += size;
			break;
		default:
			std::map<wchar_t,FontTextureGlyph>::iterator glyphLoc = locations.find(*it);
			if (glyphLoc == locations.end()) {
				Logger::log("Missing glyph for codepoint %d '%lc'\n",*it,*it);
				glyphLoc = locations.find('?');
			}

	//		if (prevChar != -1) {
	//			FT_Vector delta;
	//			FT_Get_Kerning( ftFace, FT_Get_Char_Index(ftFace, prevChar), FT_Get_Char_Index(ftFace, *it), FT_KERNING_DEFAULT, &delta);
	//			cursor.x += delta.x / Number(64);
	//		}

			for (int i = 0; i < 4; i++, index++) {
				Vertex* vertex;
				if (index == vertices.size()) {
					vertices.push_back(vertex = new Vertex());
				}
				else {
					vertex = vertices[index];
				}
				vertex->set(cursor.x + glyphLoc->second.offset[i].x, cursor.y + glyphLoc->second.offset[i].y, 0);
				vertex->texCoord = glyphLoc->second.texCoord[i];
			}
			cursor += glyphLoc->second.advance;
			break;
		}

		prevChar = *it;
	}
	return index;
}

*/

