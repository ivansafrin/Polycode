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
 
#include "PolycodeEntityEditor.h"
#include "PolycodeFrame.h"
#include "PolyCubemap.h"
#include "PolycodeMaterialEditor.h"

extern UIGlobalMenu *globalMenu;
extern PolycodeFrame *globalFrame;
extern Scene *globalScene;

LightDisplay::LightDisplay(SceneLight *light) : Entity() {
    editorOnly = true;
    this->light = light;
    spotSpot = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 1.0, 1.0, 32);
	spotSpot->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
    addChild(spotSpot);
    spotSpot->setColor(1.0, 0.8, 0.0, 1.0);
    spotSpot->enabled = false;
    
    fovSceneMesh = new SceneMesh(Mesh::LINE_MESH);
    fovSceneMesh->setColor(1.0, 0.8, 0.0, 1.0);
    fovMesh = fovSceneMesh->getMesh();
    fovMesh->indexedMesh = true;
    addChild(fovSceneMesh);
    
    fovMesh->addVertex(0.0, 0.0, 0.0);
    
    fovMesh->addVertex(-1.0, 1.0, -1.0);
    fovMesh->addVertex(1.0, 1.0, -1.0);
    fovMesh->addVertex(1.0, -1.0, -1.0);
    fovMesh->addVertex(-1.0, -1.0, -1.0);
    
    fovMesh->addIndexedFace(0, 1);
    fovMesh->addIndexedFace(0, 2);
    fovMesh->addIndexedFace(0, 3);
    fovMesh->addIndexedFace(0, 4);
    
    
    light->addChild(this);
}

LightDisplay::~LightDisplay() {
    
}

void LightDisplay::Update() {
    if(light->getLightType() == SceneLight::SPOT_LIGHT) {
        spotSpot->enabled = true;
        fovSceneMesh->enabled = true;
        Number distance = light->getIntensity() * 2.0;
        Number spotAngle = ((light->getSpotlightCutoff()) * 2.0);
        Number spotLightSize = ((PI * 2.0) * distance * spotAngle) / 360.0;
        
        spotSpot->setPosition(0.0, 0.0, -distance);
        spotSpot->setPrimitiveOptions(ScenePrimitive::TYPE_LINE_CIRCLE, spotLightSize, spotLightSize, 32);
       	spotSpot->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
        
        spotLightSize *= 0.5;
        fovMesh->getActualVertex(1)->set(sin(PI/2.0)*spotLightSize, cos(PI/2.0)*spotLightSize, -distance);
        fovMesh->getActualVertex(2)->set(sin(PI)*spotLightSize, cos(PI)*spotLightSize, -distance);
        fovMesh->getActualVertex(3)->set(sin(PI + (PI/2.0))*spotLightSize, cos(PI + (PI/2.0))*spotLightSize, -distance);
        fovMesh->getActualVertex(4)->set(sin(PI*2.0)*spotLightSize, cos(PI*2.0)*spotLightSize, -distance);
         fovMesh->dirtyArray(RenderDataArray::VERTEX_DATA_ARRAY);
    } else {
        spotSpot->enabled = false;
        fovSceneMesh->enabled = false;
    }
}


CameraDisplay::CameraDisplay(Camera *camera) : Entity() {
    
    editorOnly = true;
    
    fovSceneMesh = new SceneMesh(Mesh::LINE_MESH);
    fovSceneMesh->setColor(1.0, 0.0, 1.0, 1.0);
    fovMesh = fovSceneMesh->getMesh();
    fovMesh->indexedMesh = true;
    
    fovMesh->addVertex(0.0, 0.0, 0.0);
    
    fovMesh->addVertex(-1.0, 1.0, -1.0);
    fovMesh->addVertex(1.0, 1.0, -1.0);
    fovMesh->addVertex(1.0, -1.0, -1.0);
    fovMesh->addVertex(-1.0, -1.0, -1.0);
    
    fovMesh->addIndexedFace(0, 1);
    fovMesh->addIndexedFace(0, 2);
    fovMesh->addIndexedFace(0, 3);
    fovMesh->addIndexedFace(0, 4);
    
    fovMesh->addIndexedFace(1, 2);
    fovMesh->addIndexedFace(2, 3);
    fovMesh->addIndexedFace(3, 4);
    fovMesh->addIndexedFace(4, 1);
    
    addChild(fovSceneMesh);
    
    camera->addChild(this);
    this->camera = camera;
}

CameraDisplay::~CameraDisplay() {
    
}

void CameraDisplay::Update() {
    
    if(camera->getOrthoMode()) {

        Number xPos = camera->getOrthoSizeX() * 0.5;
        Number yPos = camera->getOrthoSizeY() * 0.5;
        Number zPos = 0.0;

 
        switch(camera->getOrthoSizeMode()) {
            case Camera::ORTHO_SIZE_LOCK_HEIGHT:
                xPos = yPos * (camera->getViewport().w/camera->getViewport().h);
            break;
            case Camera::ORTHO_SIZE_LOCK_WIDTH:
                yPos = xPos * (camera->getViewport().h/camera->getViewport().w);
            break;
            case Camera::ORTHO_SIZE_VIEWPORT:
                xPos = camera->getViewport().w * 0.5;
                yPos = camera->getViewport().h * 0.5;
            break;
        }
        
        fovMesh->getActualVertex(1)->set(-xPos, yPos, zPos);
        fovMesh->getActualVertex(2)->set(xPos, yPos, zPos);
        fovMesh->getActualVertex(3)->set(xPos, -yPos, zPos);
        fovMesh->getActualVertex(4)->set(-xPos, -yPos, zPos);
        fovMesh->dirtyArray(RenderDataArray::VERTEX_DATA_ARRAY);
    } else {
        Number fovRad = (90+camera->getFOV()/2.0) * TORADIANS;
        Number displayScale = 3.0;
        Number xPos = cos(fovRad) * displayScale;
        Number yPos = xPos * 0.5625;
        Number zPos = -sin(fovRad) * displayScale * 0.5;
        
        fovMesh->getActualVertex(1)->set(-xPos, yPos, zPos);
        fovMesh->getActualVertex(2)->set(xPos, yPos, zPos);
        fovMesh->getActualVertex(3)->set(xPos, -yPos, zPos);
        fovMesh->getActualVertex(4)->set(-xPos, -yPos, zPos);
        fovMesh->dirtyArray(RenderDataArray::VERTEX_DATA_ARRAY);
    }
}

CameraPreviewWindow::CameraPreviewWindow() : UIElement() {
    
    bgRect = new UIRect((160 * 1.5)+16, (90 * 1.5) + 28);
    addChild(bgRect);
    bgRect->setColor(0.0, 0.0, 0.0, 0.5);
    
    UILabel *label = new UILabel("CAMERA PREVIEW", 11);
    label->setColor(1.0, 1.0, 1.0, 1.0);
    addChild(label);
    label->setPosition(15, 3);
    
    previewRect = new UIRect(160 * 1.5, 90 * 1.5);
    previewRect->setPosition(8, 20);
    addChild(previewRect);
    enabled = false;
    camera = NULL;
    scene = NULL;
    renderTexture = NULL;
}

CameraPreviewWindow::~CameraPreviewWindow() {
    
}

void CameraPreviewWindow::setCamera(Scene *scene, Camera *camera) {
    this->camera = camera;
    this->scene = scene;
    if(camera) {
        enabled = true;
        if(renderTexture) {
            delete renderTexture;
        }
        renderTexture = new SceneRenderTexture(scene, camera, previewRect->getWidth(), previewRect->getHeight());
        previewRect->setTexture(renderTexture->getTargetTexture());
        
    } else {
        enabled = false;
    }
}

EntityEditorMainView::EntityEditorMainView() {
	processInputEvents = true;
    multiselectIndex = 0;

	mainScene = new Scene(Scene::SCENE_3D, true);
	renderTexture = new SceneRenderTexture(mainScene, mainScene->getDefaultCamera(), 512, 512);
	mainScene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);	
	mainScene->useClearColor = true;
	mainScene->rootEntity.processInputEvents = true;
	   
	renderTextureShape = new UIRect(256, 256);
	renderTextureShape->setAnchorPoint(-1.0, -1.0, 0.0);	
	renderTextureShape->setTexture(renderTexture->getTargetTexture());
	addChild(renderTextureShape);
	renderTextureShape->setPosition(0, 30);

    cameraPreview = new CameraPreviewWindow();
    addChild(cameraPreview);
    cameraPreview->setPosition(5, 35);
    
    
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
    
	
	topBar = new Entity();
	addChild(topBar);
	topBar->setPosition(0, 0);
	topBar->processInputEvents = true;
    
	
	mainScene->getDefaultCamera()->setPosition(10, 10, 10);
	mainScene->getDefaultCamera( )->lookAt(Vector3());
	mainScene->getDefaultCamera()->setClippingPlanes(0.01, 10000);
    
	grid = new EditorGrid();
	mainScene->addChild(grid);
	
    sceneObjectRoot = new Entity();
    sceneObjectRoot->processInputEvents = true;
    mainScene->addChild(sceneObjectRoot);
    
	transformGizmo = new TransformGizmo(mainScene, mainScene->getDefaultCamera());
	mainScene->addChild(transformGizmo);		
	trackballCamera = new TrackballCamera(mainScene->getDefaultCamera(), renderTextureShape);
    trackballCamera->addEventListener(this, Event::CHANGE_EVENT);
	
    addEntityButton = new UIImageButton("entityEditor/add_entity.png", 1.0, 24, 24);
	topBar->addChild(addEntityButton);
    addEntityButton->setPosition(4, 2);
    addEntityButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
	transformGizmoMenu = new TransformGizmoMenu(transformGizmo);
	topBar->addChild(transformGizmoMenu);
    transformGizmoMenu->setPositionX(40);
    
    modeSwitchDropdown = new UIComboBox(globalMenu, 100);
    topBar->addChild(modeSwitchDropdown);
    
    modeSwitchDropdown->addComboItem("3D MODE");
    modeSwitchDropdown->addComboItem("2D MODE");
    modeSwitchDropdown->setSelectedIndex(0);
    modeSwitchDropdown->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    editorMode = EDITOR_MODE_3D;
    
    input = CoreServices::getInstance()->getCore()->getInput();
    input->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void EntityEditorMainView::setEditorMode(int newMode) {
    editorMode = newMode;
    if(editorMode == EDITOR_MODE_3D) {
        mainScene->setSceneType(Scene::SCENE_3D);
        grid->setGridMode(EditorGrid::GRID_MODE_3D);
        transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_3D);
        mainScene->getDefaultCamera()->setOrthoMode(false);
        mainScene->getDefaultCamera()->setClippingPlanes(1, 1000);
        trackballCamera->disableRotation(false);
    } else {
        mainScene->setSceneType(Scene::SCENE_2D);
        mainScene->getDefaultCamera()->setOrthoMode(true);
        mainScene->getDefaultCamera()->setClippingPlanes(-1, 10000);
        trackballCamera->setCameraPosition(trackballCamera->getOribitingCenter()+Vector3(0.0, 0.0, trackballCamera->getCameraDistance()));
        grid->setGridMode(EditorGrid::GRID_MODE_2D);
        transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_2D);
        trackballCamera->disableRotation(true);
        Update();
    }
}

Entity *EntityEditorMainView::getSelectedEntity() {
    if(selectedEntities.size() > 0) {
        return selectedEntities[selectedEntities.size()-1];
    } else {
        return NULL;
    }
}

void EntityEditorMainView::Update() {
    
    if(entitiesToSelect.size() != 0) {
        if(multiselectIndex > entitiesToSelect.size()-1) {
            multiselectIndex = 0;
        }
        selectEntity(entitiesToSelect[multiselectIndex], input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT));
        multiselectIndex++;
        entitiesToSelect.clear();
    }
    
    if(editorMode == EDITOR_MODE_2D) {
        Number aspect = renderTextureShape->getWidth() / renderTextureShape->getHeight();
        mainScene->getDefaultCamera()->setOrthoSize(trackballCamera->getCameraDistance() * aspect, trackballCamera->getCameraDistance());
    }
    
    for(int i=0; i < icons.size(); i++) {
        Number scale;
        if(editorMode == EDITOR_MODE_2D) {
            scale = trackballCamera->getCameraDistance() * 0.1;
        } else {
            scale = mainScene->getDefaultCamera()->getPosition().distance(icons[i]->getConcatenatedMatrix().getPosition()) * 0.1;
        }
        icons[i]->setScale(scale, scale, scale);
    }
}

void EntityEditorMainView::createIcon(Entity *entity, String iconFile) {
    
    entity->removeAllHandlersForListener(this);
    
    ScenePrimitive *iconPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.4, 0.4);
    
    iconPrimitive->setMaterialByName("Unlit");
	Texture *tex = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile("entityEditor/"+iconFile);
	if(iconPrimitive->getLocalShaderOptions()) {
        iconPrimitive->getLocalShaderOptions()->addTexture("diffuse", tex);
	}
    
    entity->addChild(iconPrimitive);
    iconPrimitive->billboardMode = true;
    iconPrimitive->processInputEvents = true;
    iconPrimitive->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    
    iconPrimitive->addTag("");
    iconPrimitive->depthTest = false;
    iconPrimitive->depthWrite = false;
    iconPrimitive->editorOnly = true;
    iconPrimitive->alphaTest = true;
    iconPrimitive->setUserData(entity);
    icons.push_back(iconPrimitive);
}

void EntityEditorMainView::setEditorPropsRecursive(Entity *entity) {
    setEditorProps(entity);
    for(int i=0; i < entity->getNumChildren(); i++) {
        setEditorProps(entity->getChildAtIndex(i));
    }
}

void EntityEditorMainView::setEditorProps(Entity *entity) {
    entity->processInputEvents = true;
    entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(entity);
    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(entity);
    
    if(sceneMesh && !emitter) {
        sceneMesh->wireFrameColor = Color(1.0, 0.8, 0.3, 1.0);
//        sceneMesh->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
        sceneMesh->useGeometryHitDetection = true;
    }
    
    SceneLight *sceneLight = dynamic_cast<SceneLight*>(entity);
    if(sceneLight) {
        createIcon(entity, "light_icon.png");
        LightDisplay *lightVis = new LightDisplay(sceneLight);
    }
    
    if(emitter) {
        createIcon(entity, "emitter_icon.png");
    }

    SceneSound *sound = dynamic_cast<SceneSound*>(entity);
    if(sound) {
        createIcon(entity, "sound_icon.png");
    }

    Camera *camera = dynamic_cast<Camera*>(entity);
    if(camera) {
        CameraDisplay *camVis = new CameraDisplay(camera);
        createIcon(entity, "camera_icon.png");
    }
    
    if(!emitter && !sceneLight && !camera && !sound && !sceneMesh && entity != sceneObjectRoot) {
        createIcon(entity, "empty_icon.png");
    }
    
    
}

void EntityEditorMainView::addEntityFromMenu(String command) {

    if(command == "add_primitive") {
        ScenePrimitive  *newPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0, 1.0, 1.0);
        sceneObjectRoot->addChild(newPrimitive);
        setEditorProps(newPrimitive);
        newPrimitive->setPosition(cursorPosition);
        selectEntity(newPrimitive);
        return;
    }

    if(command == "add_empty") {
        Entity *newEntity = new Entity();
        sceneObjectRoot->addChild(newEntity);
        setEditorProps(newEntity);
        newEntity->setPosition(cursorPosition);
        selectEntity(newEntity);
        return;
    }

    if(command == "add_sound") {
        SceneSound *newSound = new SceneSound("default.wav", 1.0, 2.0);
        sceneObjectRoot->addChild(newSound);
        setEditorProps(newSound);
        newSound->setPosition(cursorPosition);
        selectEntity(newSound);
        return;
    }

    if(command == "add_sound") {
        SceneSound *newSound = new SceneSound("default.wav", 1.0, 2.0);
        sceneObjectRoot->addChild(newSound);
        setEditorProps(newSound);
        newSound->setPosition(cursorPosition);
        selectEntity(newSound);
        return;
    }

    if(command == "add_camera") {
        Camera *newCamera = new Camera(mainScene);
        sceneObjectRoot->addChild(newCamera);
        setEditorProps(newCamera);
        newCamera->setPosition(cursorPosition);
        selectEntity(newCamera);
        return;
    }
    
    if(command == "add_image") {
        assetSelectType = "image";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("png");
        globalFrame->showAssetBrowser(extensions);
        return;
    }

    if(command == "add_sprite") {
        assetSelectType = "sprite";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("sprite");
        globalFrame->showAssetBrowser(extensions);
        return;
    }
    
    if(command == "add_label") {
        SceneLabel  *newLabel = new SceneLabel("TEXT", 12, "sans", Label::ANTIALIAS_FULL, 1.0);
        newLabel->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
        newLabel->setAnchorPoint(0.0, 0.0, 0.0);
        newLabel->snapToPixels = false;
        newLabel->positionAtBaseline = false;
        sceneObjectRoot->addChild(newLabel);
        setEditorProps(newLabel);
        newLabel->setPosition(cursorPosition);
        selectEntity(newLabel);
        return;
    }

    
    if(command == "add_light") {
        SceneLight *newLight = new SceneLight(SceneLight::POINT_LIGHT, mainScene, 1.0);
        sceneObjectRoot->addChild(newLight);
        mainScene->addLight(newLight);
        setEditorProps(newLight);
        newLight->setPosition(cursorPosition);
        selectEntity(newLight);
        return;
    }
    
    if(command == "add_mesh") {
        assetSelectType = "mesh";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("mesh");
        globalFrame->showAssetBrowser(extensions);
        return;
    }
    
    if(command == "add_particles") {
        SceneParticleEmitter  *newEmitter = new SceneParticleEmitter(30, 3.0, 0.2);
        newEmitter->bBox = Vector3(0.5, 0.5, 0.5);
        
        newEmitter->setParticleType(SceneParticleEmitter::PARTICLE_TYPE_QUAD);
        
        sceneObjectRoot->addChild(newEmitter);
        setEditorProps(newEmitter);
        newEmitter->setPosition(cursorPosition);
        
        
        newEmitter->scaleCurve.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
        newEmitter->scaleCurve.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);
        
        newEmitter->colorCurveR.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
        newEmitter->colorCurveR.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);
        
        newEmitter->colorCurveG.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
        newEmitter->colorCurveG.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);
        
        newEmitter->colorCurveB.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
        newEmitter->colorCurveB.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);
        
        newEmitter->colorCurveA.addControlPoint2dWithHandles(-0.1, 0.5, 0.0, 0.5, 0.1, 0.5);
        newEmitter->colorCurveA.addControlPoint2dWithHandles(0.9, 0.5, 1.0, 0.5, 1.1, 0.5);
        
        selectEntity(newEmitter);
        return;
        
    }
}

void EntityEditorMainView::deleteSelected() {

    for(int i=0; i < selectedEntities.size(); i++) {
        selectedEntities[i]->getParentEntity()->removeChild(selectedEntities[i]);
    }
    
    for(int i=0; i < selectedEntities.size(); i++) {
        selectedEntities[i]->setOwnsChildrenRecursive(true);
        for(int j=0; j < icons.size(); j++) {
            if(icons[j]->getUserData() == selectedEntities[i]) {
                delete icons[j];
                icons[j]->getParentEntity()->removeChild(icons[j]);
                icons.erase(icons.begin()+j);
                break;
            }
        }
        selectedEntities[i]->removeAllHandlers();
        delete selectedEntities[i];
    }
    
    selectedEntities.clear();
    transformGizmo->setTransformSelection(selectedEntities);
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void EntityEditorMainView::handleEvent(Event *event) {

    if(event->getDispatcher() == trackballCamera) {
        Update();
    } else if(event->getDispatcher() == modeSwitchDropdown) {
        setEditorMode(modeSwitchDropdown->getSelectedIndex());
    } else if(event->getDispatcher() == globalFrame->assetBrowser) {
        if(event->getEventCode() == UIEvent::OK_EVENT) {
            if(assetSelectType == "mesh") {
                SceneMesh *newMesh = new SceneMesh(globalFrame->assetBrowser->getFullSelectedAssetPath());
                newMesh->cacheToVertexBuffer(true);
                sceneObjectRoot->addChild(newMesh);
                setEditorProps(newMesh);
                newMesh->setPosition(cursorPosition);
                selectEntity(newMesh);
            } else if(assetSelectType == "image") {
                SceneImage *newImage = new SceneImage(globalFrame->assetBrowser->getFullSelectedAssetPath());
                newImage->setMaterialByName("Unlit");
                if(newImage->getLocalShaderOptions()) {
                    newImage->getLocalShaderOptions()->addTexture("diffuse", newImage->getTexture());
                }
                sceneObjectRoot->addChild(newImage);
                setEditorProps(newImage);
                newImage->setPosition(cursorPosition);
                selectEntity(newImage);
        } else if(assetSelectType == "sprite") {
            SceneSprite *newSprite = new SceneSprite(globalFrame->assetBrowser->getFullSelectedAssetPath());
            
            if(newSprite->getNumAnimations()) {
                newSprite->playAnimation(newSprite->getAnimationAtIndex(0)->name, 0, false);
            }
            
            newSprite->setMaterialByName("Unlit");
            if(newSprite->getLocalShaderOptions()) {
                newSprite->getLocalShaderOptions()->addTexture("diffuse", newSprite->getTexture());
            }
            sceneObjectRoot->addChild(newSprite);
            setEditorProps(newSprite);
            newSprite->setPosition(cursorPosition);
            selectEntity(newSprite);
        }
        
        
            globalFrame->assetBrowser->removeAllHandlersForListener(this);
            globalFrame->hideModal();
        }
        
    } else if(event->getDispatcher() == addEntityMenu) {
        addEntityMenu->removeAllHandlersForListener(this);
        String command = addEntityMenu->getSelectedItem()->getMenuItemID();
        addEntityMenu = NULL;
        addEntityFromMenu(command);
    } else if(event->getDispatcher() == addEntityButton) {
        addEntityMenu = globalMenu->showMenuAtMouse(150);
        addEntityMenu->addOption("Add Primitive", "add_primitive");
        addEntityMenu->addOption("Add Mesh", "add_mesh");
        addEntityMenu->addOption("Add Entity", "add_entity");
        addEntityMenu->addDivider();
        addEntityMenu->addOption("Add Sprite", "add_sprite");
        addEntityMenu->addOption("Add Image", "add_image");
        addEntityMenu->addOption("Add Label", "add_label");
        addEntityMenu->addDivider();
        addEntityMenu->addOption("Add Light", "add_light");
        addEntityMenu->addOption("Add Particle System", "add_particles");
        addEntityMenu->addOption("Add Sound", "add_sound");
        addEntityMenu->addOption("Add Camera", "add_camera");
        addEntityMenu->addDivider();
        addEntityMenu->addOption("Add Empty", "add_empty");
        addEntityMenu->fitToScreenVertical();
        addEntityMenu->addEventListener(this, UIEvent::OK_EVENT);
    } else if(event->getDispatcher() == input) {
        InputEvent *inputEvent = (InputEvent*) event;
        if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
            switch(inputEvent->key) {
                case KEY_BACKSPACE:
                case KEY_DELETE:
                    //deleteSelected();
                break;
            }
        }
    } else {
        if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN ) {
            InputEvent *inputEvent = (InputEvent*) event;

            if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {
                Entity* targetEntity = (Entity*) event->getDispatcher();
                
                // if it's an icon, select the entity linked to the icon
                for(int i=0; i < icons.size(); i++) {
                    if(icons[i] == targetEntity) {
                        targetEntity = (Entity*)targetEntity->getUserData();
                    }
                }
                
                entitiesToSelect.push_back(targetEntity);
            }
        }
    }
}

Scene *EntityEditorMainView::getMainScene() {
    return mainScene;
}

void EntityEditorMainView::doEntityDeselect(Entity *targetEntity) {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    if(sceneMesh) {
        sceneMesh->overlayWireframe = false;
    }
}

void EntityEditorMainView::doEntitySelect(Entity *targetEntity) {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(targetEntity);
    
    if(sceneMesh && ! emitter) {
        sceneMesh->overlayWireframe = true;
    }
    
    Camera *camera = dynamic_cast<Camera*>(targetEntity);
    cameraPreview->setCamera(mainScene, camera);
}


void EntityEditorMainView::selectEntity(Entity *targetEntity, bool addToSelection) {
    
    bool doNotReselect = false;
    if(!addToSelection) {
        for(int i=0; i < selectedEntities.size(); i++) {
            doEntityDeselect(selectedEntities[i]);
        }
        selectedEntities.clear();
    } else {
        for(int i=0; i < selectedEntities.size(); i++) {
            if(targetEntity == selectedEntities[i]) {
                doEntityDeselect(targetEntity);
                selectedEntities.erase(selectedEntities.begin() + i);
                doNotReselect = true;
                break;
            }
        }
    }

    if(!doNotReselect) {
        selectedEntities.push_back(targetEntity);
        doEntitySelect(targetEntity);
    }
    
    transformGizmo->setTransformSelection(selectedEntities);
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
    
}

Entity *EntityEditorMainView::getObjectRoot() {
    return sceneObjectRoot;
}

void EntityEditorMainView::setObjectRoot(Entity *entity) {
    if(sceneObjectRoot) {
        sceneObjectRoot->getParentEntity()->removeChild(sceneObjectRoot);
        delete sceneObjectRoot;
    }
    sceneObjectRoot = entity;
    sceneObjectRoot->processInputEvents = true;
    mainScene->addChild(sceneObjectRoot);
    sceneObjectRoot->getParentEntity()->moveChildBottom(sceneObjectRoot);
}

EntityEditorMainView::~EntityEditorMainView() {
	
}

void EntityEditorMainView::Resize(Number width, Number height) {
	headerBg->Resize(width, 30);
	modeSwitchDropdown->setPosition(width-110, 4);
    
    Vector2 screenPos = renderTextureShape->getScreenPosition(globalScene->getDefaultCamera()->getProjectionMatrix(), globalScene->getDefaultCamera()->getTransformMatrix(), globalScene->getDefaultCamera()->getViewport());
    
	mainScene->sceneMouseRect.x = screenPos.x;
	mainScene->sceneMouseRect.y = screenPos.y;
	mainScene->sceneMouseRect.w = renderTextureShape->getWidth();
	mainScene->sceneMouseRect.h = renderTextureShape->getHeight();
    mainScene->remapMouse = true;
    
	renderTexture->resizeRenderTexture(width, height-30);
	renderTextureShape->setTexture(renderTexture->getTargetTexture());		
	renderTextureShape->Resize(width, height-30);
    Update();
}

EntityEditorPropertyContainer::EntityEditorPropertyContainer() : UIElement() {
    
    propIconSelector = new UIIconSelector();
    addChild(propIconSelector);
    propIconSelector->addIcon("entityEditor/properties_icon.png");
    propIconSelector->addIcon("entityEditor/icon_tree.png");
    propIconSelector->addIcon("entityEditor/settings_icon.png");
    propIconSelector->setPosition(10.0, 3.0);
    propIconSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    propertyView = new EntityEditorPropertyView();
    addChild(propertyView);
    propertyView->setPosition(0.0, 30.0);
    currentView = propertyView;
    
    treeView = new EntityEditorTreeView();
    addChild(treeView);
    treeView->setPosition(0.0, 30.0);
    treeView->visible = false;
}

void EntityEditorPropertyContainer::handleEvent(Event *event) {
    if(event->getDispatcher() == propIconSelector) {
        currentView->visible = false;
        currentView->enabled = false;
        switch(propIconSelector->getSelectedIndex()) {
            case 0:
                currentView = propertyView;
            break;
            case 1:
                currentView = treeView;
                treeView->refreshTree();
            break;
            case 2:
                currentView = treeView;
            break;
        }
        currentView->visible = true;
        currentView->enabled = true;
    }
}

EntityEditorPropertyContainer::~EntityEditorPropertyContainer() {
    
}

void EntityEditorPropertyContainer::Resize(Number width, Number height) {
    propertyView->Resize(width, height-30);
    treeView->Resize(width, height-30);
}


PolycodeEntityEditor::PolycodeEntityEditor() : PolycodeEditor(true){
	mainSizer = new UIHSizer(300, 300, 300, false);
	addChild(mainSizer);
	
	mainView = new EntityEditorMainView();
    mainView->addEventListener(this, Event::CHANGE_EVENT);
	mainSizer->addLeftChild(mainView);
    
    mainSizer->setMinimumSize(200);
    
    propertyContainer = new EntityEditorPropertyContainer();
    propertyView = propertyContainer->propertyView;
    treeView = propertyContainer->treeView;
    
    treeView->addEventListener(this, Event::CHANGE_EVENT);
    
    mainSizer->addRightChild(propertyContainer);
}

void PolycodeEntityEditor::handleEvent(Event *event) {
    
    if(event->getDispatcher() == treeView) {
        mainView->selectEntity(treeView->getSelectedEntity());
    }
    
    if(event->getDispatcher() == mainView) {
        switch(event->getEventCode()) {
            case Event::CHANGE_EVENT:
                propertyView->setEntity(mainView->getSelectedEntity());
                treeView->setSelectedEntity(mainView->getSelectedEntity());
            break;
        }
    }
    
    
    PolycodeEditor::handleEvent(event);
}

PolycodeEntityEditor::~PolycodeEntityEditor() {
}

bool PolycodeEntityEditor::openFile(OSFileEntry filePath) {	
	PolycodeEditor::openFile(filePath);
//    return true;
    SceneEntityInstance *loadedInstance = new SceneEntityInstance(mainView->getMainScene(), filePath.fullPath);
    mainView->setObjectRoot(loadedInstance);
    mainView->setEditorPropsRecursive(loadedInstance);
    
    treeView->setRootEntity(loadedInstance);
    
	return true;
}

void PolycodeEntityEditor::Activate() {
    Resize(getWidth(), getHeight());
}

void PolycodeEntityEditor::saveCurveToObject(ObjectEntry *entry, BezierCurve *curve) {
    ObjectEntry *controlPoints = entry->addChild("controlPoints");
    
    for(int i=0; i < curve->getNumControlPoints(); i++) {
        ObjectEntry *controlPointEntry = controlPoints->addChild("controlPoint");
        ObjectEntry *pt1 = controlPointEntry->addChild("pt1");
        pt1->addChild("x", curve->getControlPoint(i)->p1.x);
        pt1->addChild("y", curve->getControlPoint(i)->p1.y);
        pt1->addChild("z", curve->getControlPoint(i)->p1.z);
        
        ObjectEntry *pt2 = controlPointEntry->addChild("pt2");
        pt2->addChild("x", curve->getControlPoint(i)->p2.x);
        pt2->addChild("y", curve->getControlPoint(i)->p2.y);
        pt2->addChild("z", curve->getControlPoint(i)->p2.z);
        
        ObjectEntry *pt3 = controlPointEntry->addChild("pt3");
        pt3->addChild("x", curve->getControlPoint(i)->p3.x);
        pt3->addChild("y", curve->getControlPoint(i)->p3.y);
        pt3->addChild("z", curve->getControlPoint(i)->p3.z);
    }
}

void PolycodeEntityEditor::saveEntityToObjectEntry(Entity *entity, ObjectEntry *entry) {
    if(entity->editorOnly)
        return;
    
    entry->addChild("id", entity->id);
    
    String tagString = "";
    for(int i=0; i < entity->getNumTags(); i++) {
        if(i != 0) {
            tagString += ",";
        }
        tagString += entity->getTagAtIndex(i);
    }
    entry->addChild("tags", tagString);

    
    if(entity->entityProps.size() > 0) {
        ObjectEntry *props = entry->addChild("props");
        for(int i=0; i < entity->entityProps.size(); i++) {
            ObjectEntry *prop = props->addChild("prop");
            prop->addChild("name", entity->entityProps[i].propName);
            prop->addChild("value", entity->entityProps[i].propValue);
        }
    }
    
    if(dynamic_cast<SceneEntityInstance*>(entity)) {
        if(!(*(entry))["type"]) {
            entry->addChild("type", "SceneEntityInstance");
        }
        SceneEntityInstance *instance = (SceneEntityInstance*) entity;
        ObjectEntry *instanceEntry = entry->addChild("SceneEntityInstance");
        instanceEntry->addChild("filePath", instance->getFileName());
    }
    
    if(dynamic_cast<SceneParticleEmitter*>(entity)) {
        if(!(*(entry))["type"])
            entry->addChild("type", "SceneParticleEmitter");
        
        SceneParticleEmitter *emitter = (SceneParticleEmitter*) entity;
        
        ObjectEntry *emitterEntry = entry->addChild("SceneParticleEmitter");
        emitterEntry->addChild("type", (int)emitter->getParticleType());
        emitterEntry->addChild("count", (int)emitter->getParticleCount());
        emitterEntry->addChild("lifetime", emitter->getParticleLifetime());
        emitterEntry->addChild("size", emitter->getParticleSize());
        emitterEntry->addChild("world", emitter->getParticlesInWorldSpace());
        emitterEntry->addChild("loop", emitter->getLoopParticles());
        emitterEntry->addChild("rX", emitter->getParticleRotationSpeed().x);
        emitterEntry->addChild("rY", emitter->getParticleRotationSpeed().y);
        emitterEntry->addChild("rZ", emitter->getParticleRotationSpeed().z);
        emitterEntry->addChild("gX", emitter->getGravity().x);
        emitterEntry->addChild("gY", emitter->getGravity().y);
        emitterEntry->addChild("gZ", emitter->getGravity().z);
        emitterEntry->addChild("dirX", emitter->getParticleDirection().x);
        emitterEntry->addChild("dirY", emitter->getParticleDirection().y);
        emitterEntry->addChild("dirZ", emitter->getParticleDirection().z);
        emitterEntry->addChild("eX", emitter->getEmitterSize().x);
        emitterEntry->addChild("eY", emitter->getEmitterSize().y);
        emitterEntry->addChild("eZ", emitter->getEmitterSize().z);
        emitterEntry->addChild("devX", emitter->getDirectionDeviation().x);
        emitterEntry->addChild("devY", emitter->getDirectionDeviation().y);
        emitterEntry->addChild("devZ", emitter->getDirectionDeviation().z);
        emitterEntry->addChild("perlin", emitter->getPerlinEnabled());
        emitterEntry->addChild("pX", emitter->getPerlinValue().x);
        emitterEntry->addChild("pY", emitter->getPerlinValue().y);
        emitterEntry->addChild("pZ", emitter->getPerlinValue().z);
        emitterEntry->addChild("useColorCurves", emitter->useColorCurves);
        emitterEntry->addChild("useScaleCurve", emitter->useScaleCurve);
        
        if(emitter->useScaleCurve) {
            saveCurveToObject(emitterEntry->addChild("scaleCurve"), &emitter->scaleCurve);
        }
        if(emitter->useColorCurves) {
            saveCurveToObject(emitterEntry->addChild("colorCurveR"), &emitter->colorCurveR);
            saveCurveToObject(emitterEntry->addChild("colorCurveG"), &emitter->colorCurveG);
            saveCurveToObject(emitterEntry->addChild("colorCurveB"), &emitter->colorCurveB);
            saveCurveToObject(emitterEntry->addChild("colorCurveA"), &emitter->colorCurveA);
        }
    }
    
    if(dynamic_cast<SceneSprite*>(entity)) {
        if(!(*(entry))["type"])
            entry->addChild("type", "SceneSprite");
        SceneSprite *sprite = (SceneSprite*) entity;
        
        ObjectEntry *spriteEntry = entry->addChild("SceneSprite");
        spriteEntry->addChild("filePath", sprite->getFileName());
        
        String animName = "";
        if(sprite->getCurrentAnimation()) {
            animName = sprite->getCurrentAnimation()->name;
        }
        spriteEntry->addChild("anim", animName);
    }
    
    if(dynamic_cast<SceneLabel*>(entity)) {
        SceneLabel *label = (SceneLabel*) entity;
        
        if(!(*(entry))["type"])
            entry->addChild("type", "SceneLabel");
        ObjectEntry *labelEntry = entry->addChild("SceneLabel");
        labelEntry->addChild("text", label->getText());
        labelEntry->addChild("font", label->getLabel()->getFont()->getFontName());
        labelEntry->addChild("size", (Number)label->getLabel()->getSize());
        labelEntry->addChild("actualHeight", label->getLabelActualHeight());
        labelEntry->addChild("aaMode", (int)label->getLabel()->getAntialiasMode());
    }
    
    if(dynamic_cast<SceneLight*>(entity)) {
        SceneLight *light = (SceneLight*) entity;
        if(!(*(entry))["type"]) {
            entry->addChild("type", "SceneLight");
        }
        
        ObjectEntry *lightEntry = entry->addChild("SceneLight");
        lightEntry->addChild("type", light->getType());

        lightEntry->addChild("cR", light->lightColor.r);
        lightEntry->addChild("cG", light->lightColor.g);
        lightEntry->addChild("cB", light->lightColor.b);
        lightEntry->addChild("cA", light->lightColor.a);

        lightEntry->addChild("scR", light->specularLightColor.r);
        lightEntry->addChild("scG", light->specularLightColor.g);
        lightEntry->addChild("scB", light->specularLightColor.b);
        lightEntry->addChild("scA", light->specularLightColor.a);

        lightEntry->addChild("intensity", light->getIntensity());

        lightEntry->addChild("cAtt", light->getConstantAttenuation());
        lightEntry->addChild("lAtt", light->getLinearAttenuation());
        lightEntry->addChild("qAtt", light->getQuadraticAttenuation());

        if(light->getType() == SceneLight::SPOT_LIGHT) {
            lightEntry->addChild("spotCutoff", light->getSpotlightCutoff());
            lightEntry->addChild("spotExponent", light->getSpotlightExponent());
            lightEntry->addChild("shadows", light->areShadowsEnabled());
            if(light->areShadowsEnabled()) {
                lightEntry->addChild("shadowmapFOV", light->getShadowMapFOV());
                lightEntry->addChild("shadowmapRes", (int)light->getShadowMapResolution());
            }
        }
        
    }
    
    if(dynamic_cast<SceneSound*>(entity)) {
        SceneSound *sound = (SceneSound*) entity;
        
        if(!(*(entry))["type"]) {
            entry->addChild("type", "SceneSound");
        }
        ObjectEntry *soundEntry = entry->addChild("SceneSound");
        soundEntry->addChild("filePath", sound->getSound()->getFileName());
        soundEntry->addChild("refDistance", sound->getSound()->getReferenceDistance());
        soundEntry->addChild("maxDistance", sound->getSound()->getMaxDistance());
        soundEntry->addChild("volume", sound->getSound()->getVolume());
        soundEntry->addChild("pitch", sound->getSound()->getPitch());
    }

    if(dynamic_cast<Camera*>(entity)) {
        Camera *camera = (Camera*) entity;
        
        if(!(*(entry))["type"]) {
            entry->addChild("type", "Camera");
        }
        
        ObjectEntry *cameraEntry = entry->addChild("Camera");
        
        cameraEntry->addChild("exposure", camera->getExposureLevel());
        cameraEntry->addChild("nearClip", camera->getNearClipppingPlane());
        cameraEntry->addChild("farClip", camera->getFarClipppingPlane());
        cameraEntry->addChild("ortho", camera->getOrthoMode());
        if(camera->getOrthoMode()) {
            cameraEntry->addChild("sizeMode", camera->getOrthoSizeMode());
            cameraEntry->addChild("orthoWidth", camera->getOrthoSizeX());
            cameraEntry->addChild("orthoHeight", camera->getOrthoSizeY());
        } else {
            cameraEntry->addChild("fov", camera->getFOV());
        }
    }
    
    if(dynamic_cast<ScenePrimitive*>(entity) && !dynamic_cast<SceneSprite*>(entity) && !dynamic_cast<SceneLabel*>(entity)) {
        if(!(*(entry))["type"]) {
            entry->addChild("type", "ScenePrimitive");
        }
        ScenePrimitive *primitive = (ScenePrimitive*) entity;
        ObjectEntry *primitiveEntry = entry->addChild("ScenePrimitive");
        primitiveEntry->addChild("type", primitive->getPrimitiveType());
        primitiveEntry->addChild("p1", primitive->getPrimitiveParameter1());
        primitiveEntry->addChild("p2", primitive->getPrimitiveParameter2());
        primitiveEntry->addChild("p3", primitive->getPrimitiveParameter3());
        primitiveEntry->addChild("p4", primitive->getPrimitiveParameter4());
        primitiveEntry->addChild("p5", primitive->getPrimitiveParameter5());
    }
    
    if(dynamic_cast<SceneMesh*>(entity)) {
        if(!(*(entry))["type"]) {
            entry->addChild("type", "SceneMesh");
        }
        
        SceneMesh *sceneMesh = (SceneMesh*) entity;
        
        ObjectEntry *meshEntry = entry->addChild("SceneMesh");
        
        if(sceneMesh->getFilename() != "") {
            meshEntry->addChild("file", sceneMesh->getFilename().replace(parentProject->getRootFolder()+"/", ""));
        }
        
        if(sceneMesh->getMaterial()) {
            meshEntry->addChild("material", sceneMesh->getMaterial()->getResourceName());
            ObjectEntry *shaderOptions = meshEntry->addChild("shader_options");
            saveShaderOptionsToEntry(shaderOptions, sceneMesh->getMaterial(), sceneMesh->getLocalShaderOptions());
        }
    }
    
    if(!(*(entry))["type"])
        entry->addChild("type", "Entity");
    
    entry->addChild("cR", entity->color.r);
    entry->addChild("cG", entity->color.g);
    entry->addChild("cB", entity->color.b);
    entry->addChild("cA", entity->color.a);
    entry->addChild("blendMode", entity->blendingMode);
    
    entry->addChild("sX", entity->getScale().x);
    entry->addChild("sY", entity->getScale().y);
    entry->addChild("sZ", entity->getScale().z);
        
    entry->addChild("rX", entity->getPitch());
    entry->addChild("rY", entity->getYaw());
    entry->addChild("rZ", entity->getRoll());
    
    entry->addChild("pX", entity->getPosition().x);
    entry->addChild("pY", entity->getPosition().y);
    entry->addChild("pZ", entity->getPosition().z);
    
    entry->addChild("bbX", entity->bBox.x);
    entry->addChild("bbY", entity->bBox.y);
    entry->addChild("bbZ", entity->bBox.z);
    
    ObjectEntry *children = NULL;
    
    for(int i=0; i < entity->getNumChildren(); i++) {
        if(!entity->getChildAtIndex(i)->editorOnly) {
            if(!children)
                children = entry->addChild("children");
            ObjectEntry *child = children->addChild("child");
            saveEntityToObjectEntry((ScreenEntity*)entity->getChildAtIndex(i), child);
        }
    }
}

void PolycodeEntityEditor::saveShaderOptionsToEntry(ObjectEntry *entry, Material *material, ShaderBinding *binding) {

	
    if(material->getNumShaders() > 0) {
        for(int s=0; s < material->getNumShaders(); s++) {
            Shader *shader = material->getShader(s);
            
            ObjectEntry *shaderEntry = entry->addChild("shader");
            ObjectEntry *texturesEntry = shaderEntry->addChild("textures");
            
            for(int j=0; j < shader->expectedTextures.size(); j++) {
                Texture *texture = binding->getTexture(shader->expectedTextures[j]);
                if(texture) {
                    String texturePath = texture->getResourcePath();
                    texturePath = texturePath.replace(parentProject->getRootFolder()+"/", "");
                    ObjectEntry *textureEntry = texturesEntry->addChild("texture", texturePath);
                    textureEntry->addChild("name", shader->expectedTextures[j]);
                }
            }
            
            for(int j=0; j < shader->expectedCubemaps.size(); j++) {
                Cubemap *cubemap = binding->getCubemap(shader->expectedCubemaps[j]);
                if(cubemap) {
                    String cubemapName = cubemap->getResourceName();
                    ObjectEntry *cubemapEntry = texturesEntry->addChild("cubemap", cubemapName);
                    cubemapEntry->addChild("name", shader->expectedCubemaps[j]);
                }
            }
            
            
            if(shader->expectedParams.size() > 0 || shader->expectedParams.size() > 0) {
                ObjectEntry *paramsEntry = shaderEntry->addChild("params");
                
                for(int j=0; j < shader->expectedParams.size(); j++) {
                    if(binding->getLocalParamByName(shader->expectedParams[j].name)) {
                        ObjectEntry *paramEntry = paramsEntry->addChild("param");
                        paramEntry->addChild("name", shader->expectedParams[j].name);
                        paramEntry->addChild("value", PolycodeMaterialEditor::createStringValue(shader->expectedParams[j].type, binding->getLocalParamByName(shader->expectedParams[j].name)->data));
                    }
                }
            }
        }
    }
}

void PolycodeEntityEditor::saveFile() {
    Object saveObject;
    
    saveObject.root.name = "entity";
    ObjectEntry *children = saveObject.root.addChild("root");
    saveEntityToObjectEntry(mainView->getObjectRoot(), children);
    saveObject.saveToXML(filePath);
    setHasChanges(false);
}


void PolycodeEntityEditor::Resize(int x, int y) {
	mainSizer->Resize(x, y);
	PolycodeEditor::Resize(x,y);
}

