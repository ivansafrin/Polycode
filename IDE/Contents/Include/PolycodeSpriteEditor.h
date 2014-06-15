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

class SpriteAnimationEntry : public PropProp {
	public:
		SpriteAnimationEntry(SpriteAnimation *animation);
		~SpriteAnimationEntry();
		
		void setPropWidth(Number width);
		
		void handleEvent(Event *event);
		
		UITextInput *nameInput;
		UITextInput *framesInput;
		UITextInput *speedInput;
						
		UIImageButton *removeButton;
		UIImageButton *playButton;	
		
		SpriteAnimation *animation;
};


class SpritePreviewProp : public PropProp {
	public:
		SpritePreviewProp();
		void setSprite(SceneSprite *sprite);	
		void setPropWidth(Number width);		
		void setSpriteScale(Number scale);		
		SceneSprite *previewSprite;
		Number propWidth;
};

class SpritePreviewSheet : public PropSheet {
	public:
		SpritePreviewSheet();
		void handleEvent(Event *event);
		void setSprite(SceneSprite *sprite);
		
	protected:
		SliderProp *zoomProp;
		SpritePreviewProp *previewProp;
};

class SpriteAnimationsSheet : public PropSheet {
	public:
		SpriteAnimationsSheet();
		void setSprite(SceneSprite *sprite);		
		void refreshAnimationEntries();	
		void handleEvent(Event *event);
		void Update();
		void Resize(Number width, Number height);
		
	protected:
	
		int removeIndex;
		SceneSprite *sprite;
		int lastNumProps;
		UILabel *animHelpLabel;
		UIButton *addAnimationButton;
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
	
		SpriteAnimationsSheet *animationsSheet;
			
		PropList *propList;		
		UIRect *headerBg;	
		
		TextureProp *textureProp;
		NumberProp *widthProp;
		NumberProp *heightProp;	
		
		bool initialLoad;
		
		SceneSprite *previewSprite;		
		SpritePreviewSheet *previewPropSheet;
};

class PolycodeSpriteEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeSpriteEditorFactory() : PolycodeEditorFactory() { extensions.push_back("sprite"); }
		PolycodeEditor *createEditor() { return new PolycodeSpriteEditor(); }
};
