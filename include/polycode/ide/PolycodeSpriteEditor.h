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
 
#pragma once

#include "PolycodeEditor.h"
#include <Polycode.h>
#include "PolycodeProps.h"
#include "TransformGizmo.h"

using namespace Polycode;

class PolycodeSpriteEditorActionData : public PolycodeEditorActionData {
public:
    PolycodeSpriteEditorActionData() {
        reverse = true;
        sprite = NULL;
        state = NULL;
    }
    
    ~PolycodeSpriteEditorActionData() {
        
    }

    Sprite *sprite;
    SpriteState *state;
    String name;
    
    Number stateFPS;
    Number stateScale;
    Vector2 stateBBox;
    Vector2 stateOffset;
    
    std::vector<unsigned int> frameIDs;
    std::vector<SpriteFrame> spriteFrames;
    bool reverse;
};

class SpritePreview : public UIElement {
    public:
        SpritePreview(SpriteSet *spriteSet);
        ~SpritePreview();
    
        void Update();
    
        void handleEvent(Event *event);
    
        SceneSprite *getSceneSprite();
        void Resize(Number width, Number height);
    
    protected:
        UIRect *headerBg;    
        UIImage *previewBg;
        SceneSprite *sprite;
    
        UIIconSelector *bgSelector;
    
        SceneMesh *boundingBoxPreview;
    
};

class SpriteSheetEditor : public UIElement {
    public:
        SpriteSheetEditor(SpriteSet *sprite);
        ~SpriteSheetEditor();
    
        void handleEvent(Event *event);
    
        void Update();
    
        void Render();
    
        void deleteSelectedFrames();
    
        void selectAll();
        void clearSelected();
        bool hasSelectedID(unsigned int frameID);
        std::vector<unsigned int> getSelectedFrameIDs();
    
        void Resize(Number width, Number height);
    
        PolycodeEditor *editor;
    
        SpriteSet *sprite;
        UIRect *previewImage;
    
    protected:
    
        UIRect *headerBg;
    
        UIIconSelector *bgSelector;
    
        bool creatingFrame;
        bool willCreateFrame;
    
        Number zoomScale;
        Vector2 panOffset;
    
        TransformGrips *transformGrips;
    
        SpriteFrame frameToAdd;

        Vector2 clickBaseCoord;
    
        Vector2 panMouseBase;
        bool panning;
    
    
        std::vector<Vector2> defaultAnchors;
    
        UIImage *previewBg;
    
        SceneMesh *frameVisualizerMesh;
        SceneMesh *frameVisualizerMeshSelected;
    
        Entity *bottomMenu;
        UIRect *bottomMenuRect;
        UIButton *changeImageButton;
        UIButton *generateFramesButton;
        UIButton *clearFramesButton;
    
        UIButton *generateOptionsButton;
    
        UIElement *uniformOptions;
        UIElement *detectOptions;
    
        UIComboBox *defaultAnchorCombo;
    
        UIWindow *optionsWindow;
    
        UITextInput *uniformGridWidthInput;
        UITextInput *uniformGridHeightInput;
    
        UITextInput *minimumDistanceInput;
    
        std::vector<unsigned int> selectedIDs;
    
        UIComboBox *generateTypeDropdown;
};

class SpriteBrowser : public UIElement {
    public:
        SpriteBrowser(SpriteSet *spriteSet);
        ~SpriteBrowser();
    
        void Resize(Number width, Number height);
		void handleEvent(Event *event);
        void refreshSprites();
    
        Sprite *getSelectedSpriteEntry();
    
        PolycodeEditor *editor;
    protected:
    
    
        UIRect *headerBg;
        SpriteSet *spriteSet;
    
        Sprite *selectedEntry;
    
        UITreeContainer *spriteTreeView;
        UIImageButton *newSpriteButton;
        UIImageButton *removeSpriteButton;
        UIImageButton *moreButton;
    
        UIMenu *spriteMoreMenu;
};


class SpriteStateEditBar : public UIElement {
    public:
        SpriteStateEditBar(SpriteSet *spriteSet);
        ~SpriteStateEditBar();
    
        void Resize(Number width, Number height);
        void clearBar();
        void refreshBar();
    
        void handleEvent(Event *event);
    
        void moveSelectedLeft();
        void moveSelectedRight();
    
        void doSelectFrame(unsigned int selectedFrameIndex);
    
        bool isFrameSelected(unsigned int frameID);
        void deleteSelectedFrames();
    
        void Update();
    
        void setSceneSprite(SceneSprite *sprite);
        void setSpriteState(SpriteState *state);
    
        PolycodeEditor *editor;
    
    protected:
    
        Vector2 clickBaseCoord;
        Vector2 frameMoveBase;
    
        bool draggingFrames;
        bool extendingFrame;
        unsigned int extendingID;
        unsigned int extendingIndex;
    
        Number zoomScale;
        SpriteState *spriteState;
        SpriteSet *spriteSet;
        SceneSprite *sceneSprite;
    
        Number defaultFrameWidth;
    
        SceneMesh *barMesh;
        SceneMesh *barMeshBg;
        SceneMesh *frameTicksMesh;
        SceneMesh *frameGripsMesh;
    
        UIElement *barBase;
        UIScrollContainer *scroller;
    
        std::vector<unsigned int> selectedFrames;
};

class SpriteStateBrowser : public UIElement {
    public:
        SpriteStateBrowser();
        ~SpriteStateBrowser();
    
        void Resize(Number width, Number height);
    
        UITreeContainer *stateTreeView;
        UIRect *headerBg;
    
        UIImageButton *newStateButton;
        UIImageButton *removeStateButton;
        UIImageButton *moreButton;
        PolycodeEditor *editor;
    
};

class SpriteStateEditorDetails : public UIElement {
    public:
        SpriteStateEditorDetails(SpriteSet *spriteSet);
        ~SpriteStateEditorDetails();
    
        void Resize(Number width, Number height);
        void handleEvent(Event *event);
    
        void Update();
    
        void setSpriteState(SpriteState *state);
        SpriteState *getSpriteState();
    
        void setSceneSprite(SceneSprite *spritePreview);

        PolycodeSpriteEditorActionData *makeStateData();
    
        void refreshState();
    
        UIButton *getAppendFramesButton();
        SpriteStateEditBar *getEditBar();
    
        PolycodeEditor *editor;
    
    protected:
    
        UIRect *headerBg;
    
        SpriteState *spriteState;
        SpriteSet *spriteSet;
        SceneSprite *sceneSprite;
    
        UITextInput *fpsInput;
        UITextInput *scaleInput;
        UITextInput *bBoxWidthInput;
        UITextInput *bBoxHeightInput;

        UITextInput *offsetXInput;
        UITextInput *offsetYInput;
    
        UIButton *appendFramesButton;
        UIButton *removeFramesButton;
        UIButton *clearFramesButton;
    
        UIImageButton *playButton;
        UIImageButton *pauseButton;
        SpriteStateEditBar *editBar;
    
};

class SpriteStateEditor : public UIElement {
    public:
        SpriteStateEditor(SpriteSet *spriteSet);
        ~SpriteStateEditor();
    
        void setSpriteEntry(Sprite *entry);
        void refreshStates();
        void handleEvent(Event *event);
    
        void Resize(Number width, Number height);
    
        SpriteStateEditorDetails *getDetailsEditor();
        SpriteStateBrowser *getStateBrowser();
        SpriteState *getSelectedState();
        PolycodeEditor *editor;
    
    protected:
        UITreeContainer *stateTreeView;
        SpriteSet *spriteSet;
        SpriteState *selectedState;
    
        UIMenu *stateMoreMenu;
    
        SpriteStateBrowser *stateBrowser;
    
        Sprite *spriteSetEntry;
    
        UIImageButton *newStateButton;
    
        UIHSizer *stateSizer;

    
        SpriteStateEditorDetails *stateDetails;
};

class PolycodeSpriteEditor : public PolycodeEditor {
	public:
		PolycodeSpriteEditor();
		virtual ~PolycodeSpriteEditor();
		
		void handleEvent(Event *event);
		
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
		void saveFile();
    
        void doAction(String actionName, PolycodeEditorActionData *data);
        void selectAll();
				
	protected:
	
        SpriteSet *sprite;
        UIVSizer *mainSizer;
        UIHSizer *topSizer;
    
        UIHSizer *bottomSizer;
    
        PolycodeSpriteEditorActionData *beforeData;
    
        SpriteSheetEditor *spriteSheetEditor;
        SpriteBrowser *spriteBrowser;
        SpriteStateEditor *stateEditor;
        SpritePreview *spritePreview;
    
        UIButton *addFramesButton;
    
};

class PolycodeSpriteEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeSpriteEditorFactory() : PolycodeEditorFactory() { extensions.push_back("sprites"); }
		PolycodeEditor *createEditor() { return new PolycodeSpriteEditor(); }
};
