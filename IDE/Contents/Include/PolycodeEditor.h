
#pragma once

#include "Polycode.h"

using namespace Polycode;

class PolycodeEditor : public ScreenEntity { 
public:
	PolycodeEditor(bool _isReadOnly);
	virtual ~PolycodeEditor();
	
	virtual bool openFile(string filePath){ this->filePath = filePath; }
	virtual void Resize(int x, int y) = 0;
	
	string getFilePath() { return filePath; }
	
	bool isReadOnly() { return _isReadOnly; }
	
protected:
	string filePath;
	bool _isReadOnly;
};


class PolycodeEditorFactory {
public:
	PolycodeEditorFactory();
	virtual ~PolycodeEditorFactory();

	virtual PolycodeEditor *createEditor() = 0;
	
	bool canHandleExtension(string extension);
	
protected:
	vector<string> extensions;
	
};