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
	delete editorImage;
}

bool PolycodeImageEditor::openFile(OSFileEntry filePath) {
		
	editorImage = new UIRect(filePath.fullPath);
	aspectRatio = ((Number)editorImage->getWidth()) / ((Number)editorImage->getHeight());
	editorImage->setAnchorPoint(0.0, 0.0, 0.0);
	addChild(editorImage);
	editorImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	PolycodeEditor::openFile(filePath);
	
	return true;
}

void PolycodeImageEditor::Resize(int x, int y) {

	editorImage->setPosition(x/2, y/2);

	if((y * 0.8) * aspectRatio > x * 0.8) {
		editorImage->Resize((x * 0.8), (x * 0.8) / aspectRatio);	
	} else {
		editorImage->Resize((y * 0.8) * aspectRatio, (y * 0.8));
	}
			
	PolycodeEditor::Resize(x,y);
}

