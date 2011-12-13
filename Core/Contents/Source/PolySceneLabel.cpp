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

#include "PolySceneLabel.h"
#include "PolyCoreServices.h"
#include "PolyFontManager.h"
#include "PolyLabel.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyRenderer.h"
#include "PolyMaterialManager.h"

using namespace Polycode;

SceneLabel::SceneLabel(const String& fontName, const String& text, int size, Number scale, int amode) : ScenePrimitive(ScenePrimitive::TYPE_PLANE, 1, 1) {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode);
	this->scale = scale;
	setText(text);
	
	for(int i=0; i < mesh->getPolygonCount(); i++) {
		mesh->getPolygon(i)->flipUVY();
	}
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
}

SceneLabel::~SceneLabel() {
}

Label *SceneLabel::getLabel() {
	return label;
}

void SceneLabel::setText(const String& newText) {
	if(texture)
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
		
	label->setText(newText);	
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label);

	if(material) {
		localShaderOptions->clearTexture("diffuse");
		localShaderOptions->addTexture("diffuse", texture);	
	}

	delete mesh;
	mesh = new Mesh(Mesh::QUAD_MESH);
	mesh->createPlane(label->getWidth()*scale,label->getHeight()*scale);
	
	// TODO: resize it here
	
	bBoxRadius = label->getWidth()*scale;
}
