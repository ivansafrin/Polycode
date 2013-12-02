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
#include "PolyUIElement.h"
#include <Polycode.h>
#include "PolycodeUI.h"
#include "EntityEditorPropertyView.h"

#include "TrackballCamera.h"

#include "TransformGizmo.h"
#include "EditorGrid.h"

using namespace Polycode;

class LightDisplay : public Entity {
public:
    LightDisplay(SceneLight *light);
    ~LightDisplay();
    void Update();
    
private:
    ScenePrimitive *spotSpot;
    SceneMesh *fovSceneMesh;    
    Mesh *fovMesh;
    
    SceneLight *light;
};

class CameraDisplay : public Entity {
    public:
        CameraDisplay(Camera *camera);
        ~CameraDisplay();
        void Update();
    
    
    private:
        SceneMesh *fovSceneMesh;
        Mesh *fovMesh;
        Camera *camera;
};

class CameraPreviewWindow : public UIElement {
    public:
        CameraPreviewWindow();
        ~CameraPreviewWindow();

        void setCamera(Scene *scene, Camera *camera);
    
    private:
    
        SceneRenderTexture *renderTexture;
        Camera *camera;
        Scene *scene;
        UIRect *bgRect;
        UIRect *previewRect;
    
};

class EntityEditorMainView : public UIElement {
		public:
			EntityEditorMainView();
			~EntityEditorMainView();
			
            void createIcon(Entity *entity, String iconFile);
            void setEditorProps(Entity *entity);
    
            void selectEntity(Entity *targetEntity, bool addToSelection = false);
    
			void handleEvent(Event *event);
			void Resize(Number width, Number height);
			void Update();
            void addEntityFromMenu(String command);
    
            void doEntityDeselect(Entity *targetEntity);
            void doEntitySelect(Entity *targetEntity);
            void setEditorMode(int newMode);
            Entity *getSelectedEntity();
    
            static const int EDITOR_MODE_3D = 0;
            static const int EDITOR_MODE_2D = 1;
    
		protected:
    
            CoreInput *input;
			
            int editorMode;
			Entity *topBar;
			UIRect *headerBg;
				
            unsigned int multiselectIndex;
			std::vector<Entity*> selectedEntities;
            std::vector<Entity*> entitiesToSelect;
    
			Scene *mainScene;
            Entity *sceneObjectRoot;
    
			SceneRenderTexture *renderTexture;
			UIRect *renderTextureShape;	

			TransformGizmo *transformGizmo;
			TransformGizmoMenu *transformGizmoMenu;
			TrackballCamera *trackballCamera;
			EditorGrid *grid;
    
            UIImageButton *addEntityButton;
            UIComboBox *modeSwitchDropdown;
            UIMenu *addEntityMenu;
    
            CameraPreviewWindow *cameraPreview;
    
            std::vector<ScenePrimitive*> icons;
    
            Vector3 cursorPosition;
            String assetSelectType;
    
};

class PolycodeEntityEditor : public PolycodeEditor {
	public:
		PolycodeEntityEditor();
		virtual ~PolycodeEntityEditor();
		
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
    
        void Activate();
        void saveFile();
    
		
        void handleEvent(Event *event);
    
	protected:
	
		EntityEditorMainView *mainView;
        EntityEditorPropertyView *propertyView;
    
		UIHSizer *mainSizer;
        UIVSizer *rightSizer;
    
    
};

class PolycodeEntityEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeEntityEditorFactory() : PolycodeEditorFactory() { extensions.push_back("entity"); }
		PolycodeEditor *createEditor() { return new PolycodeEntityEditor(); }
};
