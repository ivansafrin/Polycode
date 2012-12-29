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
#include "PolycodeUI.h"

using namespace Polycode;


class MaterialBrowserData  {
public:
	MaterialBrowserData() {
		material = NULL;
	}
	Material *material;
	String name;
};


class MaterialBrowser : public UIElement {
	public:
		MaterialBrowser();
		~MaterialBrowser();
		
		void Resize(Number width, Number height);
		
		UITree * addMaterial(Material *material);
		void handleEvent(Event *event);
		
		MaterialBrowserData *selectedData;
				
		UIImageButton *newMaterialButton;
		
		UITree *selectedNode;
												
	protected:
	
		ScreenShape *headerBg;
	
		UITree *shadersNode;
		UITree *materialsNode;
		UITree *cubemapsNode;			
	
		UITreeContainer *treeContainer;	
};

class MaterialTextureSlot : public UIElement {
	public:
		MaterialTextureSlot(String textureNameString);
		~MaterialTextureSlot();
		
		ScreenShape *bgShape;
		ScreenShape *imageShape;
		
		ScreenLabel *textureName;
		ScreenLabel *textureFileName;	
		
		String textureString;
};

class MaterialPropertySlot : public UIElement {
	public:
		MaterialPropertySlot(ShaderBinding *binding, ProgramParam param);
		~MaterialPropertySlot();
		
		void handleEvent(Event *event);
		
		ScreenLabel *propertyName;	
		
		ScreenLabel *minLabel;
		ScreenLabel *maxLabel;
							
		UIHSlider *numberSlider;
		UIColorBox *colorBox;
					
		ShaderBinding *binding;		
		ProgramParam param;
		
		String finalName;
		
};

class MaterialEditorPane : public UIWindow {
	public:
		MaterialEditorPane();
		~MaterialEditorPane();
		
		void setMaterial(Material *material);
		
		void clearAll();
		
		void handleEvent(Event *event);
		
		void handleDroppedFile(OSFileEntry file, Number x, Number y);	
		
		void showPrimitive(unsigned int index);
		
		Material *currentMaterial;
				
	protected:
	
	
		std::vector<MaterialTextureSlot*> textureSlots;
		std::vector<MaterialPropertySlot*> fragmentPropertySlots;
	
		ScreenEntity *textureSlotBase;
	
		ScenePrimitive *previewPrimitive;
		
		UIElement *paramsEntity;
		
		Scene *previewScene;
		SceneLight *mainLight;
		SceneLight *secondLight;		
		SceneRenderTexture *renderTexture;
		ScreenShape *previewShape;
		
		UIComboBox *shaderSelector;

		UIComboBox *blendSelector;
		
		UITextInput *nameInput;
		
		std::vector<UIImageButton*> shapeSwitches;
		std::vector<ScenePrimitive*> shapePrimitives;
		ScreenImage *shapeSelector;
		
};

class MaterialMainWindow : public UIElement {
	public:
	MaterialMainWindow();
	~MaterialMainWindow(){}
	
	void Resize(Number width, Number height);
	
	MaterialEditorPane *materialPane;	
	UIColorPicker *colorPicker;
};

class PolycodeMaterialEditor : public PolycodeEditor {
	public:
	PolycodeMaterialEditor();
	virtual ~PolycodeMaterialEditor();
	
	bool openFile(OSFileEntry filePath);
	void Resize(int x, int y);
	
	void handleDroppedFile(OSFileEntry file, Number x, Number y);
	
	void handleEvent(Event *event);	
	void saveFile();
	
	String createStringValue(unsigned int type, void *value);
	
	protected:
		ScreenImage *grid;	
		ScreenImage *editorImage;
		
		MaterialBrowser *materialBrowser;
		UIHSizer *mainSizer;
		
		MaterialMainWindow *mainWindow;
		std::vector<Material*> materials;
		
		UITree *selectedMaterialNode;
};

class PolycodeMaterialEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeMaterialEditorFactory() : PolycodeEditorFactory() { extensions.push_back("mat"); }
		PolycodeEditor *createEditor() { return new PolycodeMaterialEditor(); }
};
