

#include "PolycodeTextEditor.h"

PolycodeTextEditor::PolycodeTextEditor() : PolycodeEditor(true){

}

PolycodeTextEditor::~PolycodeTextEditor() {
	
}

bool PolycodeTextEditor::openFile(String filePath) {
	
	textInput = new UITextInput(true, 600, 550);
	addChild(textInput);	
	
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeTextEditor::Resize(int x, int y) {
	textInput->Resize(x,y);
}

