
#include "PolyTextMesh.h"
#include "PolyFontGlyphSheet.h"

using namespace Polycode;

TextMesh::TextMesh(FontGlyphSheet *font, const String &text)
:	Mesh(QUAD_MESH)
,	font(font)
,	text(text)
{
	rebuild();
}

void TextMesh::setFont(FontGlyphSheet *font) {
	this->font = font;
	rebuild();
}

void TextMesh::setText(const String &text) {
	if (text == this->text) return;
	this->text = text;
	rebuild();
}

void TextMesh::rebuild() {

    // TODO: FIX
/*
	if (text == "" || font == NULL) {
		for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++) delete *it;
		vertices.clear();
		return;
	}

	int last = font->renderStringVertices(text, vertices);
	if (last < vertices.size()) {
		for (int i = last; i < vertices.size(); i++) {
			delete vertices[i];
		}
		vertices.resize(last);
	}
 */
}


