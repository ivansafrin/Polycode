
#pragma once

#include "Polycode.h"

using namespace Polycode;

class PolycodeEditor : public ScreenEntity { 
public:
	PolycodeEditor(bool _isReadOnly);
	virtual ~PolycodeEditor();
	
	virtual bool openFile(String filePath){ this->filePath = filePath; }
	virtual void Resize(int x, int y) = 0;
	
	virtual void saveFile(){};
	
	String getFilePath() { return filePath; }
	
	bool isReadOnly() { return _isReadOnly; }
	
protected:
	String filePath;
	bool _isReadOnly;
};


class PolycodeEditorFactory {
public:
	PolycodeEditorFactory();
	virtual ~PolycodeEditorFactory();

	virtual PolycodeEditor *createEditor() = 0;
	
	bool canHandleExtension(String extension);
	
protected:
	std::vector<std::string> extensions;
	
};