
#pragma once

#include "Polycode.h"
#include "PolycodeEditor.h"

using namespace Polycode;

class PolycodeEditorManager { 
	public:
		PolycodeEditorManager();
		~PolycodeEditorManager();
	
		PolycodeEditor *getEditorForPath(string path);
		PolycodeEditor *createEditorForExtension(string extension);
		void registerEditorFactory(PolycodeEditorFactory *editorFactory);
	
		
	
protected:
	vector<PolycodeEditor*> openEditors;
	vector<PolycodeEditorFactory*> editorFactories;	
};