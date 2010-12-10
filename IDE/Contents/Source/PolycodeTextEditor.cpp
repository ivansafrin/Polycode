

#include "PolycodeTextEditor.h"

PolycodeTextEditor::PolycodeTextEditor() : PolycodeEditor(true){

}

PolycodeTextEditor::~PolycodeTextEditor() {
	
}

bool PolycodeTextEditor::openFile(String filePath) {
	
	textInput = new UITextInput(true, 100, 100);
	addChild(textInput);	
	
	Data *data = new Data();
	data->loadFromFile(filePath);	
	textInput->insertText(data->getAsString(String::ENCODING_UTF8));
	delete data;
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeTextEditor::saveFile() {
	Data *data = new Data();
	data->setFromString(textInput->getText(), String::ENCODING_UTF8);
	data->saveToFile(filePath);
	delete data;
}

void PolycodeTextEditor::Resize(int x, int y) {
	textInput->Resize(x,y);
}

