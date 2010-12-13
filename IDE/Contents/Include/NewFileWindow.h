

#pragma once

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "Polycode.h"

using namespace Polycode;

class FileTemplateUserData  {
public:
	String templateFolder;
	int type;
};

class NewFileWindow : public UIWindow {
	public:
		NewFileWindow();
		~NewFileWindow();
	
		void resetForm();
		void parseTemplatesIntoTree(UITree *tree, OSFileEntry folder);

	
	protected:
	
		UITreeContainer *templateContainer;	
		UITree *defaultTemplateTree;
};