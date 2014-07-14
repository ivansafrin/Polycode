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

using namespace Polycode;

class SpriteFrame {
    public:
        Polycode::Rectangle coordinates;
        Vector2 anchorPoint;
        unsigned int frameID;
};

class SpriteSet;

class SpriteState {
    public:
        SpriteState(SpriteSet *spriteSet, String name);
    
        void setName(String name);
        String getName() const;
    
        void appendFrames(std::vector<unsigned int> newFrameIDs);
    
        unsigned int getNumFrameIDs();
        unsigned int getFrameIDAtIndex(unsigned int index);
    
        Mesh *getMeshForFrameIndex(unsigned int index);
    
        void insertFrame(unsigned int index, unsigned int frameID);
    
        void setNewFrameIDs(std::vector<unsigned int> newIDs);
    
        void removeFrameByIndex(unsigned int frameIndex);
        void removeFrameIndices(std::vector<unsigned int> indices);
        void clearFrames();
    
        void setPixelsPerUnit(Number ppu);
        Number getPixelsPerUnit();
    
        void rebuildStateMeshes();
    
        void setStateFPS(Number fps);
        Number getStateFPS();
    
        void setBoundingBox(Vector2 boundingBox);
        Vector2 getBoundingBox();
    
        Vector2 getSpriteOffset();
        void setSpriteOffset(const Vector2 &offset);
    
    protected:
    
        Vector2 boundingBox;
        Vector2 spriteOffset;
        Number pixelsPerUnit;
        Number stateFPS;
        SpriteSet *spriteSet;
        String name;
        std::vector<unsigned int> frameIDs;
        std::vector<Mesh*> frameMeshes;
};

class Sprite {
    public:
        Sprite(String name);
        ~Sprite();
    
        String getName();
        void setName(String name);
    
        void addSpriteState(SpriteState *state);
        void removeSpriteState(SpriteState *state);
    
        unsigned int getNumStates();
        SpriteState *getState(unsigned int index);
    
    protected:
        String name;
        std::vector<SpriteState*> states;
};

class SpriteSet {
    public:
        SpriteSet(String imageFileName);
        ~SpriteSet();

        void setTexture(Texture *texture);
        Texture *getTexture();
        Texture *loadTexture(String imageFileName);
    
        void addSpriteEntry(Sprite *newEntry);
        unsigned int getNumSpriteEntries() const;
        Sprite *getSpriteEntry(unsigned int index) const;
        void removeSprite(Sprite *sprite);
    
        void loadSpriteSet(String fileName);
    
        // frame manipulation
        void addSpriteFrame(const SpriteFrame &frame, bool assignID = true);
        unsigned int getNumFrames() const;
        SpriteFrame getSpriteFrame(unsigned int index) const;
    
        SpriteFrame getSpriteFrameByID(unsigned int frameID) const;
        void removeFrameByID(unsigned int frameID);
    
        void setSpriteFrame(const SpriteFrame &frame);
    
        void clearFrames();
    
        // automatic frame generation
        void createGridFrames(Number width, Number height, const Vector2 &defaultAnchor);
        void createFramesFromIslands(unsigned int minDistance, const Vector2 &defaultAnchor);
    
    protected:
    
        unsigned int nextFrameIDIndex;
        Texture *spriteTexture;
        std::vector<SpriteFrame> frames;
        std::vector<Sprite*> sprites;
};


class SceneSpriteRewrite : public SceneMesh {
    public:
        SceneSpriteRewrite(SpriteSet *spriteSet);
        ~SceneSpriteRewrite();
    
        SpriteSet *getSpriteSet();
        Sprite *getCurrentSprite();
    
        void setCurrentFrame(unsigned int frameIndex);
        unsigned int getCurrentFrame();
        void Update();
        void Render();
    
        void setPaused(bool val);
        bool isPaused();
    
        void setSprite(Sprite *spriteEntry);
        void setSpriteState(SpriteState *spriteState);
        SpriteState *getCurrentSpriteState();

    
    protected:
    
        bool paused;
        Core *core;
        unsigned int currentFrame;
        Mesh *defaultMesh;
        Sprite *currentSprite;
        SpriteState *currentSpriteState;
        SpriteSet *spriteSet;
        Number spriteTimer;
        Number spriteTimerVal;
    
};

class SpritePreview : public UIElement {
    public:
        SpritePreview(SpriteSet *spriteSet);
        ~SpritePreview();
    
        void Update();
    
        void handleEvent(Event *event);
    
        SceneSpriteRewrite *getSceneSprite();
        void Resize(Number width, Number height);
    
    protected:
        UIRect *headerBg;    
        UIImage *previewBg;
        SceneSpriteRewrite *sprite;
    
        UIIconSelector *bgSelector;
    
        SceneMesh *boundingBoxPreview;
    
};

class TransformGrips : public UIElement {
    public:
        TransformGrips();
        ~TransformGrips();
    
        void setGripRectangle(Polycode::Rectangle rectangle, Vector2 offset);
    
        void handleEvent(Event *event);
        Polycode::Rectangle getGripRectangle();
    
        Vector2 getAnchorPoint();
    
    private:
    
        bool transforming;
        UIImage *movingTransform;
    
        Polycode::Rectangle gripRectangle;
        Vector2 anchorPoint;
    
        Vector2 mouseBase;
    
        UIRect *mainRect;
        UIImage *transformTL;
        UIImage *transformT;
        UIImage *transformTR;
        UIImage *transformR;
        UIImage *transformL;
        UIImage *transformBL;
        UIImage *transformB;
        UIImage *transformBR;
        UIImage *transformOffset;
        std::vector<UIElement*> grips;
    
};

class SpriteSheetEditor : public UIElement {
    public:
        SpriteSheetEditor(SpriteSet *sprite);
        ~SpriteSheetEditor();
    
        void handleEvent(Event *event);
    
        void Update();
    
        void Render();
    
        void deleteSelectedFrames();
    
        void clearSelected();
        bool hasSelectedID(unsigned int frameID);
        std::vector<unsigned int> getSelectedFrameIDs();
    
        void Resize(Number width, Number height);
    
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
    
        SpriteSet *sprite;
        UIRect *previewImage;
    
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
    
        void setSceneSprite(SceneSpriteRewrite *sprite);
        void setSpriteState(SpriteState *state);
    
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
        SceneSpriteRewrite *sceneSprite;
    
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
    
        void setSceneSprite(SceneSpriteRewrite *spritePreview);
    
        void refreshState();
    
        UIButton *getAppendFramesButton();
        SpriteStateEditBar *getEditBar();
    
    protected:
    
        UIRect *headerBg;
    
        SpriteState *spriteState;
        SpriteSet *spriteSet;
        SceneSpriteRewrite *sceneSprite;
    
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
    
        SpriteState *getSelectedState();

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
				
	protected:
	
        SpriteSet *sprite;
        UIVSizer *mainSizer;
        UIHSizer *topSizer;
    
        UIHSizer *bottomSizer;
    
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
