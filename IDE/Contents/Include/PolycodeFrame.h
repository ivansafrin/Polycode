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

class EditPoint : public ScreenEntity {
	public:
		EditPoint(BezierPoint *point, unsigned int type);
		~EditPoint();

		void handleEvent(Event *event);

		void updatePosition();
		void updateCurvePoint();

		void setMode(unsigned int mode);

		void limitPoint(ScreenImage *point);

		ScreenImage *pointHandle;

		ScreenImage *controlHandle1;
		ScreenImage *controlHandle2;

		ScreenLine *connectorLine1;
		ScreenLine *connectorLine2;

		static const int TYPE_START_POINT = 0;
		static const int TYPE_POINT = 1;
		static const int TYPE_END_POINT = 2;

		ScreenImage *draggingPoint;
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
		ScreenMesh *visMesh;
		Polycode::Polygon *poly;

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

		ScreenImage	*selectorImage;

		static const int MODE_SELECT = 0;
		static const int MODE_ADD = 1;
		static const int MODE_REMOVE = 2;

		UITreeContainer *treeContainer;

		unsigned int mode;
		ScreenImage *bg;

		EditCurve *selectedCurve;
		std::vector<EditCurve*> curves;
};

class EditorHolder : public UIElement {
	public:
		EditorHolder();
		~EditorHolder();

		void Resize(Number width, Number height);

		PolycodeEditor *currentEditor;

};

class PolycodeFrame : public ScreenEntity {
public:

	PolycodeFrame();
	~PolycodeFrame();

	void Resize(int x, int y);

	void Update();

	void showModal(UIWindow *modalChild);
	void hideModal();

	void showFileBrowser(String baseDir, bool foldersOnly, std::vector<String> extensions, bool allowMultiple);

	void handleEvent(Event *event);

	void addEditor(PolycodeEditor *editor);
	void removeEditor(PolycodeEditor *editor);

	void showEditor(PolycodeEditor *editor);

	void showAssetBrowser(std::vector<String> extensions);

	void toggleConsole();
	void showConsole();
	void hideConsole();

	void showCurveEditor();

	PolycodeProjectBrowser *getProjectBrowser();

	NewProjectWindow *newProjectWindow;
	ExampleBrowserWindow *exampleBrowserWindow;
	NewFileWindow *newFileWindow;
	ExportProjectWindow *exportProjectWindow;
	SettingsWindow *settingsWindow;

	AssetBrowser *assetBrowser;

	TextInputPopup *textInputPopup;
	YesNoPopup *yesNoPopup;
	YesNoCancelPopup *yesNoCancelPopup;

	ScreenEntity *welcomeEntity;
	PolycodeProjectBrowser *projectBrowser;
	PolycodeEditorManager *editorManager;

	UIImageButton *playButton;
	UIImageButton *stopButton;

	UIHSizer *mainSizer;

	PolycodeConsole *console;

	PolycodeProjectManager *projectManager;

	CurveEditor *curveEditor;

	UIElement *modalRoot;
	UIElement *fileBrowserRoot;
	UIFileDialog *fileDialog;

	UIWindow *aboutWindow;
	UIButton *aboutOKButton;

	UIImageButton *closeFileButton;

	void updateFileSelector();
	void showNextEditor();
	void showPreviousEditor();

private:

	int frameSizeX;
	int frameSizeY;

	bool willHideModal;

	bool showingConsole;
	Number consoleSize;

	ScreenShape *fileDialogBlocker;

	ScreenShape *topBarBg;
	ScreenImage *logo;
	ScreenImage *resizer;

	OSFileEntry draggedFile;
	ScreenEntity *dragEntity;
	ScreenLabel *dragLabel;
	bool isDragging;

	ScreenLabel *currentProjectTitle;
	UIComboBox *currentFileSelector;

	ScreenImage *welcomeImage;


	EditorHolder *editorHolder;


	vector<PolycodeEditor*> editors;

	ScreenShape *modalBlocker;
	UIWindow *modalChild;

	UIVSizer *consoleSizer;

	UIButton *newProjectButton;
	UIButton *examplesButton;

	bool displayFilePathInSelector;

};
