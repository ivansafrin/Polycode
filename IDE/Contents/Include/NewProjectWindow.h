
#pragma once

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "Polycode.h"
#include "OSBasics.h"

using namespace Polycode;

class TemplateUserData  {
public:
	String templateFolder;
	int type;
};

class NewProjectWindow : public UIWindow {
	public:
	NewProjectWindow();
	~NewProjectWindow();
	
	void parseTemplatesIntoTree(UITree *tree, OSFileEntry folder);

	String getTemplateFolder();
	String getProjectName();
	String getProjectLocation();
	
	void handleEvent(Event *event);
	void ResetForm();
	
	protected:
	
		UITree *defaultTemplateTree;
	
		UITextInput *projectLocationInput;
		UITextInput *projectNameInput;
	
		UIButton *cancelButton;
		UIButton *okButton;
		UIButton *locationSelectButton;	
		UITreeContainer *templateContainer;
	
		String templateFolder;
};