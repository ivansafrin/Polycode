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

SceneLabel::SceneLabel(const String& fontName, const String& text, int size, Number scale, int amode) : SceneEntity() {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode);
	this->scale = scale;
	setText(text);
	mesh = new Mesh(Mesh::QUAD_MESH);
	mesh->createPlane(label->getWidth()*scale,label->getHeight()*scale);
	
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

bool SceneLabel::testMouseCollision(Number x, Number y) {
	
	Matrix4 fullMatrix = getConcatenatedMatrix();
	if(billboardMode) {
		fullMatrix.m[0][0] = 1.0f * getScale().x;
		fullMatrix.m[0][1] = 0;
		fullMatrix.m[0][2] = 0;
		
		fullMatrix.m[1][0] = 0;
		fullMatrix.m[1][1] = 1.0f * getScale().y;
		fullMatrix.m[1][2] = 0;
		
		fullMatrix.m[2][0] = 0;
		fullMatrix.m[2][1] = 0;
		fullMatrix.m[2][2] = 1.0f * getScale().z;
	}
	
	Matrix4 camInverse = CoreServices::getInstance()->getRenderer()->getCameraMatrix().inverse();	
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;	
	
	fullMatrix = fullMatrix * cmv;
	
	if(billboardMode && billboardRoll) {
		Quaternion q;
		q.createFromAxisAngle(0.0f, 0.0f, 1.0f, getRoll());
		Matrix4 tm = q.createMatrix();
		fullMatrix = tm * fullMatrix ;
	}		
	
	return false; //CoreServices::getInstance()->getRenderer()->test2DCoordinate(x, y, imagePolygon, fullMatrix, billboardRoll);
}

void SceneLabel::setText(const String& newText) {
	if(texture)
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
		
	label->setText(newText);	
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label);

	// TODO: resize it here
	
	bBoxRadius = label->getWidth()*scale;
}

void SceneLabel::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	renderer->setTexture(texture);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::NORMAL_DATA_ARRAY);		
	renderer->drawArrays(mesh->getMeshType());	
}
