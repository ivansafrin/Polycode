/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "PolycodeUI.h"
#include "Polycode.h"
#include "PolycodeProjectBrowser.h"
#include "PolycodeEditor.h"
#include "PolycodeConsole.h"
#include "NewProjectWindow.h"
#include "TextureBrowser.h"
#include "ExportProjectWindow.h"
#include "ExampleBrowserWindow.h"
#include "NewFileWindow.h"
#include "ToolWindows.h"
#include "PolycodeProjectManager.h"
#include "PolycodeEditorManager.h"
#include "SettingsWindow.h"

using namespace Polycode;

#define CURVE_SIZE 160.0

class EditPoint : public Entity {
	public:
		EditPoint(BezierPoint *point, unsigned int type);
		~EditPoint();
		
		void handleEvent(Event *event);
		
		void updatePosition();
		void updateCurvePoint();
		
		void setMode(unsigned int mode);

		void limitPoint(UIRect *point);
								
		UIRect *pointHandle;
		UIRect *controlHandle1;
		UIRect *controlHandle2;
		
		SceneLine *connectorLine1;
		SceneLine *connectorLine2;
				
		static const int TYPE_START_POINT = 0;		
		static const int TYPE_POINT = 1;
		static const int TYPE_END_POINT = 2;				
		
		UIImage *draggingPoint;
		bool dragging;
		Vector2 basePosition;
		Vector2 basePointPosition;
		
		Vector2 baseControl1;
		Vector2 baseControl2;	
		
		unsigned int mode;
				
		unsigned int type;				
		BezierPoint *point;
};

class EditCurve : public UIElement {
	public:
		EditCurve(BezierCurve *targetCurve, Color curveColor);
		~EditCurve();
		
		void updateCurve();
		void updatePoints();
		
		void setMode(unsigned int mode);
		
		void Activate();
		void Deactivate();
		
		void Update();
				
		void handleEvent(Event *event);
		
		BezierCurve *targetCurve;
		SceneMesh *visMesh;
		
		EditPoint *pointToRemove;
		UIElement *pointsBase;
		vector<EditPoint*> points;

		unsigned int mode;
};

class CurveEditor : public UIWindow {
	public:
		CurveEditor();
		~CurveEditor();
		
		void handleEvent(Event *event);		
		void setMode(unsigned int mode);
		
		void addCurve(String name, BezierCurve *curve, Color curveColor);

		void onClose();

		void clearCurves();
		
		UIImageButton *selectButton;
		UIImageButton *addButton;
		UIImageButton *removeButton;
				
		UIImage	*selectorImage;
		
		static const int MODE_SELECT = 0;		
		static const int MODE_ADD = 1;
		static const int MODE_REMOVE = 2;
		
		UITreeContainer *treeContainer;
		
		unsigned int mode;
		UIRect *bg;
		
		EditCurve *selectedCurve;
		std::vector<EditCurve*> curves;
};

class EditorHolder : public UIElement {
	public:
		EditorHolder(PolycodeProject *project, PolycodeEditorManager *editorManager, EditorHolder *parentHolder);
		~EditorHolder();
		
		ObjectEntry *getEditorHolderConfig();
		void applyConfig(ObjectEntry *entry);
		
        void activateEditor(bool val);
    
		void handleEvent(Event *event);
		void Resize(Number width, Number height);		
		
		void makeVSplit();
		void makeHSplit();
				
		void _mergeSides(EditorHolder *mainHolder);
		void mergeSides(EditorHolder *mainHolder);
		
		void Update();
		void setActive(bool val);
				
		void updateFileSelector();
		
		void setEditor(PolycodeEditor *newEditor);		
		PolycodeEditor *getEditor();
		
						
	protected:
	
		PolycodeProject *project;
	
		EditorHolder *parentHolder;
		PolycodeEditorManager *editorManager;
		
		PolycodeEditor *currentEditor;
		EditorHolder *editorToMerge;
		
		UIElement *holderBar;
		
		UIRect *headerBg;
		UIImageButton *vSplitButton;
		UIImageButton *hSplitButton;
		UIImageButton *mergeSplitButton;
		
		UIVSizer *vSizer;
		UIHSizer *hSizer;	
		
		EditorHolder *firstChildHolder;
		EditorHolder *secondChildHolder;
		
		UIImageButton *closeFileButton;		
		UIComboBox *currentFileSelector;
		
		bool displayFilePathInSelector;
		bool initialUpdate;
		bool isActive;
};

class PolycodeProjectTab : public UIElement {
	public:
		PolycodeProjectTab(String caption, PolycodeProject *project, PolycodeEditorManager *editorManager);
		~PolycodeProjectTab();
		
		void handleEvent(Event *event);
		
		EditorHolder *getEditorHolder();
		void Resize(Number width, Number height);				
		void showEditor(PolycodeEditor *editor);
		
		ObjectEntry *getTabConfig();
		void applyTabConfig(ObjectEntry *tabEntry);
		
		void setActive(bool val);
		bool isActive();
		
		String getTabName();
		void setTabName(String newName);		
		
		PolycodeProjectBrowser *getProjectBrowser();
			
	protected:
	
		bool active;
		String tabName;
		UIHSizer *mainSizer;	
		PolycodeProjectBrowser *projectBrowser;
		EditorHolder *editorHolder;
		PolycodeEditorManager *editorManager;
};

class PolycodeTabButton : public UIElement {
	public:
		PolycodeTabButton(PolycodeProjectTab *tab);
		~PolycodeTabButton();

		void setActive(bool val);
		void handleEvent(Event *event);
		void updateLabel();

		PolycodeProjectTab *getTab();		
	protected:
		PolycodeProjectTab *tab;
		UIImage *bgRect;
		UILabel *tabLabel;
		UIMenu *menu;
		
		TextInputPopup *renamePopup;
		
		UIImageButton *closeButton;
	
};

class PolycodeProjectFrame : public UIElement {
	public:
		PolycodeProjectFrame(PolycodeProject *project, PolycodeEditorManager *editorManager);
		~PolycodeProjectFrame();
		
		PolycodeProject *getProject();
		
		PolycodeProjectTab *addNewTab(String caption = "New Tab");
		
		ObjectEntry *getFrameConfig();
		
		void showTab(PolycodeProjectTab *tab);
		void closeTab(PolycodeProjectTab *tab);
		void showNextTab();
		void showPreviousTab();
		
		void Update();
								
		PolycodeProjectTab *getActiveTab();
		void handleEvent(Event *event);
		
		void restructTabs();
		
		void Resize(Number width, Number height);
		
		EditorHolder *lastActiveEditorHolder;
		
		PolycodeProjectTab *getTabAtIndex(unsigned int index);
		unsigned int getNumTabs();
		
	protected:
	
		PolycodeProject *project;
		
		UIElement *tabButtonAnchor;		
		UIImageButton *newTabButton;
	
		PolycodeEditorManager *editorManager;
		PolycodeProjectTab *activeTab;
		std::vector<PolycodeProjectTab*> tabs;		
		std::vector<PolycodeTabButton*> tabButtons;
		
		PolycodeProjectTab *tabToClose;
};

class PolycodeFrame : public UIElement {
public:
	
	PolycodeFrame(PolycodeEditorManager *editorManager);
	~PolycodeFrame();
	
	void Resize(int x, int y);

	void Update();
	
	void showModal(UIWindow *modalChild);
	void hideModal();
	
	void showFileBrowser(String baseDir, bool foldersOnly, std::vector<String> extensions, bool allowMultiple);

	void handleEvent(Event *event);	
	void showAssetBrowser(std::vector<String> extensions);

	void showAssetBrowserForPools(std::vector<ResourcePool*> pools, int resourceType);
    
	PolycodeProjectBrowser *getCurrentProjectBrowser();
	PolycodeProjectFrame *getActiveProjectFrame();	
	PolycodeProjectFrame *getProjectFrame(PolycodeProject *project);
	
	void removeProjectFrame(PolycodeProject *project);
	
	TextInputPopup *showTextInput(String caption, String action, String value);
	
	ObjectEntry *getFrameConfigForProject(PolycodeProject *project);
	
	void toggleConsole();
	void showConsole();
	void hideConsole();
	
	PolycodeProjectFrame *createProjectFrame(PolycodeProject *project);
	void switchToProjectFrame(PolycodeProjectFrame *projectFrame);
	
	UIVSizer *getConsoleSizer();
	
	void showCurveEditor();
	
	NewProjectWindow *newProjectWindow;	
	ExampleBrowserWindow *exampleBrowserWindow;
	NewFileWindow *newFileWindow;
	ExportProjectWindow *exportProjectWindow;
	SettingsWindow *settingsWindow;	
	AssetBrowser *assetBrowser;
	
	TextInputPopup *textInputPopup;
	YesNoPopup *yesNoPopup;
    MessagePopup *messagePopup;
	YesNoCancelPopup *yesNoCancelPopup;
	
	Entity *welcomeEntity;	
	PolycodeEditorManager *editorManager;
		
	UIImageButton *playButton;
	UIImageButton *stopButton;
			
	PolycodeProjectManager *projectManager;
		
	PolycodeConsole *console;	
	CurveEditor *curveEditor;
	
	UIElement *modalRoot;
	UIElement *fileBrowserRoot;
	UIFileDialog *fileDialog;
	
	UIWindow *aboutWindow;
	UIButton *aboutOKButton;
	
	AssetImporterWindow *assetImporterWindow;
	
	void updateFileSelector();
	
	bool isShowingConsole();
	Number getConsoleSize();
	
private:
	
	Number consoleSize;
				
	UIVSizer *consoleSizer;
	
	bool willHideModal;	
	bool showingConsole;

	UIRect *fileDialogBlocker;

	UIRect *topBarBg;
	UIImage *logo;	
	UIImage *resizer;	

	OSFileEntry draggedFile;
	Entity *dragEntity;
	UILabel *dragLabel;
	bool isDragging;
	
	UIComboBox *currentProjectSelector;	
	UIImage *welcomeImage;	
	
	UIRect *modalBlocker;
	UIWindow *modalChild;		
	
	
	UIButton *newProjectButton;
	UIButton *examplesButton;
	
	bool displayFilePathInSelector;
	
	PolycodeProjectFrame* activeProjectFrame;
	std::vector<PolycodeProjectFrame*> projectFrames;

};
