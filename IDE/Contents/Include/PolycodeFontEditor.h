

#pragma once

#include "PolycodeEditor.h"
#include "PolycodeUI.h"
#include <Polycode.h>

using namespace Polycode;

class PolycodeFontEditor : public PolycodeEditor {
public:
	PolycodeFontEditor();
	virtual ~PolycodeFontEditor();
	
	bool openFile(string filePath);
	void Resize(int x, int y);
	
protected:
	
	ScreenImage *grid;
	
	UIBox *bg;
	
	ScreenEntity *anchor;
	ScreenLabel *editorLabel;
	ScreenLabel *editorLabel2;
	ScreenLabel *editorLabel3;
	ScreenLabel *editorLabel4;
	ScreenLabel *editorLabel5;	
};

class PolycodeFontEditorFactory : public PolycodeEditorFactory {
public:
	PolycodeFontEditorFactory() : PolycodeEditorFactory() { extensions.push_back("otf"); extensions.push_back("ttf");}
	PolycodeEditor *createEditor() { return new PolycodeFontEditor(); }
};
