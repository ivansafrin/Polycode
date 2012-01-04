
#pragma once 

#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProject.h"
#include "OSBasics.h"

using namespace Polycode;


class BrowserUserData  {
public:
	BrowserUserData() { parentProject = NULL; }
	OSFileEntry fileEntry;
	PolycodeProject *parentProject;
	int type;
};


class PolycodeProjectBrowserEvent : public Event {
	public:
		PolycodeProjectBrowserEvent() : Event() {eventType = "PolycodeProjectBrowserEvent";}
		~PolycodeProjectBrowserEvent() {}
		static const int SHOW_MENU = 0;
		
		
};

class PolycodeProjectBrowser : public ScreenEntity {
public:
	PolycodeProjectBrowser();
	~PolycodeProjectBrowser();
	
	void Resize(int newWidth, int newHeight);
	void addProject(PolycodeProject *project);
	void removeProject(PolycodeProject *project);
	
	void handleEvent(Event *event);
	
	void parseFolderIntoNode(UITree *node, String spath, PolycodeProject *parentProject);
	
	
	
	BrowserUserData *getSelectedData() { return selectedData; }
	
protected:
	
		BrowserUserData *selectedData;
		UITreeContainer *treeContainer;
};	