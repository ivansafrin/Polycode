
#pragma once
#include "PolyGlobals.h"
#include "ft2build.h"
#include "PolyString.h"
#include "PolyVector2.h"
#include <vector>
#include <map>
#include <set>

#include FT_FREETYPE_H

namespace Polycode {
	
	class String;
	class Texture;
	class Image;
	class Font;

	struct FontTextureGlyph {
		Vector2 offset[4];
		Vector2 texCoord[4];
		Vector2 advance;
	};

	/** Wraps a sheet of rendered font glyphs on a Texture.
	 *  Use in combination with TextMesh to render text from minimal texture creation. */
	class _PolyExport FontGlyphSheet : public PolyBase {
		public:

			enum FontTextureGlyphMode {
				/** Regular anti-aliased font rendering. Colour is pure-white for clean custom tinting with an alpha channel. */
				ANTIALIAS,
				/** Using distance-from-edge calculation as described in the Valve paper.
				 *
				 *  "Improved Alpha-Tested Magniﬁcation for Vector Textures and Special Effects"
				 *  http://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf
				 *
				 * To make the most of this:
				 *   set renderer->alphaTestValue = 0.5
				 *   set sceneMesh->alphaTest = true
				 *   set sceneMesh->blendingMode = Renderer::BLEND_MODE_NONE;
				 *
				 * Or use a custom shader - alpha values of 0.5 indicate the boundary.
				 * */
				ALPHA_TEST
			};

			FontGlyphSheet(Font* font, int size = 32, FontTextureGlyphMode mode = ANTIALIAS);
			virtual ~FontGlyphSheet();
			
			void setMode(FontTextureGlyphMode mode) { this->mode = mode; }
			/** Set height of font to be rendered in pixels. */
			void setSize(int size);

			/** Scans extraCharacters for anything that isn't currently in the rendered sheet and rebuilds the sheet if necessary. */
			void addGlyphs(String extraCharacters);

			/** Convenience method to build a sheet with all of the visible ASCII characters. */
			void buildVisibleAscii();

			/** Convenience method to build a sheet of glyphs with one of each of what is in characters. */
			void buildGlyphs(String characters);

			/** Creates the sheet given a set of characters. */
			void buildGlyphs(std::set<wchar_t> characters);

			/** Returns the currently rendered characters as a set. */
			std::set<wchar_t> getCharacters() const;

			/** Used by TextMesh to generate the vertices for the given text into the vertex array.
				@return the next index after that which was used */
			//int renderStringVertices(String text, std::vector<Vertex*>& vertices, int index = 0);

			Texture* getTexture() { return texture; }

			int tabWidth;
			
		protected:
			Font* font;
			FontTextureGlyphMode mode;
			Texture* texture;
			std::map<wchar_t,FontTextureGlyph> locations;
			int size;
	};
}
