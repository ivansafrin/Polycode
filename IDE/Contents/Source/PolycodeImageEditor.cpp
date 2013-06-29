/*
 Copyright (C) 2012 by Ivan Safrin
 
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
 
#include "PolycodeImageEditor.h"

PolycodeImageEditor::PolycodeImageEditor() : PolycodeEditor(true){

}

PolycodeImageEditor::~PolycodeImageEditor() {
	delete grid;
	delete editorImage;
	delete leftShape;
	delete rightShape;
	delete topShape;
	delete bottomShape;
}

bool PolycodeImageEditor::openFile(OSFileEntry filePath) {

	grid = new ScreenImage("Images/editorGrid.png");

	addChild(grid);
	grid->snapToPixels = true;

	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();


	leftShape = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	leftShape->setColor(0.0, 0.0, 0.0, 0.3);
	leftShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(leftShape);

	rightShape = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	rightShape->setColor(0.0, 0.0, 0.0, 0.3);
	rightShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(rightShape);

	topShape = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	topShape->setColor(0.0, 0.0, 0.0, 0.3);
	topShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(topShape);

	bottomShape = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	bottomShape->setColor(0.0, 0.0, 0.0, 0.3);
	bottomShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(bottomShape);


	editorImage = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);

	Texture *newTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(filePath.fullPath);
	newTexture->reloadOnFileModify = true;
	editorImage->setTexture(newTexture);

	editorImage->strokeEnabled = true;
	editorImage->setStrokeColor(1.0, 1.0, 1.0, 0.2);

	aspectRatio = ((Number)newTexture->getWidth()) / ((Number)newTexture->getHeight());

	addChild(editorImage);

	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeImageEditor::Resize(int x, int y) {
	editorImage->setPosition(x/2, y/2);
	grid->setImageCoordinates(0,0,x,y);

	if((y * 0.8) * aspectRatio > x * 0.8) {
		editorImage->setShapeSize((x * 0.8), (x * 0.8) / aspectRatio);
	} else {
		editorImage->setShapeSize((y * 0.8) * aspectRatio, (y * 0.8));
	}

	leftShape->setShapeSize((x - editorImage->getWidth())/2.0, y);
	rightShape->setShapeSize((x - editorImage->getWidth())/2.0, y);
	rightShape->setPosition(leftShape->getWidth() + editorImage->getWidth(), 0);

	topShape->setShapeSize(editorImage->getWidth(), (y - editorImage->getHeight())/2.0);
	topShape->setPosition(leftShape->getWidth(),0);

	bottomShape->setShapeSize(editorImage->getWidth(), (y - editorImage->getHeight())/2.0);
	bottomShape->setPosition(leftShape->getWidth(),y-bottomShape->getHeight());


	PolycodeEditor::Resize(x,y);
}

