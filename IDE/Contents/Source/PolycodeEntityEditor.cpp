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

PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Vector3 vec3, Number number) {
    this->vec3 = vec3;
    this->number = number;
}
PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Vector3 vec3) {
    this->vec3 = vec3;
}

PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Quaternion quat) {
    this->quat = quat;
}

PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Vector3 vec3, Vector3 vec3Secondary) {
    this->vec3 = vec3;
    this->vec3Secondary = vec3Secondary;
}

PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Quaternion quat, Vector3 vec3) {
    this->quat = quat;
    this->vec3 = vec3;
}


PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Number number) {
    this->number = number;
}

PolycodeSceneEditorActionDataEntry::PolycodeSceneEditorActionDataEntry(Entity *entity) {
    this->entity = entity;
}

DummyTargetEntity::DummyTargetEntity() {
    addTag("dummy_target");
    propertyEntity = NULL;
}

DummyTargetEntity::~DummyTargetEntity() {
    
}

Vector3 DummyTargetEntity::getSelectedPoint() const {
    return selectedPoint;
}

void DummyTargetEntity::selectPoint(Vector3 point, Number distance) {
    selectedPoint = point;
    InputEvent *rebroadcastEvent = new InputEvent();
    rebroadcastEvent->mouseButton = CoreInput::MOUSE_BUTTON2;
    rebroadcastEvent->hitDistance = distance;
    dispatchEvent(rebroadcastEvent, InputEvent::EVENT_MOUSEDOWN);
    
}

Entity *DummyTargetEntity::getPropertyEntity() {
    return propertyEntity;
}

CurveDisplay::CurveDisplay(Scene *parentScene, SceneCurve *curve) : DummyTargetEntity () {
    editorOnly = true;
    curve->addChild(this);
    this->curve = curve;
    this->parentScene = parentScene;
    targetPoint = NULL;
    propertyEntity = curve;
    colorAffectsChildren = false;
    
    controlPointLines = new SceneMesh(Mesh::LINE_MESH);
    controlPointLines->setColor(1.0, 1.0, 0.4, 1.0);
    addChild(controlPointLines);
    
   
    mainPoints = new SceneMesh(Mesh::POINT_MESH);
    mainPoints->setColor(0.0, 0.5, 1.0, 1.0);
    addChild(mainPoints);
    mainPoints->pointSize = 10.0;
    mainPoints->pointSmooth = true;

    controlPoints = new SceneMesh(Mesh::POINT_MESH);
    controlPoints->setColor(1.0, 0.7, 0.0, 1.0);
    addChild(controlPoints);
    controlPoints->pointSize = 8.0;
    controlPoints->pointSmooth = true;
    
    renderControlPoints = false;
    
    coreInput = Services()->getCore()->getInput();
    coreInput->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
}

void CurveDisplay::handleDelete() {
    if(targetPoint) {
        if(curve->getCurve()->getNumControlPoints() > 2) {
            curve->getCurve()->removePoint(targetPoint);
        } else {
            globalFrame->messagePopup->setCaption("Curve must have at least two points.");
            globalFrame->showModal(globalFrame->messagePopup);
        }
    }
}

void CurveDisplay::handleDeselect() {
    renderControlPoints = false;
}

void CurveDisplay::handleSelect() {
    renderControlPoints = true;
}

CurveDisplay::~CurveDisplay() {
    Services()->getCore()->getInput()->removeAllHandlersForListener(this);
}

void CurveDisplay::handleEvent(Event *event) {
    
    InputEvent *inputEvent = (InputEvent*) event;
    if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {
        
        Ray ray = parentScene->projectRayFromCameraAndViewportCoordinate(parentScene->getDefaultCamera(), coreInput->getMousePosition());
        
        for(int i=0; i < curve->getCurve()->getNumControlPoints(); i++) {
            Matrix4 parentMatrix = getConcatenatedMatrix();
            Matrix4 pointTransform;
            
            Vector3 pt = curve->getCurve()->getControlPoint(i)->p2;
            pt = parentMatrix * pt;
            Number relativeSize = parentScene->getDefaultCamera()->getPosition().distance(pt) * 0.02;
            Vector3 hitSize(relativeSize, relativeSize, relativeSize);
            pointTransform.setPosition(pt.x, pt.y, pt.z);
            
            Number distance = ray.boxIntersect(hitSize, pointTransform);
            if(distance >= 0.0) {
                selectMode = SELECT_MODE_P2;
                targetPoint = curve->getCurve()->getControlPoint(i);
                selectPoint(pt, distance);
            }
            
            if(renderControlPoints) {
                pt = curve->getCurve()->getControlPoint(i)->p1;
                pt = parentMatrix * pt;
                relativeSize = parentScene->getDefaultCamera()->getPosition().distance(pt) * 0.02;
                hitSize.set(relativeSize, relativeSize, relativeSize);
                pointTransform.setPosition(pt.x, pt.y, pt.z);

                distance = ray.boxIntersect(hitSize, pointTransform);
                if(distance >= 0.0) {
                    selectMode = SELECT_MODE_P1;
                    targetPoint = curve->getCurve()->getControlPoint(i);
                    selectPoint(pt, distance);
                }
                
                pt = curve->getCurve()->getControlPoint(i)->p3;
                pt = parentMatrix * pt;
                relativeSize = parentScene->getDefaultCamera()->getPosition().distance(pt) * 0.02;
                hitSize.set(relativeSize, relativeSize, relativeSize);
                pointTransform.setPosition(pt.x, pt.y, pt.z);
                distance = ray.boxIntersect(hitSize, pointTransform);
                
                if(distance >= 0.0) {
                    selectMode = SELECT_MODE_P3;
                    targetPoint = curve->getCurve()->getControlPoint(i);
                    selectPoint(pt, distance);
                }
            }
        }
    }
}

void CurveDisplay::setDummyTransform(Entity *dummy) {
    if(targetPoint) {
        Vector3 position = dummy->getPosition();
        
        Matrix4 parentMatrix = getConcatenatedMatrix().Inverse();
        position = parentMatrix * position;
        
        Vector3 p1Offset = targetPoint->p1 - targetPoint->p2;
        Vector3 p3Offset = targetPoint->p3 - targetPoint->p2;
        
        switch(selectMode) {
            case SELECT_MODE_P1:
            {
                targetPoint->p1 = position;
                
                // transform the opposing point to match
                Number p3Distance = targetPoint->p3.distance(targetPoint->p2);
                Vector3 p3Normal = p1Offset * -1.0;
                p3Normal.Normalize();
                targetPoint->p3 = targetPoint->p2 + (p3Normal * p3Distance);
            }
            break;
            case SELECT_MODE_P2:
            {
                targetPoint->p2 = position;
                targetPoint->p1 = position+p1Offset;
                targetPoint->p3 = position+p3Offset;
            }
            break;
            case SELECT_MODE_P3:
            {
                targetPoint->p3 = position;
                
                // transform the opposing point to match
                Number p1Distance = targetPoint->p1.distance(targetPoint->p2);
                Vector3 p1Normal = p3Offset * -1.0;
                p1Normal.Normalize();
                targetPoint->p1 = targetPoint->p2 + (p1Normal * p1Distance);
                
            }
            break;
        }
        
        curve->getCurve()->recalculateDistances();
    }
}

void CurveDisplay::Update() {
    
    mainPoints->getMesh()->clearMesh();
    controlPoints->getMesh()->clearMesh();
    controlPointLines->getMesh()->clearMesh();
    
    for(int i=0; i < curve->getCurve()->getNumControlPoints(); i++) {
        
        Vector3 pt2 = curve->getCurve()->getControlPoint(i)->p2;
        mainPoints->getMesh()->addVertex(pt2.x, pt2.y, pt2.z);
        
        if(renderControlPoints) {
            Vector3 pt1 = curve->getCurve()->getControlPoint(i)->p1;
            controlPoints->getMesh()->addVertex(pt1.x, pt1.y, pt1.z);
            
            Vector3 pt3 = curve->getCurve()->getControlPoint(i)->p3;
            controlPoints->getMesh()->addVertex(pt3.x, pt3.y, pt3.z);
            
            
            controlPointLines->getMesh()->addVertex(pt1.x, pt1.y, pt1.z);
            controlPointLines->getMesh()->addVertex(pt2.x, pt2.y, pt2.z);
            
            controlPointLines->getMesh()->addVertex(pt2.x, pt2.y, pt2.z);
            controlPointLines->getMesh()->addVertex(pt3.x, pt3.y, pt3.z);
        }
    }
    
    mainPoints->setLocalBoundingBox(mainPoints->getMesh()->calculateBBox());
    controlPoints->setLocalBoundingBox(controlPoints->getMesh()->calculateBBox());
    controlPointLines->setLocalBoundingBox(controlPointLines->getMesh()->calculateBBox());
    
}

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
    
    fovSceneMesh->setLocalBoundingBox(fovMesh->calculateBBox());
    
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
        fovMesh->setVertexAtOffset(1, sin(PI/2.0)*spotLightSize, cos(PI/2.0)*spotLightSize, -distance);
        fovMesh->setVertexAtOffset(2, sin(PI)*spotLightSize, cos(PI)*spotLightSize, -distance);
        fovMesh->setVertexAtOffset(3, sin(PI + (PI/2.0))*spotLightSize, cos(PI + (PI/2.0))*spotLightSize, -distance);
        fovMesh->setVertexAtOffset(4, sin(PI*2.0)*spotLightSize, cos(PI*2.0)*spotLightSize, -distance);
        fovSceneMesh->setLocalBoundingBox(fovMesh->calculateBBox());
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
    
    fovSceneMesh->setLocalBoundingBox(fovMesh->calculateBBox());
    
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
        
        fovMesh->setVertexAtOffset(1, -xPos, yPos, zPos);
        fovMesh->setVertexAtOffset(2, xPos, yPos, zPos);
        fovMesh->setVertexAtOffset(3, xPos, -yPos, zPos);
        fovMesh->setVertexAtOffset(4, -xPos, -yPos, zPos);
    } else {
        Number fovRad = (90+camera->getFOV()/2.0) * TORADIANS;
        Number displayScale = 3.0;
        Number xPos = cos(fovRad) * displayScale;
        Number yPos = xPos * 0.5625;
        Number zPos = -sin(fovRad) * displayScale * 0.5;
        
        fovMesh->setVertexAtOffset(1, -xPos, yPos, zPos);
        fovMesh->setVertexAtOffset(2, xPos, yPos, zPos);
        fovMesh->setVertexAtOffset(3, xPos, -yPos, zPos);
        fovMesh->setVertexAtOffset(4, -xPos, -yPos, zPos);
    }
}

CameraPreviewWindow::CameraPreviewWindow() : UIElement() {
    
    bgRect = new UIRect((160 * 1.5)+16, (90 * 1.5) + 38);
    addChild(bgRect);
    bgRect->setColor(0.0, 0.0, 0.0, 0.5);
    
    UILabel *label = new UILabel("PREVIEW", 11);
    label->setColor(1.0, 1.0, 1.0, 1.0);
//    addChild(label);
    label->setPosition(15, 3);
  
    aspectCombo = new UIComboBox(globalMenu, 80);
    addChild(aspectCombo);
    aspectCombo->setPosition(5, 3);
    aspectCombo->addComboItem("16:9");
    aspectCombo->addComboItem("16:10");
    aspectCombo->addComboItem("4:3");
    aspectCombo->addComboItem("16:18");
    aspectCombo->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    pinButton = new UIButton("Pin", 60);
    addChild(pinButton);
    pinButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    previewRect = new UIRect(160 * 1.5, 90 * 1.5);
    previewRect->setPosition(8, 30);
    addChild(previewRect);
    enabled = false;
    camera = NULL;
    scene = NULL;
    renderTexture = NULL;
    
    setLocalBoundingBox(bgRect->getLocalBoundingBox());
    pinned = false;
    cameraSelected = false;
    
    aspectCombo->setSelectedIndex(0);
}

bool CameraPreviewWindow::isPinned() {
    return pinned;
}

void CameraPreviewWindow::Resize(Number width, Number height) {
    UIElement::Resize(width, height);
    bgRect->Resize(width, height);
    
    previewRect->Resize(width-16, height-38);
    
    if(camera) {
        if(renderTexture) {
            delete renderTexture;
        }
        renderTexture = new SceneRenderTexture(scene, camera, previewRect->getWidth(), previewRect->getHeight());
        previewRect->setTexture(renderTexture->getTargetTexture());
    }
    pinButton->setPosition(width-70, 3);
}

void CameraPreviewWindow::handleEvent(Event *event) {
    
    if(event->getDispatcher() == pinButton) {
        pinned = !pinned;
        if(pinned) {
            pinButton->setCaption("Unpin");
        } else {
            pinButton->setCaption("Pin");
            if(!cameraSelected) {
                enabled = false;
                camera = NULL;
            }
        }
    } else if(event->getDispatcher() == aspectCombo) {
        switch(aspectCombo->getSelectedIndex()) {
            case 0:
                Resize(bBox.y * 1.77777, bBox.y);
            break;
            case 1:
                Resize(bBox.y * 1.6, bBox.y);
            break;
            case 2:
                Resize(bBox.y * 1.3, bBox.y);
            break;
            case 3:
                Resize(bBox.y * 0.888, bBox.y);
            break;
                
        }
    }
}

CameraPreviewWindow::~CameraPreviewWindow() {
    delete renderTexture;
}

void CameraPreviewWindow::setCamera(Scene *scene, Camera *camera) {
    
    if(pinned && !camera) {
        cameraSelected = false;
        return;
    }
    
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
        if(!pinned) {
            enabled = false;
        }
    }
}

EntityEditorMainView::EntityEditorMainView(PolycodeEditor *editor) {
	processInputEvents = true;
    multiselectIndex = 0;
    objectRootInstance = NULL;
    lightsDisabled = false;
    beforeData = NULL;
    dummyTargetEntity = NULL;
    setOwnsChildrenRecursive(true);
    
    this->editor = editor;
	mainScene = new Scene(Scene::SCENE_3D, true);
    
//    mainScene->getDefaultCamera()->frustumCulling = false;
//    mainScene->doVisibilityChecking(false);
    
	renderTexture = new SceneRenderTexture(mainScene, mainScene->getDefaultCamera(), 512, 512);
	mainScene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);	
	mainScene->useClearColor = true;
	mainScene->rootEntity.processInputEvents = true;
    
    dummyEntity = new Entity();
    mainScene->addChild(dummyEntity);
	   
    Number customFalloff = 0.006;
    // setup custom lights for disabled lighting
    customLight1 = new SceneLight(SceneLight::POINT_LIGHT, mainScene,999999, customFalloff, customFalloff, customFalloff);
    customLight1->editorOnly = true;
    customLight1->setPosition(-9999, 9999, 9999);
    mainScene->addLight(customLight1);
    customLight1->enabled = false;

    customLight2 = new SceneLight(SceneLight::POINT_LIGHT, mainScene,999999, customFalloff, customFalloff, customFalloff);
    customLight2->editorOnly = true;
    customLight2->setPosition(8999, -8999, -8999);
    mainScene->addLight(customLight2);
    customLight2->enabled = false;
    
	renderTextureShape = new UIRect(256, 256);
	renderTextureShape->setAnchorPoint(-1.0, -1.0, 0.0);	
	renderTextureShape->setTexture(renderTexture->getTargetTexture());
	addChild(renderTextureShape);
	renderTextureShape->setPosition(0, 30);
    renderTextureShape->focusable = true;
    renderTextureShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

    
    cameraPreview = new CameraPreviewWindow();
    addChild(cameraPreview);
    cameraPreview->setPosition(5, 35);
    
    
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	footerBg = new UIRect(10,10);
	addChild(footerBg);
	footerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	footerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
    
	bottomBar = new Entity();
	addChild(bottomBar);
	bottomBar->setPosition(0, 0);
	bottomBar->processInputEvents = true;
	
	topBar = new Entity();
	addChild(topBar);
	topBar->setPosition(0, 0);
	topBar->processInputEvents = true;
    
	
	mainScene->getDefaultCamera()->setPosition(10, 10, 10);
	mainScene->getDefaultCamera( )->lookAt(Vector3());
	mainScene->getDefaultCamera()->setClippingPlanes(0.01, 1000);
    
	grid = new EditorGrid();
    grid->addEventListener(this, Event::CHANGE_EVENT);
	mainScene->addChild(grid);
	
    objectRootBase = new Entity();
    mainScene->addChild(objectRootBase);
    objectRootBase->processInputEvents = true;
    
    sceneObjectRoot = new Entity();
    sceneObjectRoot->processInputEvents = true;
    objectRootBase->addChild(sceneObjectRoot);
    
    iconBase = new Entity();
    mainScene->addChild(iconBase);
    iconBase->processInputEvents = true;
    
	transformGizmo = new TransformGizmo(mainScene, mainScene->getDefaultCamera());
    transformGizmo->enableGizmo = false;
    transformGizmo->addEventListener(this, Event::CHANGE_EVENT);
    transformGizmo->addEventListener(this, Event::SELECT_EVENT);
    
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
    

    viewModeSelector = new UIIconSelector();
    viewModeSelector->addIcon("entityEditor/icon_cam_2d.png");
    viewModeSelector->addIcon("entityEditor/icon_cam_x.png");
    viewModeSelector->addIcon("entityEditor/icon_cam_y.png");
    viewModeSelector->addIcon("entityEditor/icon_cam_z.png");
    viewModeSelector->addIcon("entityEditor/icon_cam_3d.png");
    topBar->addChild(viewModeSelector);
    viewModeSelector->selectIndex(EDITOR_MODE_3D);
    viewModeSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    shadeModeSelector = new UIIconSelector();
    shadeModeSelector->addIcon("entityEditor/shade_full.png");
    shadeModeSelector->addIcon("entityEditor/shade_solid.png");
    shadeModeSelector->addIcon("entityEditor/shade_wire.png");
    topBar->addChild(shadeModeSelector);
    shadeModeSelector->setPosition(320, 3);
    shadeModeSelector->addEventListener(this, UIEvent::SELECT_EVENT);

    lightingModeSelector = new UIIconSelector();
    lightingModeSelector->addIcon("entityEditor/lights_icon.png");
    lightingModeSelector->addIcon("entityEditor/nolights_icon.png");
    topBar->addChild(lightingModeSelector);
    lightingModeSelector->setPosition(420, 3);
    lightingModeSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    
    moveUpButton = new UIImageButton("entityEditor/button_move_up.png", 1.0, 24, 24);
	bottomBar->addChild(moveUpButton);
    moveUpButton->setPosition(4, 2);
    moveUpButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    moveTopButton = new UIImageButton("entityEditor/button_move_top.png", 1.0, 24, 24);
	bottomBar->addChild(moveTopButton);
    moveTopButton->setPosition(30, 2);
    moveTopButton->addEventListener(this, UIEvent::CLICK_EVENT);

    moveDownButton = new UIImageButton("entityEditor/button_move_down.png", 1.0, 24, 24);
	bottomBar->addChild(moveDownButton);
    moveDownButton->setPosition(56, 2);
    moveDownButton->addEventListener(this, UIEvent::CLICK_EVENT);

    moveBottomButton = new UIImageButton("entityEditor/button_move_bottom.png", 1.0, 24, 24);
	bottomBar->addChild(moveBottomButton);
    moveBottomButton->setPosition(82, 2);
    moveBottomButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    gridSettingsButton = new UIImageButton("entityEditor/grid_button.png", 1.0, 24, 24);
	bottomBar->addChild(gridSettingsButton);
    gridSettingsButton->setPosition(120, 2);
    gridSettingsButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    snapSelector = new UIIconSelector();
    snapSelector->addIcon("entityEditor/snap_off.png");
    snapSelector->addIcon("entityEditor/snap_on.png");
    bottomBar->addChild(snapSelector);
    snapSelector->setPosition(156, 2);
    snapSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    iconVisibilitySelector = new UIIconSelector();
    iconVisibilitySelector->addIcon("entityEditor/show_icons.png");
    iconVisibilitySelector->addIcon("entityEditor/hide_icons.png");
    bottomBar->addChild(iconVisibilitySelector);
    iconVisibilitySelector->setPosition(230, 2);
    iconVisibilitySelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    bBoxVis = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0, 1.0, 1.0);
    bBoxVis->overlayWireframe = true;
    bBoxVis->wireFrameColor = Color(0.3, 0.5, 1.0, 0.5);
    bBoxVis->color.a = 0.0;
    bBoxVis->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    mainScene->addChild(bBoxVis);
    
    editorMode = EDITOR_MODE_3D;
    
    input = CoreServices::getInstance()->getCore()->getInput();
    input->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    
    gridSettings = new EditorGridSettingsWindow(grid);
    addChild(gridSettings);
    gridSettings->setPosition(30,40);
}

std::vector<Entity*> EntityEditorMainView::getSelectedEntities() {
    return selectedEntities;
}

void EntityEditorMainView::doAction(String actionName, PolycodeEditorActionData *data) {
    PolycodeSceneEditorActionData *sceneData = (PolycodeSceneEditorActionData*)data;
    
    if(!sceneData) {
        return;
    }
    
	if(actionName == "move") {
		for(int i=0; i < selectedEntities.size(); i++) {
            if(i < sceneData->entries.size()) {
			selectedEntities[i]->setPosition(sceneData->entries[i].vec3);
            }
		}
        transformGizmo->setTransformSelection(selectedEntities);
        setBBox();
	} else if(actionName == "scale") {
		for(int i=0; i < selectedEntities.size(); i++) {
            if(i < sceneData->entries.size()) {
                selectedEntities[i]->setScale(sceneData->entries[i].vec3);
                selectedEntities[i]->setPosition(sceneData->entries[i].vec3Secondary);
            }
		}
    } else if(actionName == "rotate") {
		for(int i=0; i < selectedEntities.size(); i++) {
            if(i < sceneData->entries.size()) {
                selectedEntities[i]->setRotationByQuaternion(sceneData->entries[i].quat);
                selectedEntities[i]->setPosition(sceneData->entries[i].vec3);
            }
		}
    } else if(actionName == "select") {
        selectNone(false);
        if(sceneData) {
            for(int i=0; i < sceneData->entries.size(); i++) {
                    selectEntity(sceneData->entries[i].entity, true, false);
            }
        }
    } else if(actionName == "delete") {
        if(sceneData->reverse) {
            selectNone(false);
            for(int i=0; i < sceneData->entries.size(); i++) {
                sceneData->entries[i].parentEntity->addChild(sceneData->entries[i].entity);
                
                SceneLight *sceneLight = dynamic_cast<SceneLight*>(sceneData->entries[i].entity);
                if(sceneLight) {
                    mainScene->addLight(sceneLight);
                }
                
                setEditorPropsRecursive(sceneData->entries[i].entity);
                selectEntity(sceneData->entries[i].entity, true, false);
            }
            sceneData->deleteEntitiesInDestructor = false;
		} else {
            deleteSelected(false);
            sceneData->deleteEntitiesInDestructor = true;
		}
    } else if(actionName == "create_entity") {
        if(sceneData->reverse) {
			deleteSelected(false);
            selectNone(false);
            for(int i=0; i < sceneData->entries.size(); i++) {
                selectEntity(sceneData->entries[i].entity, true, false);
            }
            
		} else {
            selectNone(false);
            sceneData->entries[0].parentEntity->addChild(sceneData->entries[0].entity);
            
            SceneLight *sceneLight = dynamic_cast<SceneLight*>(sceneData->entries[0].entity);
            if(sceneLight) {
                mainScene->addLight(sceneLight);
            }
            
            
            setEditorPropsRecursive(sceneData->entries[0].entity);
            selectEntity(sceneData->entries[0].entity, true, false);
		}
    }
}

SceneRenderTexture *EntityEditorMainView::getRenderTexture() {
    return renderTexture;
}

void EntityEditorMainView::setEditorMode(int newMode) {
    editorMode = newMode;
    
    if(newMode != EDITOR_MODE_3D) {
        trackballCamera->setOrbitingCenter(Vector3(0.0, 0.0, 0.0));        
    }
    
    switch(editorMode) {
        case EDITOR_MODE_3D:
            mainScene->setSceneType(Scene::SCENE_3D);
            grid->setGridMode(EditorGrid::GRID_MODE_3D);
            transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_3D);
            mainScene->getDefaultCamera()->setOrthoMode(false);
            mainScene->getDefaultCamera()->setClippingPlanes(0.1, 1000);
            trackballCamera->disableRotation(false);
        break;
        case EDITOR_MODE_3D_X:
            
            mainScene->setSceneType(Scene::SCENE_2D);
            mainScene->getDefaultCamera()->setOrthoMode(true);
            mainScene->getDefaultCamera()->setClippingPlanes(-0.1, 1000);
            trackballCamera->setCameraPosition(trackballCamera->getOribitingCenter()+Vector3(trackballCamera->getCameraDistance(), 0.0, 0.0));
            grid->setGridMode(EditorGrid::GRID_MODE_2D_X);
            transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_2D_X);
            trackballCamera->disableRotation(true);
            Update();
        break;
        case EDITOR_MODE_3D_Y:
            
            mainScene->setSceneType(Scene::SCENE_2D);
            mainScene->getDefaultCamera()->setOrthoMode(true);
            mainScene->getDefaultCamera()->setClippingPlanes(-0.1, 1000);
            trackballCamera->setCameraPosition(trackballCamera->getOribitingCenter()+Vector3(0.001, trackballCamera->getCameraDistance(), 0.00));
            grid->setGridMode(EditorGrid::GRID_MODE_2D_Y);
            transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_2D_Y);
            trackballCamera->disableRotation(true);
            Update();
        break;
        case EDITOR_MODE_3D_Z:
        case EDITOR_MODE_2D:
            mainScene->setSceneType(Scene::SCENE_2D);
            mainScene->getDefaultCamera()->setOrthoMode(true);
            mainScene->getDefaultCamera()->setClippingPlanes(-0.1, 1000);
            trackballCamera->setCameraPosition(trackballCamera->getOribitingCenter()+Vector3(0.0, 0.0, trackballCamera->getCameraDistance()));
            grid->setGridMode(EditorGrid::GRID_MODE_2D_Z);
            transformGizmo->setGizmoMode(TransformGizmo::GIZMO_MODE_2D_Z);
            trackballCamera->disableRotation(true);
            Update();
        break;
    }

}

Entity *EntityEditorMainView::getSelectedEntity() {
    if(selectedEntities.size() > 0) {
        
        if(selectedEntities[selectedEntities.size()-1] == dummyEntity) {
            return dummyTargetEntity->getPropertyEntity();
        } else {
            return selectedEntities[selectedEntities.size()-1];
        }
    } else {
        return NULL;
    }
}


void EntityEditorMainView::Paste(EntityEditorClipboardData *data) {
    
    if(!hasFocus) {
        return;
    }
    
    
    selectNone(false);
    
    for(int i=0; i < data->entities.size(); i++) {
        Entity *entity = data->entities[i]->Clone(true, true);
        setEditorPropsRecursive(entity);
        sceneObjectRoot->addChild(entity);
        selectEntity(entity, true);
    }
}

bool EntityEditorMainView::selectingNewEntities(){
    
    if(entitiesToSelect.size() != lastEntitiesToSelect.size()) {
        return true;
    }

    for(int i=0; i < entitiesToSelect.size(); i++) {
        if(entitiesToSelect[i].entity == dummyEntity) {
            if(dummyTargetEntity) {
                if(dummyTargetEntity->getSelectedPoint() != lastSelectedDummyPoint) {
                    return true;
                }
            }
        }
    }
    
    for(int i=0; i < entitiesToSelect.size(); i++) {
        if(lastEntitiesToSelect[i].entity != entitiesToSelect[i].entity) {
            return true;
        }
    }
    return false;
}

bool EntityDistanceSorter::operator() (MultiselectorEntry i,MultiselectorEntry j) {
	if(i.distance < j.distance) {
        return true;
    } else {
        return false;
    }
}

void EntityEditorMainView::Update() {
    
    // update dummy target if trasnforming dummy entity
    
    if(dummyTargetEntity) {
        dummyTargetEntity->setDummyTransform(dummyEntity);
    }
    
    if(entitiesToSelect.size() != 0) {
        
        sort (entitiesToSelect.begin(), entitiesToSelect.end(), distanceSorter);
        
        if(multiselectIndex > entitiesToSelect.size()-1 || selectingNewEntities()) {
            multiselectIndex = 0;
        }
        
        // force dummy to always select
        for(int i=0; i < entitiesToSelect.size(); i++) {
            if(entitiesToSelect[i].entity == dummyEntity) {
                multiselectIndex = i;
            }
        }
        
        selectEntity(entitiesToSelect[multiselectIndex].entity, input->getKeyState(KEY_LSHIFT) || input->getKeyState(KEY_RSHIFT));
        multiselectIndex++;
        lastEntitiesToSelect = entitiesToSelect;
        if(dummyTargetEntity) {
            lastSelectedDummyPoint = dummyTargetEntity->getSelectedPoint();
        }
        entitiesToSelect.clear();
    }
    
    if(editorMode != EDITOR_MODE_3D) {
        Number aspect = renderTextureShape->getWidth() / renderTextureShape->getHeight();
        mainScene->getDefaultCamera()->setOrthoSize(trackballCamera->getCameraDistance() * aspect, trackballCamera->getCameraDistance());
    }
    
    
    for(int i=0; i < icons.size(); i++) {
        Number scale;
        
        
        Entity *parentEntity = (Entity*) icons[i]->getUserData();
        
        if(!parentEntity->visible) {
            icons[i]->visible = false;
        } else {
            icons[i]->visible = true;
            Vector3 parentPosition = parentEntity->getConcatenatedMatrix().getPosition();
            icons[i]->setPosition(parentPosition);
            
            if(editorMode != EDITOR_MODE_3D) {
                scale = trackballCamera->getCameraDistance() * 0.1;
            } else {
                scale = mainScene->getDefaultCamera()->getPosition().distance(icons[i]->getConcatenatedMatrix().getPosition()) * 0.1;
            }
            icons[i]->setScale(scale, scale, scale);
            icons[i]->rebuildTransformMatrix();
            icons[i]->recalculateAABBAllChildren();
        }
    }
    
    if(selectedEntities.size() > 0) {
        setBBox();
        bBoxVis->wireFrameColor = Color(0.3, 0.5, 1.0, 0.5);
    } else {
        setBBox(getObjectRoot());
        bBoxVis->wireFrameColor = Color(0.5, 1.0, 0.3, 0.5);
    }
}

void EntityEditorMainView::createIcon(Entity *entity, String iconFile) {
    
    entity->removeAllHandlersForListener(this);
    
    ScenePrimitive *iconPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.3, 0.3);
    
    iconPrimitive->setMaterialByName("Unlit");
	Texture *tex = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile("entityEditor/"+iconFile);
	if(iconPrimitive->getLocalShaderOptions()) {
        iconPrimitive->getLocalShaderOptions()->addTexture("diffuse", tex);
	}
    
    iconBase->addChild(iconPrimitive);
    iconPrimitive->billboardMode = true;
    iconPrimitive->setUserData((void*)entity);
    iconPrimitive->forceMaterial = true;
    iconPrimitive->processInputEvents = true;
    iconPrimitive->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    iconPrimitive->ignoreParentMatrix = true;
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
        if(!entity->getChildAtIndex(i)->editorOnly) {
            setEditorProps(entity->getChildAtIndex(i));
        }
    }
}

void EntityEditorMainView::setLinkedEntityPropsRecursive(SceneEntityInstance *parentInstance, Entity *entity) {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(entity);
    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(entity);
    
    entity->setUserData((void*)parentInstance);
    entity->processInputEvents = true;
    entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    entity->editorOnly = true;
    
    if(sceneMesh && !emitter) {
        sceneMesh->wireFrameColor = Color(0.2, 0.9, 0.6, 1.0);
        sceneMesh->useGeometryHitDetection = true;
    }
 
    for(int i=0; i < entity->getNumChildren(); i++) {
        setLinkedEntityPropsRecursive(parentInstance, entity->getChildAtIndex(i));
    }

}

void EntityEditorMainView::setEditorProps(Entity *entity) {
    entity->processInputEvents = true;
    entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(entity);
    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(entity);
    SceneSprite *sprite = dynamic_cast<SceneSprite*>(entity);
    
    if(sceneMesh && !emitter && !sprite) {
        sceneMesh->wireFrameColor = Color(1.0, 0.8, 0.3, 1.0);
//        sceneMesh->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
        sceneMesh->useGeometryHitDetection = true;
    }
    
    SceneEntityInstance *instance = dynamic_cast<SceneEntityInstance*>(entity);
    if(instance && instance != objectRootInstance) {
        for(int i=0; i < instance->getNumChildren(); i++) {
            setLinkedEntityPropsRecursive(instance, instance->getChildAtIndex(i));
            instance->getResourceEntry()->reloadOnFileModify = true;
            instance->getResourceEntry()->addEventListenerUnique(this, Event::RESOURCE_RELOAD_EVENT);
            if(!CoreServices::getInstance()->getResourceManager()->getGlobalPool()->hasResource(instance->getResourceEntry())) {
                CoreServices::getInstance()->getResourceManager()->getGlobalPool()->addResource(instance->getResourceEntry());
            }
        }
    }
    
    SceneLight *sceneLight = dynamic_cast<SceneLight*>(entity);
    if(sceneLight) {
        createIcon(entity, "light_icon.png");
        LightDisplay *lightVis = new LightDisplay(sceneLight);
        if(!sceneLight->getParentScene()) {
            sceneLight->setParentScene(mainScene);
            mainScene->addLight(sceneLight);
        }
    }
    
    SceneCurve *sceneCurve = dynamic_cast<SceneCurve*>(entity);
    if(sceneCurve) {
        CurveDisplay *curveVis = new CurveDisplay(mainScene, sceneCurve);
        curveVis->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        createIcon(entity, "curve_icon.png");
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
        newPrimitive->setMaterialByName("Default");
        didPlaceEntity(newPrimitive);
        selectEntity(newPrimitive, false, false);
        return;
    }

    if(command == "add_empty") {
        Entity *newEntity = new Entity();
        sceneObjectRoot->addChild(newEntity);
        setEditorProps(newEntity);
        newEntity->setPosition(cursorPosition);
        didPlaceEntity(newEntity);
        selectEntity(newEntity, false, false);
        return;
    }
    
    if(command == "add_curve") {
        SceneCurve *curve = new SceneCurve();
        
        curve->getCurve()->addControlPoint(3.0, -1.0, 0.0,
                                           2.0, 0.0, 0.0,
                                           1.0, 1.0, 0.0);
        curve->getCurve()->addControlPoint(
                                           -1.0, 1.0, 0.0,
                                           -2.0, 0.0, 0.0,
                                           -3.0, -1.0, 0.0);
        
        sceneObjectRoot->addChild(curve);
        setEditorProps(curve);
        curve->setPosition(cursorPosition);
        didPlaceEntity(curve);
        selectEntity(curve, false, false);
        return;
    }

    if(command == "add_sound") {
        SceneSound *newSound = new SceneSound("default.wav", 1.0, 2.0);
        sceneObjectRoot->addChild(newSound);
        setEditorProps(newSound);
        newSound->setPosition(cursorPosition);
        didPlaceEntity(newSound);
        selectEntity(newSound, false, false);
        return;
    }

    if(command == "add_camera") {
        Camera *newCamera = new Camera(mainScene);
        sceneObjectRoot->addChild(newCamera);
        setEditorProps(newCamera);
        newCamera->setPosition(cursorPosition);
        didPlaceEntity(newCamera);
        selectEntity(newCamera, false, false);
        return;
    }
    
    if(command == "add_image") {
        assetSelectType = "image";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("png");
        extensions.push_back("hdr");
        extensions.push_back("jpg");
        extensions.push_back("psd");
        extensions.push_back("tga");
        globalFrame->showAssetBrowser(extensions);
        return;
    }

    if(command == "add_sprite") {
        assetSelectType = "sprite";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		std::vector<ResourcePool*> pools;
        pools.push_back(CoreServices::getInstance()->getResourceManager()->getGlobalPool());
        for(int i=0; i < objectRootInstance->getNumLinkedResourePools(); i++) {
            pools.push_back(objectRootInstance->getLinkedResourcePoolAtIndex(i));
        }
		globalFrame->showAssetBrowserForPools(pools, Resource::RESOURCE_SPRITE);
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
        didPlaceEntity(newLabel);
        selectEntity(newLabel, false, false);
        return;
    }
    
    if(command == "add_light") {
        SceneLight *newLight = new SceneLight(SceneLight::POINT_LIGHT, mainScene, 1.0);
        sceneObjectRoot->addChild(newLight);
        mainScene->addLight(newLight);
        newLight->enabled = !lightsDisabled;        
        setEditorProps(newLight);
        newLight->setLocalBoundingBox(Vector3());
        newLight->setPosition(cursorPosition);
        didPlaceEntity(newLight);
        selectEntity(newLight, false, false);
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
    
    if(command == "add_entity") {
        assetSelectType = "entity";
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("entity");
        globalFrame->showAssetBrowser(extensions);
        return;
    }
    
    if(command == "add_particles") {
        SceneParticleEmitter  *newEmitter = new SceneParticleEmitter(30, 3.0, 0.2);
        newEmitter->setLocalBoundingBox(0.5, 0.5, 0.5);
        
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
        
        selectEntity(newEmitter, false, false);
        didPlaceEntity(newEmitter);
        return;
    }
}

void EntityEditorMainView::didPlaceEntity(Entity *entity) {
    PolycodeSceneEditorActionData *beforeData = new PolycodeSceneEditorActionData();
    PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
    data->reverse = false;
    
    for(int i=0; i < selectedEntities.size(); i++) {
        beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]));
    }
    
    PolycodeSceneEditorActionDataEntry entry(entity);
    entry.parentEntity = sceneObjectRoot;
    data->entries.push_back(entry);
    
    editor->didAction("create_entity", beforeData, data);
}

void EntityEditorMainView::deleteSelected(bool doAction) {

    for(int i=0; i < selectedEntities.size(); i++) {
        if(selectedEntities[i] == dummyEntity) {
            if(dummyTargetEntity) {
                dummyTargetEntity->handleDelete();
                dummyEntity->removeAllHandlers();
                selectedEntities.clear();
                transformGizmo->setTransformSelection(selectedEntities);
                return;
            }
        }
    }
    
    if(doAction) {
        PolycodeSceneEditorActionData *oldData = new PolycodeSceneEditorActionData();
        PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
        data->reverse = false;
        oldData->deleteEntitiesInDestructor = true;
        
        for(int i=0; i < selectedEntities.size(); i++) {
            PolycodeSceneEditorActionDataEntry entry(selectedEntities[i]);
            entry.parentEntity = selectedEntities[i]->getParentEntity();
            oldData->entries.push_back(entry);
        }

        editor->didAction("delete", oldData, data);
    }
    for(int i=0; i < selectedEntities.size(); i++) {
        selectedEntities[i]->getParentEntity()->removeChild(selectedEntities[i]);
        SceneLight *sceneLight = dynamic_cast<SceneLight*>(selectedEntities[i]);
        if(sceneLight) {
            mainScene->removeLight(sceneLight);
        }
    }
    
    for(int i=0; i < selectedEntities.size(); i++) {
        selectedEntities[i]->setOwnsChildrenRecursive(true);
        for(int j=0; j < icons.size(); j++) {
            if(icons[j]->getUserData() == selectedEntities[i]) {
                icons[j]->getParentEntity()->removeChild(icons[j]);
				delete icons[j];
                icons.erase(icons.begin()+j);
                break;
            }
        }
        selectedEntities[i]->removeAllHandlers();
    }
    
    selectedEntities.clear();
    transformGizmo->setTransformSelection(selectedEntities);
    setBBox();
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void EntityEditorMainView::onGainFocus() {
    transformGizmo->enableGizmo = true;
}

void EntityEditorMainView::onLoseFocus() {
    transformGizmo->enableGizmo = false;
}

void EntityEditorMainView::handleEvent(Event *event) {
    
    
    if(event->getDispatcher() == transformGizmo) {
        if(event->getEventCode() == Event::CHANGE_EVENT) {
            TrasnformGizmoEvent *trasnformEvent = (TrasnformGizmoEvent*) event;
            switch(trasnformEvent->mode) {
                case TransformGizmo::TRANSFORM_MOVE:
                case TransformGizmo::TRANSFORM_MOVE_VIEW:
                {
                    PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        data->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getPosition()));
                    }
                    editor->didAction("move", beforeData, data);
                    beforeData = NULL;
                }
                break;
                case TransformGizmo::TRANSFORM_SCALE:
                case TransformGizmo::TRANSFORM_SCALE_VIEW:
                {
                    PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        data->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getScale(), selectedEntities[i]->getPosition()));
                    }
                    editor->didAction("scale", beforeData, data);
                    beforeData = NULL;
                }
                break;
                case TransformGizmo::TRANSFORM_ROTATE:
                case TransformGizmo::TRANSFORM_ROTATE_VIEW:
                {
                    PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        data->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getRotationQuat(), selectedEntities[i]->getPosition()));
                    }
                    editor->didAction("rotate", beforeData, data);
                    beforeData = NULL;                    
                }
                break;
            }
        } else if(event->getEventCode() == Event::SELECT_EVENT) {
            TrasnformGizmoEvent *trasnformEvent = (TrasnformGizmoEvent*) event;
            switch(trasnformEvent->mode) {
                case TransformGizmo::TRANSFORM_MOVE:
                case TransformGizmo::TRANSFORM_MOVE_VIEW:
                {
                    beforeData = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getPosition()));
                    }
                }
                break;
                case TransformGizmo::TRANSFORM_SCALE:
                case TransformGizmo::TRANSFORM_SCALE_VIEW:
                {
                    beforeData = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getScale(), selectedEntities[i]->getPosition()));
                    }
                }
                break;
                case TransformGizmo::TRANSFORM_ROTATE:
                case TransformGizmo::TRANSFORM_ROTATE_VIEW:
                {
                    beforeData = new PolycodeSceneEditorActionData();
                    for(int i=0; i < selectedEntities.size(); i++) {
                        beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]->getRotationQuat(), selectedEntities[i]->getPosition()));
                    }
                }
                break;
            }
        }
        
	} else if(event->getEventCode() == Event::RESOURCE_RELOAD_EVENT) {
        SceneEntityInstanceResourceEntry *entry = dynamic_cast<SceneEntityInstanceResourceEntry*>(event->getDispatcher());
        if(entry) {
                setEditorProps(entry->getInstance());
        }
	} else if(event->getDispatcher() == renderTextureShape) {
        focusSelf();
    } else if(event->getDispatcher() == trackballCamera) {
        Update();
        transformGizmo->Update();
    } else if(event->getDispatcher() == viewModeSelector) {
        setEditorMode(viewModeSelector->getSelectedIndex());
    } else if(event->getDispatcher() == globalFrame->assetBrowser) {
        if(event->getEventCode() == UIEvent::OK_EVENT) {
            if(assetSelectType == "mesh") {
                SceneMesh *newMesh = new SceneMesh(globalFrame->assetBrowser->getSelectedAssetPath());
                newMesh->cacheToVertexBuffer(true);
                sceneObjectRoot->addChild(newMesh);
                setEditorProps(newMesh);
                newMesh->setMaterialByName("Default");
                newMesh->setPosition(cursorPosition);
                didPlaceEntity(newMesh);
                selectEntity(newMesh, false, false);
            } else if(assetSelectType == "image") {
                SceneImage *newImage = new SceneImage(globalFrame->assetBrowser->getSelectedAssetPath());
                newImage->setMaterialByName("Unlit");
                if(newImage->getLocalShaderOptions()) {
                    newImage->getLocalShaderOptions()->addTexture("diffuse", newImage->getTexture());
                }
                sceneObjectRoot->addChild(newImage);
                setEditorProps(newImage);
                newImage->setPosition(cursorPosition);
                didPlaceEntity(newImage);
                selectEntity(newImage, false, false);
            } else if(assetSelectType == "sprite") {
                
                Resource *selectedResource = globalFrame->assetBrowser->getSelectedResource();
                
                if(selectedResource) {
                    Sprite *sprite = (Sprite*) selectedResource;
                    
                    SceneSprite *newSprite = new SceneSprite(sprite->getParentSpriteSet());
                    newSprite->setSprite(sprite);
                    if(sprite->getNumStates() > 0) {
                        newSprite->setSpriteState(sprite->getState(0), 0, false);
                    }
                    
                    newSprite->setMaterialByName("Unlit");
                    if(newSprite->getLocalShaderOptions()) {
                        newSprite->getLocalShaderOptions()->addTexture("diffuse", newSprite->getTexture());
                    }
                    sceneObjectRoot->addChild(newSprite);
                    setEditorProps(newSprite);
                    newSprite->setPosition(cursorPosition);
                    didPlaceEntity(newSprite);
                    selectEntity(newSprite, false, false);
                }
            } else if(assetSelectType == "entity") {
                SceneEntityInstance *newEntity = new SceneEntityInstance(mainScene, globalFrame->assetBrowser->getSelectedAssetPath());
                sceneObjectRoot->addChild(newEntity);
                setEditorProps(newEntity);
                newEntity->setPosition(cursorPosition);
                didPlaceEntity(newEntity);
                selectEntity(newEntity, false, false);
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
        addEntityMenu->addOption("Add Curve", "add_curve");
        addEntityMenu->fitToScreenVertical();
        addEntityMenu->addEventListener(this, UIEvent::OK_EVENT);
    } else if(event->getDispatcher() == input) {
        InputEvent *inputEvent = (InputEvent*) event;
        if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
            switch(inputEvent->key) {
                case KEY_BACKSPACE:
                case KEY_DELETE:
                    if(hasFocus) {
                        deleteSelected(true);
                    }
                break;
                case KEY_ESCAPE:
                {
                    selectNone(true);
                }
                break;
            }
        }
    } else if(event->getDispatcher() == lightingModeSelector) {
        switch(lightingModeSelector->getSelectedIndex()) {
            case 0:
                disableLighting(false);
            break;
            case 1:
                disableLighting(true);
            break;
        }
    } else if(event->getDispatcher() == shadeModeSelector) {
        switch(shadeModeSelector->getSelectedIndex()) {
            case 0:
                mainScene->setOverrideMaterial(NULL);
            break;
            case 1:
                mainScene->setOverrideMaterial((Material*)CoreServices::getInstance()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, "Default"));
            break;
            case 2:
                mainScene->setOverrideMaterial((Material*)CoreServices::getInstance()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, "UnlitWireframe"));
            break;
        }
    } else if(event->getDispatcher() == moveUpButton) {
        moveSelectedUp();
    } else if(event->getDispatcher() == moveTopButton) {
        moveSelectedTop();
    } else if(event->getDispatcher() == moveDownButton) {
        moveSelectedDown();
    } else if(event->getDispatcher() == moveBottomButton) {
        moveSelectedBottom();
    } else if(event->getDispatcher() == gridSettingsButton) {
        gridSettings->visible = !gridSettings->visible;
        gridSettings->enabled = !gridSettings->enabled;
    } else if(event->getDispatcher() == snapSelector) {
        switch(snapSelector->getSelectedIndex()) {
            case 0:
                transformGizmo->enableSnap(false);
            break;
            case 1:
                transformGizmo->enableSnap(true);
                transformGizmo->setSnapSize(grid->getGridSize());
            break;
        }
    } else if(event->getDispatcher() == grid) {
                transformGizmo->setSnapSize(grid->getGridSize());
    } else if(event->getDispatcher() == iconVisibilitySelector) {
        switch(iconVisibilitySelector->getSelectedIndex()) {
            case 0:
                iconBase->visible = true;
            break;
            case 1:
                iconBase->visible = false;
            break;
        }
    } else {
        if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN && hasFocus && event->getDispatcher() != renderTextureShape) {
            InputEvent *inputEvent = (InputEvent*) event;

    
            Entity* targetEntity = (Entity*) event->getDispatcher();
            
            
            if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2 && targetEntity->visible && targetEntity != getObjectRoot()) {

                
                // if it's an icon, select the entity linked to the icon
                for(int i=0; i < icons.size(); i++) {
                    if(icons[i] == targetEntity) {
                        targetEntity = (Entity*)targetEntity->getUserData();
                    }
                }
                
                // check if dispatcher is a dummy target
                DummyTargetEntity *dummyTarget = dynamic_cast<DummyTargetEntity*>(event->getDispatcher());
                if(dummyTarget) {
                    targetEntity = dummyEntity;
                    if(dummyTargetEntity) {
                        dummyTargetEntity->handleDeselect();
                    }
                    dummyTargetEntity = dummyTarget;
                    dummyEntity->setPosition(dummyTarget->getSelectedPoint());
                }
                
                
                MultiselectorEntry entry;
                entry.entity = targetEntity;
                entry.distance = inputEvent->hitDistance;

                entitiesToSelect.push_back(entry);
            }
        }
    }
}

void EntityEditorMainView::moveSelectedUp() {
    for(int i=0; i < selectedEntities.size(); i++) {
        Entity *parent = selectedEntities[i]->getParentEntity();
        if(parent) {
            parent->moveChildUp(selectedEntities[i]);
        }
    }
}

void EntityEditorMainView::moveSelectedDown() {
    for(int i=0; i < selectedEntities.size(); i++) {
        Entity *parent = selectedEntities[i]->getParentEntity();
        if(parent) {
            parent->moveChildDown(selectedEntities[i]);
        }
    }
}

void EntityEditorMainView::moveSelectedTop() {
    for(int i=0; i < selectedEntities.size(); i++) {
        Entity *parent = selectedEntities[i]->getParentEntity();
        if(parent) {
            parent->moveChildTop(selectedEntities[i]);
        }
    }
}

void EntityEditorMainView::moveSelectedBottom() {
    for(int i=0; i < selectedEntities.size(); i++) {
        Entity *parent = selectedEntities[i]->getParentEntity();
        if(parent) {
            parent->moveChildBottom(selectedEntities[i]);
        }
    }
}

void EntityEditorMainView::selectAll(bool doAction) {

    if(doAction) {
        beforeData = new PolycodeSceneEditorActionData();
        for(int i=0; i < selectedEntities.size(); i++) {
            beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]));
        }
        
        editor->didAction("select", beforeData, NULL, false);
        beforeData = NULL;
    }

    selectedEntities.clear();
    for(int i=0; i < objectRootInstance->getNumChildren(); i++) {
        Entity *child = objectRootInstance->getChildAtIndex(i);
        if(!child->editorOnly) {
            selectEntity(child, true, false);
        }
    }
    transformGizmo->setTransformSelection(selectedEntities);
    setBBox();
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void EntityEditorMainView::selectNone(bool doAction) {
    
    
    if(doAction) {
        
        beforeData = new PolycodeSceneEditorActionData();
        for(int i=0; i < selectedEntities.size(); i++) {
            beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]));
        }
        
        editor->didAction("select", beforeData, NULL, false);
        beforeData = NULL;
    }
    
    for(int i=0; i < selectedEntities.size(); i++) {
        doEntityDeselect(selectedEntities[i]);
    }
    cameraPreview->setCamera(mainScene, NULL);
    selectedEntities.clear();
    transformGizmo->setTransformSelection(selectedEntities);
    setBBox();
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void EntityEditorMainView::disableLighting(bool disable) {
    
    lightsDisabled = disable;
    
    for(int i=0; i < mainScene->getNumLights(); i++) {
        SceneLight *light = mainScene->getLight(i);
        light->enabled = !disable;
    }
    
    if(disable) {
        customLight1->enabled = true;
        customLight2->enabled = true;
    } else {
        customLight1->enabled = false;
        customLight2->enabled = false;
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
    
    if(targetEntity == dummyEntity) {
        if(dummyTargetEntity) {
            dummyTargetEntity->handleDeselect();
        }
    }
    
    std::vector<Entity*> dummySelectChildren = targetEntity->getEntitiesByTag("dummy_target", true);
    for(int i=0; i < dummySelectChildren.size(); i++) {
        DummyTargetEntity *dummy = dynamic_cast<DummyTargetEntity*>(dummySelectChildren[i]);
        if(dummy) {
            dummy->handleDeselect();
        }
    }
    
    SceneEntityInstance *instance = dynamic_cast<SceneEntityInstance*>(targetEntity);
    if(instance) {
        setOverlayWireframeRecursive(targetEntity, false);
    }
    
}

void EntityEditorMainView::setOverlayWireframeRecursive(Entity *targetEntity, bool val) {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    if(sceneMesh) {
        sceneMesh->overlayWireframe = val;
    }
    for(int i=0; i < targetEntity->getNumChildren(); i++) {
        setOverlayWireframeRecursive(targetEntity->getChildAtIndex(i), val);
    }
}

void EntityEditorMainView::doEntitySelect(Entity *targetEntity) {
    SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
    SceneParticleEmitter *emitter = dynamic_cast<SceneParticleEmitter*>(targetEntity);
    
    if(sceneMesh && ! emitter) {
        sceneMesh->overlayWireframe = true;
    }
    
    if(targetEntity == dummyEntity) {
        if(dummyTargetEntity) {
            dummyTargetEntity->handleSelect();
        }
    } else {
        // clear the dummy target if dummy is not selected
        dummyTargetEntity = NULL;
    }
    
    std::vector<Entity*> dummySelectChildren = targetEntity->getEntitiesByTag("dummy_target", true);
    for(int i=0; i < dummySelectChildren.size(); i++) {
        DummyTargetEntity *dummy = dynamic_cast<DummyTargetEntity*>(dummySelectChildren[i]);
        if(dummy) {
            dummy->handleSelect();
        }
    }
    
    
    SceneEntityInstance *instance = dynamic_cast<SceneEntityInstance*>(targetEntity);
    if(instance) {
        setOverlayWireframeRecursive(targetEntity, true);
    }
    
    Camera *camera = dynamic_cast<Camera*>(targetEntity);
    cameraPreview->setCamera(mainScene, camera);
}


void EntityEditorMainView::selectEntity(Entity *targetEntity, bool addToSelection, bool doAction) {

    if(doAction) {
        beforeData = new PolycodeSceneEditorActionData();
        for(int i=0; i < selectedEntities.size(); i++) {
            beforeData->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]));
        }
    }
    
    if(targetEntity->getUserData()) {
        SceneEntityInstance *instance = (SceneEntityInstance*)targetEntity->getUserData();
        targetEntity = instance;
    }
    
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
    
    if(doAction) {
        PolycodeSceneEditorActionData *data = new PolycodeSceneEditorActionData();
        for(int i=0; i < selectedEntities.size(); i++) {
            data->entries.push_back(PolycodeSceneEditorActionDataEntry(selectedEntities[i]));
        }
        editor->didAction("select", beforeData, data, false);
        beforeData = NULL;
    }
    
    
    
    transformGizmo->setTransformSelection(selectedEntities);
    setBBox();
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
    
}

void EntityEditorMainView::setBBox(Entity *targetEntity) {
    
    if(!targetEntity) {
        if(selectedEntities.size() > 0) {
            targetEntity = selectedEntities[0];
        }
    }
    
    if(!targetEntity) {
        bBoxVis->visible = false;
        return;
    } else {
    
        bBoxVis->visible = true;
        bBoxVis->setPrimitiveOptions(ScenePrimitive::TYPE_BOX, targetEntity->getLocalBoundingBox().x, targetEntity->getLocalBoundingBox().y, targetEntity->getLocalBoundingBox().z);
        
        Matrix4 mat = targetEntity->getConcatenatedMatrix();
        bBoxVis->setTransformByMatrixPure(mat);
        bBoxVis->dirtyMatrix(false);
    }
}

Entity *EntityEditorMainView::getObjectRoot() {
    return sceneObjectRoot;
}

void EntityEditorMainView::setObjectRoot(SceneEntityInstance *entity) {
    objectRootInstance = entity;
    if(sceneObjectRoot) {
        sceneObjectRoot->getParentEntity()->removeChild(sceneObjectRoot);
        delete sceneObjectRoot;
    }
    sceneObjectRoot = entity;
    sceneObjectRoot->processInputEvents = true;
    objectRootBase->addChild(sceneObjectRoot);
    sceneObjectRoot->getParentEntity()->moveChildBottom(sceneObjectRoot);
}

EntityEditorMainView::~EntityEditorMainView() {
    mainScene->rootEntity.setOwnsChildrenRecursive(true);
    delete mainScene;
    delete renderTexture;
//    delete transformGizmo;
//    delete transformGizmoMenu;
//    delete trackballCamera;
//    delete grid;
//    delete cameraPreview;
    input->removeAllHandlersForListener(this);
}

void EntityEditorMainView::Resize(Number width, Number height) {
	headerBg->Resize(width, 30);
	footerBg->Resize(width, 30);
    
    footerBg->setPosition(0.0, height-30);
    bottomBar->setPosition(0.0, height-30);
    
	viewModeSelector->setPosition(width-viewModeSelector->getWidth()-10.0, 3);
    
    Vector2 screenPos = renderTextureShape->getScreenPosition(globalScene->getDefaultCamera()->getProjectionMatrix(), globalScene->getDefaultCamera()->getTransformMatrix(), globalScene->getDefaultCamera()->getViewport());
    
	renderTexture->resizeRenderTexture(width, height-60);
	renderTextureShape->setTexture(renderTexture->getTargetTexture());		
	renderTextureShape->Resize(width, height-60);
    
	mainScene->sceneMouseRect.x = screenPos.x;
	mainScene->sceneMouseRect.y = screenPos.y;
	mainScene->sceneMouseRect.w = renderTextureShape->getWidth();
	mainScene->sceneMouseRect.h = renderTextureShape->getHeight();
    mainScene->remapMouse = true;
    
    Update();
}

EntityEditorPropertyContainer::EntityEditorPropertyContainer(PolycodeEditor *editor) : UIElement() {
    
    this->editor = editor;
    
    propIconSelector = new UIIconSelector();
    addChild(propIconSelector);
    propIconSelector->addIcon("entityEditor/properties_icon.png");
    propIconSelector->addIcon("entityEditor/icon_tree.png");
    propIconSelector->addIcon("entityEditor/settings_icon.png");
    propIconSelector->setPosition(10.0, 3.0);
    propIconSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    propertyView = new EntityEditorPropertyView();
    propertyView->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
    addChild(propertyView);
    propertyView->setPosition(0.0, 30.0);
    currentView = propertyView;
    
    treeView = new EntityEditorTreeView();
    addChild(treeView);
    treeView->setPosition(0.0, 30.0);
    treeView->visible = false;
    treeView->enabled = false;
    
    settingsView = new EntityEditorSettingsView();
    addChild(settingsView);
    settingsView->setPosition(0.0, 30.0);
    settingsView->visible = false;
    settingsView->enabled = false;
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
                treeView->getTreeSheet()->refreshTree();
            break;
            case 2:
                currentView = settingsView;
            break;
        }
        currentView->visible = true;
        currentView->enabled = true;
    } else if(event->getDispatcher() == propertyView) {
        if(event->getEventCode() == PropEvent::EVENT_PROP_CHANGE) {
            PropEvent *propEvent  = (PropEvent*) event;
            editor->didAction("prop_change", propEvent->beforeData, propEvent->afterData);
        }
    }
}

EntityEditorPropertyContainer::~EntityEditorPropertyContainer() {
    
}

void EntityEditorPropertyContainer::Resize(Number width, Number height) {
    propertyView->Resize(width, height-30);
    treeView->Resize(width, height-30);
    settingsView->Resize(width, height-30);
}


PolycodeEntityEditor::PolycodeEntityEditor() : PolycodeEditor(true){
	mainSizer = new UIHSizer(300, 300, 300, false);
	addChild(mainSizer);
    
	mainView = new EntityEditorMainView(this);
    mainView->addEventListener(this, Event::CHANGE_EVENT);
	mainSizer->addLeftChild(mainView);
    
    mainSizer->setMinimumSize(200);
    
    propertyContainer = new EntityEditorPropertyContainer(this);
    propertyView = propertyContainer->propertyView;
    treeView = propertyContainer->treeView;
    settingsView = propertyContainer->settingsView;
    
    treeView->getTreeSheet()->addEventListener(this, Event::CHANGE_EVENT);
    
    mainSizer->addRightChild(propertyContainer);
}

void PolycodeEntityEditor::handleEvent(Event *event) {
    
    if(event->getDispatcher() == treeView->getTreeSheet()) {
        if(treeView->getTreeSheet()->getSelectedEntity() == mainView->getObjectRoot()) {
            mainView->selectNone(true);
        } else {
            mainView->selectEntity(treeView->getTreeSheet()->getSelectedEntity());
        }
    }
    
    if(event->getDispatcher() == mainView) {
        switch(event->getEventCode()) {
            case Event::CHANGE_EVENT:
                if(mainView->getSelectedEntity()) {
                    propertyView->setEntity(mainView->getSelectedEntity());
                    treeView->getTreeSheet()->setSelectedEntity(mainView->getSelectedEntity());
                    propertyView->getEntityProps()->setCaption("PROPERTIES");
                } else {
                    propertyView->setEntity(mainView->getObjectRoot(), true);
                    treeView->getTreeSheet()->setSelectedEntity(mainView->getObjectRoot());
                    propertyView->getEntityProps()->setCaption("ROOT ENTITY");
                    mainView->setBBox(mainView->getObjectRoot());
                }
            break;
        }
    }
    
    
    PolycodeEditor::handleEvent(event);
}

void PolycodeEntityEditor::doAction(String actionName, PolycodeEditorActionData *data) {
    
    if(actionName == "prop_change") {
        PolycodeEditorPropActionData *propData = (PolycodeEditorPropActionData*) data;
		propData->sheet->applyPropActionData(propData);
    } else {
        mainView->doAction(actionName, data);
    }
}

PolycodeEntityEditor::~PolycodeEntityEditor() {
    mainView->getMainScene()->rootEntity.setOwnsChildrenRecursive(true);
    delete mainView;
    delete propertyView;
    delete treeView;
    delete settingsView;
    
    delete propertyContainer;
    delete mainSizer;
}

bool PolycodeEntityEditor::openFile(OSFileEntry filePath) {	
	PolycodeEditor::openFile(filePath);
//    return true;
    loadedInstance = new SceneEntityInstance(mainView->getMainScene(), filePath.fullPath);
    
    // disable sounds :)
    for(int i=0; i < loadedInstance->getNumChildren(); i++) {
        SceneSound *sound = dynamic_cast<SceneSound*>(loadedInstance->getChildAtIndex(i));
        if(sound) {
            sound->getSound()->Stop();
        }
    }
    
    mainView->setObjectRoot(loadedInstance);
    mainView->setEditorPropsRecursive(loadedInstance);
    
    treeView->setEntityInstance(loadedInstance);
    propertyView->setEntityInstance(loadedInstance);
    settingsView->setEntityInstance(loadedInstance);
    
    mainView->dispatchEvent(new Event(), Event::CHANGE_EVENT);
    
	return true;
}

void PolycodeEntityEditor::Activate() {
    Resize(getWidth(), getHeight());
    mainView->getMainScene()->enabled = true;
    mainView->getRenderTexture()->enabled = true;
}

void PolycodeEntityEditor::Deactivate() {
    mainView->getMainScene()->enabled = false;
    mainView->getRenderTexture()->enabled = false;
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
    entry->addChild("layerID", (int)entity->layerID);
    
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
    
    if(dynamic_cast<SceneEntityInstance*>(entity) && entity != mainView->getObjectRoot()) {
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
        emitterEntry->addChild("speed", emitter->getParticleSpeed());
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
        
        saveCurveToObject(emitterEntry->addChild("scaleCurve"), &emitter->scaleCurve);
            
        saveCurveToObject(emitterEntry->addChild("colorCurveR"), &emitter->colorCurveR);
        saveCurveToObject(emitterEntry->addChild("colorCurveG"), &emitter->colorCurveG);
        saveCurveToObject(emitterEntry->addChild("colorCurveB"), &emitter->colorCurveB);
        saveCurveToObject(emitterEntry->addChild("colorCurveA"), &emitter->colorCurveA);
    }
    
    if(dynamic_cast<SceneSprite*>(entity)) {

        if(!(*(entry))["type"])
            entry->addChild("type", "SceneSprite");
        SceneSprite *sprite = (SceneSprite*) entity;
        
        ObjectEntry *spriteEntry = entry->addChild("SceneSprite");
        
        spriteEntry->addChild("sprite_set", sprite->getSpriteSet()->getName());
        spriteEntry->addChild("sprite", sprite->getCurrentSprite()->getName());
        spriteEntry->addChild("random_frame", sprite->getStartOnRandomFrame());
        
        String animName = "";
        if(sprite->getCurrentSpriteState()) {
            animName = sprite->getCurrentSpriteState()->getName();
        }
        spriteEntry->addChild("state", animName);

    }
    
    if(dynamic_cast<SceneCurve*>(entity)) {
        SceneCurve *curve = (SceneCurve*) entity;
        
        if(!(*(entry))["type"])
            entry->addChild("type", "SceneCurve");
        
        ObjectEntry *curveEntry = entry->addChild("SceneCurve");
        curveEntry->addChild("render", curve->renderCurve);
        curveEntry->addChild("resolution", curve->curveResolution);        
        saveCurveToObject(curveEntry->addChild("curve"), curve->getCurve());
        
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
        lightEntry->addChild("importance", light->getLightImportance());
        
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
        soundEntry->addChild("loopOnLoad", sound->getLoopOnLoad());
    }

    if(dynamic_cast<Camera*>(entity)) {
        Camera *camera = (Camera*) entity;
        
        if(!(*(entry))["type"]) {
            entry->addChild("type", "Camera");
        }
        
        ObjectEntry *cameraEntry = entry->addChild("Camera");
        
        cameraEntry->addChild("exposure", camera->getExposureLevel());
        cameraEntry->addChild("nearClip", camera->getNearClippingPlane());
        cameraEntry->addChild("farClip", camera->getFarClippingPlane());
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

        meshEntry->addChild("alphaTest", sceneMesh->alphaTest);
        meshEntry->addChild("backfaceCulled", sceneMesh->backfaceCulled);
        meshEntry->addChild("sendBoneMatricesToMaterial", sceneMesh->sendBoneMatricesToMaterial);
        
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
        
    entry->addChild("rX", entity->getRotationQuat().x);
    entry->addChild("rY", entity->getRotationQuat().y);
    entry->addChild("rZ", entity->getRotationQuat().z);
    entry->addChild("rW", entity->getRotationQuat().w);
    
    entry->addChild("pX", entity->getPosition().x);
    entry->addChild("pY", entity->getPosition().y);
    entry->addChild("pZ", entity->getPosition().z);
    
    entry->addChild("bbX", entity->getLocalBoundingBox().x);
    entry->addChild("bbY", entity->getLocalBoundingBox().y);
    entry->addChild("bbZ", entity->getLocalBoundingBox().z);
    
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

String PolycodeEntityEditor::Copy(void **data) {
    
    std::vector<Entity*> selectedEntities = mainView->getSelectedEntities();
    
    if(selectedEntities.size() > 0) {
        EntityEditorClipboardData *newData = new EntityEditorClipboardData();
        for(int i=0; i < selectedEntities.size(); i++) {
            ScreenEntity *clone = (ScreenEntity*)selectedEntities[i]->Clone(true, true);
            newData->entities.push_back(clone);
        }
        *data = (void*) newData;
    }
    return "Entity";
}

void PolycodeEntityEditor::destroyClipboardData(void *data, String type) {
    if(type == "Entity") {
        EntityEditorClipboardData *oldData = (EntityEditorClipboardData*) data;
        for(int i=0; i < oldData->entities.size(); i++) {
            delete oldData->entities[i];
        }
        delete oldData;
    }
}

void PolycodeEntityEditor::selectAll() {
    if(mainView->hasFocus) {
        mainView->selectAll(true);
    }
}

void PolycodeEntityEditor::Paste(void *data, String clipboardType) {
    if(!data) {
        return;
    }
    
    if(clipboardType == "Entity") {
        mainView->Paste((EntityEditorClipboardData*)data);
    }
}

void PolycodeEntityEditor::saveFile() {
    Object saveObject;
    
    ObjectEntry *settings = saveObject.root.addChild("settings");
    ObjectEntry *linkedMaterialFiles = settings->addChild("linkedResourcePools");
    for(int i=0; i < loadedInstance->getNumLinkedResourePools(); i++) {
        ResourcePool *pool = loadedInstance->getLinkedResourcePoolAtIndex(i);
        linkedMaterialFiles->addChild("resourcePool")->addChild("path", pool->getName());
    }
    
    ObjectEntry *layersEntry = settings->addChild("layers");
    for(int i=0; i < loadedInstance->getNumLayers(); i++) {
        SceneEntityInstanceLayer *layer = loadedInstance->getLayerAtIndex(i);
        if(layer->layerID != 0) {
            ObjectEntry *layerEntry = layersEntry->addChild("layer");
            layerEntry->addChild("name", layer->name);
            layerEntry->addChild("id", layer->layerID);
            layerEntry->addChild("visible", layer->visible);
        }
    }
    
    saveObject.root.name = "entity";
    saveObject.root.addChild("version", 2);
    
    ObjectEntry *children = saveObject.root.addChild("root");
    saveEntityToObjectEntry(mainView->getObjectRoot(), children);
    
    
    saveObject.saveToXML(filePath);
    setHasChanges(false);
}


void PolycodeEntityEditor::Resize(int x, int y) {
	mainSizer->Resize(x, y);
	PolycodeEditor::Resize(x,y);
}

