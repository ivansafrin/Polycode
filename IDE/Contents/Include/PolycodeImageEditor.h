
#pragma once

#include "PolycodeEditor.h"
#include <Polycode.h>

using namespace Polycode;

class PolycodeImageEditor : public PolycodeEditor {
	public:
	PolycodeImageEditor();
	virtual ~PolycodeImageEditor();
	
	bool openFile(String filePath);
	void Resize(int x, int y);
	
	protected:
		ScreenImage *grid;
	
		ScreenImage *editorImage;
};

class PolycodeImageEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeImageEditorFactory() : PolycodeEditorFactory() { extensions.push_back("png"); }
		PolycodeEditor *createEditor() { return new PolycodeImageEditor(); }
};
