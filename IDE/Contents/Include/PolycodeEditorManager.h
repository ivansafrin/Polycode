
#pragma once

#include "Polycode.h"
#include "PolycodeEditor.h"

using namespace Polycode;

class PolycodeEditorManager { 
	public:
		PolycodeEditorManager();
		~PolycodeEditorManager();
	
		PolycodeEditor *getEditorForPath(String path);
		PolycodeEditor *createEditorForExtension(String extension);
		void registerEditorFactory(PolycodeEditorFactory *editorFactory);
	
		
	
protected:
	vector<PolycodeEditor*> openEditors;
	vector<PolycodeEditorFactory*> editorFactories;	
};