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
	
	grid = new UIImage("Images/editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	grid->getImage()->getTexture()->clamp = false;
	grid->getImage()->getTexture()->recreateFromImageData();	
		
	
	leftShape = new UIRect(10,10);
	leftShape->setColor(0.0, 0.0, 0.0, 0.3);
	leftShape->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(leftShape);

	rightShape = new UIRect(10,10);
	rightShape->setColor(0.0, 0.0, 0.0, 0.3);
	rightShape->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(rightShape);

	topShape = new UIRect(10,10);
	topShape->setColor(0.0, 0.0, 0.0, 0.3);
	topShape->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(topShape);

	bottomShape = new UIRect(10,10);
	bottomShape->setColor(0.0, 0.0, 0.0, 0.3);
	bottomShape->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(bottomShape);
		
		
	editorImage = new UIRect(10,10);
	
	Texture *newTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(filePath.fullPath);
	newTexture->reloadOnFileModify = true;
	editorImage->setTexture(newTexture);
	
//	editorImage->strokeEnabled = true;
//	editorImage->setStrokeColor(1.0, 1.0, 1.0, 0.2);
	
	aspectRatio = ((Number)newTexture->getWidth()) / ((Number)newTexture->getHeight());
	
	addChild(editorImage);
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeImageEditor::Resize(int x, int y) {

	editorImage->setPosition(x/2, y/2);
	grid->getImage()->setImageCoordinates(0,0,x,y);	
	
	if((y * 0.8) * aspectRatio > x * 0.8) {
		editorImage->Resize((x * 0.8), (x * 0.8) / aspectRatio);	
	} else {
		editorImage->Resize((y * 0.8) * aspectRatio, (y * 0.8));
	}
	
	leftShape->Resize((x - editorImage->getWidth())/2.0, y);	
	rightShape->Resize((x - editorImage->getWidth())/2.0, y);	
	rightShape->setPosition(leftShape->getWidth() + editorImage->getWidth(), 0);
		
	topShape->Resize(editorImage->getWidth(), (y - editorImage->getHeight())/2.0);
	topShape->setPosition(leftShape->getWidth(),0);

	bottomShape->Resize(editorImage->getWidth(), (y - editorImage->getHeight())/2.0);
	bottomShape->setPosition(leftShape->getWidth(),y-bottomShape->getHeight());

		
	PolycodeEditor::Resize(x,y);
}

