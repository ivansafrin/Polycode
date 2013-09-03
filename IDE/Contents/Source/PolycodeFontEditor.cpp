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

#include "PolycodeFontEditor.h"

PolycodeFontEditor::PolycodeFontEditor() : PolycodeEditor(true){
	
}

PolycodeFontEditor::~PolycodeFontEditor() {
	delete grid;
	delete bg;
	delete anchor;
	delete editorLabel;
	delete editorLabel2;
	delete editorLabel3;
	delete editorLabel4;
	delete editorLabel5;				
}

bool PolycodeFontEditor::openFile(OSFileEntry filePath) {
	
	CoreServices::getInstance()->getFontManager()->registerFont(filePath.fullPath, filePath.fullPath);
	
	grid = new UIImage("Images/editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	grid->getImage()->getTexture()->clamp = false;
	grid->getImage()->getTexture()->recreateFromImageData();	
	
//	bg = new UIRect(10,10);
	bg = new UIBox("Images/fontBox.png", 29,9,9,9, 10,10);	
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	bg->setPosition(-50,-50);
	
	
	anchor = new Entity();
	addChild(anchor);
	anchor->addChild(bg);
	anchor->snapToPixels = true;
	
	editorLabel = new SceneLabel(L"ABCDEFGHIJKLM", 48, filePath.fullPath, Label::ANTIALIAS_FULL);
	anchor->addChild(editorLabel);
	editorLabel2 = new SceneLabel(L"NOPQRSTUVWXYZ", 48, filePath.fullPath, Label::ANTIALIAS_FULL);
	editorLabel2->setPosition(0, 48);
	editorLabel->setPosition((editorLabel2->getWidth()-editorLabel->getWidth())/2, 0);
	anchor->addChild(editorLabel2);
	editorLabel3 = new SceneLabel(L"abcdefghijklm", 48, filePath.fullPath, Label::ANTIALIAS_FULL);
	editorLabel3->setPosition((editorLabel2->getWidth()-editorLabel3->getWidth())/2, 96);	
	anchor->addChild(editorLabel3);
	editorLabel4 = new SceneLabel(L"nopqrstuvwxyz", 48, filePath.fullPath, Label::ANTIALIAS_FULL);
	editorLabel4->setPosition((editorLabel2->getWidth()-editorLabel4->getWidth())/2, 144);		
	anchor->addChild(editorLabel4);
	editorLabel5 = new SceneLabel(L"1234567890", 48, filePath.fullPath, Label::ANTIALIAS_FULL);
	editorLabel5->setPosition((editorLabel2->getWidth()-editorLabel5->getWidth())/2, 192);			
	anchor->addChild(editorLabel5);

	editorLabel->setColor(0,0,0,1);
	editorLabel2->setColor(0,0,0,1);
	editorLabel3->setColor(0,0,0,1);
	editorLabel4->setColor(0,0,0,1);
	editorLabel5->setColor(0,0,0,1);
	
	bg->resizeBox(editorLabel2->getWidth()+100, 192+48+100);
	
	anchor->setHeight(192+48);
	anchor->setWidth(editorLabel2->getWidth());
	
	PolycodeEditor::openFile(filePath);
	
	// remove the font entry so it doesn't show up in project font lists
	FontEntry *entry = 	CoreServices::getInstance()->getFontManager()->getFontEntryByFontPath(filePath.fullPath);
	CoreServices::getInstance()->getFontManager()->removeFontEntry(entry, false);	
	
	return true;
}

void PolycodeFontEditor::Resize(int x, int y) {
	anchor->setPosition((x-anchor->getWidth()) /2, (y-anchor->getHeight()) /2);
	grid->getImage()->setImageCoordinates(0,0,x,y);
	PolycodeEditor::Resize(x,y);	
}

