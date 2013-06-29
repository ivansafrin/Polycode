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
#include "PolycodeProps.h"

using namespace Polycode;


class MaterialBrowserData  {
public:
	MaterialBrowserData() {
		material = NULL;
		shader = NULL;
		cubemap = NULL;
		postMaterial = NULL;
	}
	Material *material;
	Material *postMaterial;
	Shader *shader;
	Cubemap *cubemap;
	String name;
};


class MaterialPreviewBox : public UIElement {
	public:
		MaterialPreviewBox();
		~MaterialPreviewBox();
		void setMaterial(Material *material);
		void showPrimitive(unsigned int index);
		void clearMaterial();

		void handleEvent(Event *event);

		Scene *previewScene;
		SceneLight *mainLight;
		SceneLight *secondLight;
		SceneRenderTexture *renderTexture;
		ScreenShape *previewShape;

		std::vector<UIImageButton*> shapeSwitches;
		std::vector<ScenePrimitive*> shapePrimitives;
		ScreenImage *shapeSelector;

		ScreenEntity *previewBase;
		ScenePrimitive *previewPrimitive;
		Material *currentMaterial;
};

class PostPreviewBox : public UIElement {
	public:
		PostPreviewBox();
		~PostPreviewBox();
		void setMaterial(Material *material);
		void clearMaterial();
		void handleEvent(Event *event);
		void Resize(Number width, Number height);
		void Update();	

		Scene *previewScene;
		SceneRenderTexture *renderTexture;
		ScreenShape *previewShape;
		ScreenEntity *previewBase;
		ScenePrimitive *previewPrimitive;
		Material *currentMaterial;
		ScreenShape *headerBg;

		Number spinValue;

		UICheckBox *rotateCheckBox;
		UICheckBox *hdrCheckBox;
		UITextInput *cameraExposureInput;
		UITextInput *lightStrength;

		SceneLight *mainLight;
		SceneLight *secondLight;

};


class MaterialBrowser : public UIElement {
	public:
		MaterialBrowser();
		~MaterialBrowser();

		void Resize(Number width, Number height);

		UITree *addMaterial(Material *material);
		UITree *addShader(Shader *shader);
		UITree *addCubemap(Cubemap *cubemap);
		UITree *addPostMaterial(Material *material);

		void removeSelected();

		void handleEvent(Event *event);

		MaterialBrowserData *selectedData;

		UIImageButton *newShaderButton;	
		UIImageButton *newMaterialButton;
		UIImageButton *newCubemapButton;
		UIImageButton *newPostButton;

		UIImageButton *removeButton;

		UITree *selectedNode;

	protected:

		ScreenShape *headerBg;
		UITree *shadersNode;
		UITree *materialsNode;
		UITree *cubemapsNode;
		UITree *postEffectsNode;

		UITreeContainer *treeContainer;	
};

class CubemapEditorPane : public UIElement {
	public:
		CubemapEditorPane();
		~CubemapEditorPane();
		void Resize(Number width, Number height);
		void setCubemap(Cubemap *cubemap);
		void handleEvent(Event *event);
		Cubemap *currentCubemap;

	protected:

		PropList *propList;
		ScreenShape *headerBg;

		TextureProp *yPosTexture;
		TextureProp *yNegTexture;
		TextureProp *xPosTexture;
		TextureProp *xNegTexture;
		TextureProp *zPosTexture;
		TextureProp *zNegTexture;

		StringProp *nameProp;

		MaterialPreviewBox *cubemapPreview;
};

class PostEditorPane : public UIElement {
	public:
		PostEditorPane();
		~PostEditorPane();
		void Resize(Number width, Number height);
		void setMaterial(Material *material);
		void handleEvent(Event *event);
		Material *currentMaterial;

		void adjustPreview();

		protected:

		ScreenShape *headerBgBottom;

		PropList *propList;
		PropSheet *baseProps;
		ShaderPassesSheet *passProps;
		RenderTargetsSheet *targetsProps;

		PropList *optionsPropList;

		TargetBindingsSheet *targetBindingProps;
		ShaderTexturesSheet *shaderTextureSheet;
		ShaderOptionsSheet *shaderOptionsSheet;

		UIVSizer *mainSizer;
		UIElement *topElement;
		UIElement *bottomElement;

		StringProp *nameProp;
		BoolProp *fp16Prop;

		PostPreviewBox *postPreview;

		Screen *previewScreen;


};

class ShaderEditorPane : public UIElement {
	public:
		ShaderEditorPane();
		~ShaderEditorPane();
		void Resize(Number width, Number height);
		void setShader(Shader *shader);

		void handleEvent(Event *event);

		void reloadPrograms();

		Shader *currentShader;
		PolycodeProject *parentProject;

	protected:


		bool changingShader;

		bool choosingVertexProgram;

		PropList *propList;
		ScreenShape *headerBg;

		ComboProp *vertexProgramProp;
		ComboProp *fragmentProgramProp;

		StringProp *nameProp;
		BoolProp *screenShaderProp;


		NumberProp *areaLightsProp;
		NumberProp *spotLightsProp;
};

class MaterialEditorPane : public UIElement {
	public:
		MaterialEditorPane();
		~MaterialEditorPane();

		void setMaterial(Material *material);
		void handleEvent(Event *event);

		void reloadShaders();
		void Resize(Number width, Number height);

		Material *currentMaterial;
	protected:

		MaterialPreviewBox *materialPreview;
		bool changingMaterial;

		ScreenShape *headerBg;

		PropList *propList;

		StringProp *nameProp;
		ComboProp *blendModeProp;
		ComboProp *shaderProp;

		ShaderTexturesSheet *shaderTextureSheet;
		ShaderOptionsSheet *shaderOptionsSheet;	
};

class MaterialMainWindow : public UIElement {
	public:
	MaterialMainWindow();
	~MaterialMainWindow(){}

	void Resize(Number width, Number height);

	MaterialEditorPane *materialPane;
	ShaderEditorPane *shaderPane;
	CubemapEditorPane *cubemapPane;
	PostEditorPane *postPane;

	UIColorPicker *colorPicker;
};

class PolycodeMaterialEditor : public PolycodeEditor {
	public:
	PolycodeMaterialEditor();
	virtual ~PolycodeMaterialEditor();

	bool openFile(OSFileEntry filePath);
	void Resize(int x, int y);


	void handleEvent(Event *event);	
	void saveFile();
	void saveMaterials(ObjectEntry *materialsEntry, std::vector<Material*> materials);

	String createStringValue(unsigned int type, void *value);

	protected:
		ScreenImage *editorImage;

		MaterialBrowser *materialBrowser;
		UIHSizer *mainSizer;

		MaterialMainWindow *mainWindow;
		std::vector<Material*> materials;
		std::vector<Shader*> shaders;
		std::vector<Cubemap*> cubemaps;
		std::vector<Material*> postMaterials;

		UITree *selectedMaterialNode;
};

class PolycodeMaterialEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeMaterialEditorFactory() : PolycodeEditorFactory() { extensions.push_back("mat"); }
		PolycodeEditor *createEditor() { return new PolycodeMaterialEditor(); }
};
