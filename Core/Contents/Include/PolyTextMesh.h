
#pragma once
#include "PolyGlobals.h"
#include "PolyEntity.h"
#include "PolyMesh.h"
#include "PolyString.h"

namespace Polycode {

	class FontGlyphSheet;

	class _PolyExport TextMesh : public Mesh {
	public:
		TextMesh(FontGlyphSheet* font, const String& text);

		void setFont(FontGlyphSheet* font);
		void setText(const String& text);

		void rebuild();

	private:
		String text;
		FontGlyphSheet* font;
	};
}
