

#pragma once

#include "PolycodeEditor.h"
#include <PolycodeUI.h>
#include <Polycode.h>

using namespace Polycode;

class PolycodeTextEditor : public PolycodeEditor {
public:
	PolycodeTextEditor();
	virtual ~PolycodeTextEditor();
	
	bool openFile(string filePath);
	void Resize(int x, int y);
	
protected:

	UITextInput *textInput;
};

class PolycodeTextEditorFactory : public PolycodeEditorFactory {
public:
	PolycodeTextEditorFactory() : PolycodeEditorFactory() { extensions.push_back("lua"); extensions.push_back("txt"); extensions.push_back("xml");}
	PolycodeEditor *createEditor() { return new PolycodeTextEditor(); }
};
