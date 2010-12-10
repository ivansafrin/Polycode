
#include "PolycodeEditorManager.h"


PolycodeEditorManager::PolycodeEditorManager() {
	currentEditor = NULL;
}

PolycodeEditorManager::~PolycodeEditorManager() {
	
}

PolycodeEditor *PolycodeEditorManager::createEditorForExtension(String extension) {
	for(int i=0;i < editorFactories.size(); i++) {
		PolycodeEditorFactory *factory = editorFactories[i];
		if(factory->canHandleExtension(extension)) {
			PolycodeEditor *editor = factory->createEditor();
			openEditors.push_back(editor);
			return editor;
		}
	}
	return NULL;
}

PolycodeEditor *PolycodeEditorManager::getEditorForPath(String path) {
	for(int i=0; i < openEditors.size();i++) {
		PolycodeEditor *editor = openEditors[i];
		if(editor->getFilePath() == path)
			return editor;
	}
	return NULL;
}

void PolycodeEditorManager::registerEditorFactory(PolycodeEditorFactory *editorFactory) {
	editorFactories.push_back(editorFactory);
}
