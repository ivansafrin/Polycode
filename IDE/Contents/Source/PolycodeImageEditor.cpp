
#include "PolycodeImageEditor.h"

PolycodeImageEditor::PolycodeImageEditor() : PolycodeEditor(true){
	
}

PolycodeImageEditor::~PolycodeImageEditor() {
	
}

bool PolycodeImageEditor::openFile(String filePath) {
	
	grid = new ScreenImage("editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();	
	
	
	editorImage = new ScreenImage(filePath);
	addChild(editorImage);
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeImageEditor::Resize(int x, int y) {
	editorImage->setPosition((x-editorImage->getWidth()) /2, (y-editorImage->getHeight()) /2);
	grid->setImageCoordinates(0,0,x,y);	
}

