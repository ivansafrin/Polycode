

#include "PolycodeEditor.h"

PolycodeEditorFactory::PolycodeEditorFactory() {
	
}

PolycodeEditorFactory::~PolycodeEditorFactory() {
	
}

bool PolycodeEditorFactory::canHandleExtension(String extension) {
	for(int i=0; i < extensions.size(); i++) {
		if(extension == extensions[i])
		   return true;
	}
	return false;
}

PolycodeEditor::PolycodeEditor(bool _isReadOnly) : ScreenEntity() {
	this->_isReadOnly = _isReadOnly;
}

PolycodeEditor::~PolycodeEditor() {
	
}


