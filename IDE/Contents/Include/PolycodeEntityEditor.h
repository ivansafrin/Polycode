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
#include "EntityEditorTreeView.h"
#include "EntityEditorSettingsView.h"

#include "TrackballCamera.h"

#include "TransformGizmo.h"
#include "EditorGrid.h"

using namespace Polycode;

class EntityEditorClipboardData {
public:
    EntityEditorClipboardData(){}
    std::vector<Entity*> entities;
};

class PolycodeSceneEditorActionDataEntry {
public:
    PolycodeSceneEditorActionDataEntry(){
        entity = NULL;
        parentEntity = NULL;
    }
    
    PolycodeSceneEditorActionDataEntry(Vector3 vec3, Number number);
    PolycodeSceneEditorActionDataEntry(Quaternion quat);
    PolycodeSceneEditorActionDataEntry(Vector3 vec3);
    PolycodeSceneEditorActionDataEntry(Vector3 vec3, Vector3 vec3Secondary);
    PolycodeSceneEditorActionDataEntry(Quaternion quat, Vector3 vec3);
    PolycodeSceneEditorActionDataEntry(Number number);
    PolycodeSceneEditorActionDataEntry(Entity *entity);
    Vector3 vec3;
    Vector3 vec3Secondary;
    Quaternion quat;
    Number number;
    Entity *entity;
    Entity *parentEntity;
};


class PolycodeSceneEditorActionData : public PolycodeEditorActionData {
    public:
        PolycodeSceneEditorActionData() {
            reverse = true;
            deleteEntitiesInDestructor = false;
        }
    
        ~PolycodeSceneEditorActionData() {
            if(deleteEntitiesInDestructor) {
                for(int i=0; i < entries.size(); i++) {
                    if(!entries[i].entity->getParentEntity()) {
                        delete entries[i].entity;
                    }
                }
            }
        }
    
        std::vector<PolycodeSceneEditorActionDataEntry> entries;
        bool deleteEntitiesInDestructor;
        bool reverse;
};

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
    
        void handleEvent(Event *event);
        void Resize(Number width, Number height);
    
        void setCamera(Scene *scene, Camera *camera);
    
        bool isPinned();
    
    private:
    
        SceneRenderTexture *renderTexture;
        Camera *camera;
        Scene *scene;
        UIRect *bgRect;
        UIRect *previewRect;
        bool pinned;
        bool cameraSelected;
    
        UIComboBox *aspectCombo;
        UIButton *pinButton;
};

class SceneMeshSettings {
    public:
        Material *material;
        bool backfaceCulled;
        ShaderBinding *shaderBinding;
};


class EntityEditorMainView : public UIElement {
		public:
			EntityEditorMainView(PolycodeEditor *editor);
			~EntityEditorMainView();
			
            void createIcon(Entity *entity, String iconFile);
            void setEditorProps(Entity *entity);
    
            void selectEntity(Entity *targetEntity, bool addToSelection = false, bool doAction = true);
    
			void handleEvent(Event *event);
			void Resize(Number width, Number height);
			void Update();
            void addEntityFromMenu(String command);
    
            void doEntityDeselect(Entity *targetEntity);
            void doEntitySelect(Entity *targetEntity);
            void setEditorMode(int newMode);
            Entity *getSelectedEntity();
            std::vector<Entity*> getSelectedEntities();
    
            void setOverlayWireframeRecursive(Entity *targetEntity, bool val);
            void setLinkedEntityPropsRecursive(SceneEntityInstance *parentInstance, Entity *entity);
    
            void Paste(EntityEditorClipboardData *data);
    
            void moveSelectedUp();
            void moveSelectedDown();
            void moveSelectedTop();
            void moveSelectedBottom();
    
            void disableLighting(bool disable);
            void selectNone(bool doAction);
            void selectAll(bool doAction);
    
            void onGainFocus();
            void onLoseFocus();
            void deleteSelected(bool doAction);
    
            void doAction(String actionName, PolycodeEditorActionData *data);
    
            void didPlaceEntity(Entity *entity);
    
            void setBBox();
    
            Entity *getObjectRoot();
            void setObjectRoot(SceneEntityInstance *entity);
    
            Scene *getMainScene();
    
            void setEditorPropsRecursive(Entity *entity);
    
            static const int EDITOR_MODE_3D = 0;
            static const int EDITOR_MODE_2D = 1;
    
		protected:
    
            CoreInput *input;
            PolycodeSceneEditorActionData *beforeData;
			
            bool lightsDisabled;
            int editorMode;
			Entity *topBar;
			Entity *bottomBar;
			UIRect *headerBg;
			UIRect *footerBg;
    
            PolycodeEditor *editor;
				
            unsigned int multiselectIndex;
			std::vector<Entity*> selectedEntities;
            std::vector<Entity*> entitiesToSelect;
    
			Scene *mainScene;
            Entity *sceneObjectRoot;
    
            SceneLight *customLight1;
            SceneLight *customLight2;
    
        	ScenePrimitive *bBoxVis;
    
            Entity *objectRootBase;
            Entity *iconBase;
            SceneEntityInstance *objectRootInstance;
    
			SceneRenderTexture *renderTexture;
			UIRect *renderTextureShape;	

			TransformGizmo *transformGizmo;
			TransformGizmoMenu *transformGizmoMenu;
			TrackballCamera *trackballCamera;
			EditorGrid *grid;
    
            UIImageButton *addEntityButton;
            UIComboBox *modeSwitchDropdown;
            UIMenu *addEntityMenu;
    
            UIIconSelector *shadeModeSelector;
            UIIconSelector *lightingModeSelector;

            UIIconSelector *iconVisibilitySelector;
    
            UIImageButton *moveUpButton;
            UIImageButton *moveTopButton;
            UIImageButton *moveDownButton;
            UIImageButton *moveBottomButton;    
    
            UIImageButton *gridSettingsButton;
            EditorGridSettingsWindow *gridSettings;
            UIIconSelector *snapSelector;
    
            CameraPreviewWindow *cameraPreview;
    
            std::vector<ScenePrimitive*> icons;
    
            Vector3 cursorPosition;
            String assetSelectType;
    
};

class EntityEditorPropertyContainer : public UIElement {
    public:
        EntityEditorPropertyContainer(PolycodeEditor *editor);
        ~EntityEditorPropertyContainer();
        void Resize(Number width, Number height);
    
        void handleEvent(Event *event);
    
        UIElement *currentView;
        EntityEditorPropertyView *propertyView;
        EntityEditorTreeView *treeView;
        EntityEditorSettingsView *settingsView;
        UIIconSelector *propIconSelector;
    
    private:
    
        PolycodeEditor *editor;
};

class PolycodeEntityEditor : public PolycodeEditor {
	public:
		PolycodeEntityEditor();
		virtual ~PolycodeEntityEditor();
		
		bool openFile(OSFileEntry filePath);
		void Resize(int x, int y);
    
        void Activate();
        void saveFile();
        void saveCurveToObject(ObjectEntry *entry, BezierCurve *curve);
        void saveShaderOptionsToEntry(ObjectEntry *entry, Material *material, ShaderBinding *binding);
    
        void saveEntityToObjectEntry(Entity *entity, ObjectEntry *entry);
        void doAction(String actionName, PolycodeEditorActionData *data);
    
        String Copy(void **data);
        void Paste(void *data, String clipboardType);
        void selectAll();
        void destroyClipboardData(void *data, String type);
    
        void handleEvent(Event *event);
    
	protected:
	
        EntityEditorPropertyContainer *propertyContainer;
    
		EntityEditorMainView *mainView;
        EntityEditorPropertyView *propertyView;
        EntityEditorTreeView *treeView;
        EntityEditorSettingsView *settingsView;
    
        SceneEntityInstance *loadedInstance;
		UIHSizer *mainSizer;
    
    
};

class PolycodeEntityEditorFactory : public PolycodeEditorFactory {
	public:
		PolycodeEntityEditorFactory() : PolycodeEditorFactory() { extensions.push_back("entity"); }
		PolycodeEditor *createEditor() { return new PolycodeEntityEditor(); }
};
