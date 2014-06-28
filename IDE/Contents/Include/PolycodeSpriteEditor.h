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
};

class SceneSpriteRewrite : public SceneMesh {
    public:
        SceneSpriteRewrite(String imageFileName);
        ~SceneSpriteRewrite();
    
    
    
        // frame manipulation
        void addSpriteFrame(const SpriteFrame &frame);
        unsigned int getNumFrames() const;
        SpriteFrame getSpriteFrame(unsigned int index) const;
        void clearFrames();
    
        // automatic frame generation
        void createGridFrames(Number width, Number height);
        void createFramesFromIslands(unsigned int minDistance);
    
    protected:
    
        std::vector<SpriteFrame> frames;
};

class SpriteSheetEditor : public UIElement {
    public:
        SpriteSheetEditor(SceneSpriteRewrite *sprite);
        ~SpriteSheetEditor();
    
        void handleEvent(Event *event);
    
        void Update();
    
        void Resize(Number width, Number height);
    
    protected:
    
        SceneSpriteRewrite *sprite;
        UIRect *previewImage;
    
        UIImage *previewBg;
    
        SceneMesh *frameVisualizerMesh;
    
        Entity *bottomMenu;
        UIRect *bottomMenuRect;
        UIButton *changeImageButton;
        UIButton *generateFramesButton;
    
        UITextInput *uniformGridWidthInput;
        UITextInput *uniformGridHeightInput;
    
        UITextInput *minimumDistanceInput;
    
        UIComboBox *generateTypeDropdown;
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
	
        SceneSpriteRewrite *sprite;
        UIVSizer *mainSizer;
        UIHSizer *topSizer;
    
        SpriteSheetEditor *spriteSheetEditor;
    
};

class PolycodeSpriteEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeSpriteEditorFactory() : PolycodeEditorFactory() { extensions.push_back("sprite"); }
		PolycodeEditor *createEditor() { return new PolycodeSpriteEditor(); }
};
