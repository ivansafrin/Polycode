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
 
#include "PolycodeSpriteEditor.h"
#include "PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;


SceneSpriteRewrite::SceneSpriteRewrite(SpriteSet *spriteSet) : SceneMesh(Mesh::QUAD_MESH) {
    currentSprite = NULL;
    currentSpriteState = NULL;
    this->spriteSet = spriteSet;
    defaultMesh = mesh;
    currentFrame = 0;
    core = Services()->getCore();
    spriteTimer = 0.0;
    paused = false;
    spriteTimerVal = 0.1;
}

SpriteState *SceneSpriteRewrite::getCurrentSpriteState() {
    return currentSpriteState;
}

void SceneSpriteRewrite::setPaused(bool val) {
    paused = val;
}

bool SceneSpriteRewrite::isPaused() {
    return paused;
}

void SceneSpriteRewrite::setCurrentFrame(unsigned int frameIndex) {
    currentFrame = frameIndex;
}


void SceneSpriteRewrite::setSprite(Sprite *spriteEntry) {
    currentSprite = spriteEntry;
}

void SceneSpriteRewrite::setSpriteState(SpriteState *spriteState) {
    currentSpriteState = spriteState;
}

void SceneSpriteRewrite::Update() {

    if(!currentSprite || !currentSpriteState) {
        return;
    }
    
    setTexture(spriteSet->getTexture());
    
    if(paused) {
        return;
    }
    
    spriteTimer += core->getElapsed();
    
    if(spriteTimer > 1.0/currentSpriteState->getStateFPS()) {
        spriteTimer = 0.0;
        currentFrame++;
        if(currentFrame >= currentSpriteState->getNumFrameIDs()) {
            currentFrame = 0;
        }
    }
    
}

unsigned int SceneSpriteRewrite::getCurrentFrame() {
    return currentFrame;
}

void SceneSpriteRewrite::Render() {
    
    if(!currentSprite || !currentSpriteState) {
        return;
    }
    
    Mesh *stateMesh = currentSpriteState->getMeshForFrameIndex(currentFrame);
    if(stateMesh) {
        setMesh(stateMesh);
    } else {
        setMesh(defaultMesh);
    }

    SceneMesh::Render();
}

SceneSpriteRewrite::~SceneSpriteRewrite() {
    
}

SpriteState::SpriteState(SpriteSet *spriteSet, String name) {
    this->spriteSet = spriteSet;
    this->name = name;
    stateFPS = 60.0;
}

void SpriteState::removeFrameByIndex(unsigned int index) {
    if(index < frameIDs.size()) {
        frameIDs.erase(frameIDs.begin()+index);
    }
    rebuildStateMeshes();    
}

void SpriteState::removeFrameIndices(std::vector<unsigned int> indices) {
    std::vector<unsigned int> newFrames;
    
    for(int i=0; i < frameIDs.size(); i++) {
        bool hasIndex = false;
        for(int j=0; j < indices.size(); j++) {
            if(indices[j] == i) {
                hasIndex = true;
                break;
            }
        }
        if(!hasIndex) {
            newFrames.push_back(frameIDs[i]);
        }
    }
    
    frameIDs = newFrames;
    rebuildStateMeshes();
}

void SpriteState::setStateFPS(Number fps) {
    stateFPS = fps;
}

Number SpriteState::getStateFPS() {
    return stateFPS;
}

void SpriteState::setName(String name) {
    this->name = name;
}

Mesh *SpriteState::getMeshForFrameIndex(unsigned int index) {
    if(index < frameMeshes.size()) {
        return frameMeshes[index];
    } else {
        return NULL;
    }
}

void SpriteState::rebuildStateMeshes() {
    for(int i=0; i < frameMeshes.size(); i++) {
        delete frameMeshes[i];
    }
    frameMeshes.clear();
    
    for(int i=0; i < frameIDs.size(); i++) {
        Mesh *frameMesh = new Mesh(Mesh::QUAD_MESH);
        SpriteFrame frame = spriteSet->getSpriteFrameByID(frameIDs[i]);
        
        frameMesh->indexedMesh = true;
        
        Number frameWidth = 100.0;
        Number frameHeight = 100.0;
        
        frameMesh->addVertex(0.0, 0.0, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y);
        frameMesh->addVertex(0.0, -frameHeight, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y  - frame.coordinates.h);
        frameMesh->addVertex(frameWidth, -frameHeight, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0- frame.coordinates.y  - frame.coordinates.h);
        frameMesh->addVertex(frameWidth, 0.0, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0-frame.coordinates.y);
        
        frameMesh->addIndexedFace(0,1);
        frameMesh->addIndexedFace(1,2);
        frameMesh->addIndexedFace(2,3);
        frameMesh->addIndexedFace(3,0);
        
        frameMesh->dirtyArrays();
        
        frameMeshes.push_back(frameMesh);
    }
}

String SpriteState::getName() const {
    return name;
}

unsigned int SpriteState::getNumFrameIDs() {
    return frameIDs.size();
}

unsigned int SpriteState::getFrameIDAtIndex(unsigned int index) {
    if(index < frameIDs.size()) {
        return frameIDs[index];
    } else {
        return 0;
    }
}

void SpriteState::appendFrames(std::vector<unsigned int> newFrameIDs) {
    frameIDs.insert( frameIDs.end(), newFrameIDs.begin(), newFrameIDs.end());
    rebuildStateMeshes();
}

unsigned int Sprite::getNumStates() {
    return states.size();
}

SpriteState *Sprite::getState(unsigned int index) {
    if(index < states.size()) {
        return states[index];
    } else {
        return NULL;
    }
}

void Sprite::addSpriteState(SpriteState *state) {
    states.push_back(state);
}

Sprite::Sprite(String name) {
    this->name = name;
}

String Sprite::getName() {
    return name;
}

void Sprite::setName(String name) {
    this->name = name;
}


SpriteSet::SpriteSet(String imageFileName) {
    loadTexture(imageFileName);
    nextFrameIDIndex = 0;
}

void SpriteSet::removeFrameByID(unsigned int frameID) {
    for(int i=0; i < frames.size(); i++) {
        if(frames[i].frameID == frameID) {
            frames.erase(frames.begin() + i);
            return;
        }
    }
}

Texture *SpriteSet::loadTexture(String imageFileName) {
    Texture *spriteTexture = Services()->getMaterialManager()->createTextureFromFile(imageFileName, true, Services()->getMaterialManager()->mipmapsDefault);
    setTexture(spriteTexture);
    return spriteTexture;
}

void SpriteSet::addSpriteFrame(const SpriteFrame &frame) {
    
    // do not add existing frames
    for(int i=0; i < frames.size(); i++) {
        SpriteFrame existingFrame = frames[i];
        
        if(existingFrame.coordinates == frame.coordinates) {
            return;
        }
        
    }
    
    frames.push_back(frame);
    frames[frames.size()-1].frameID = nextFrameIDIndex;
    nextFrameIDIndex++;
    
}

SpriteFrame SpriteSet::getSpriteFrameByID(unsigned int frameID) const {
    for(int i=0; i < frames.size(); i++) {
        if(frames[i].frameID == frameID ){
            return frames[i];
        }
    }
    return SpriteFrame();
}

unsigned int SpriteSet::getNumFrames() const {
    return frames.size();
}

SpriteFrame SpriteSet::getSpriteFrame(unsigned int index) const {
    if(index < frames.size()) {
        return frames[index];
    } else {
        return SpriteFrame();
    }
}

void SpriteSet::addSpriteEntry(Sprite *newEntry) {
    sprites.push_back(newEntry);
}

unsigned int SpriteSet::getNumSpriteEntries() const {
    return sprites.size();
}

Sprite *SpriteSet::getSpriteEntry(unsigned int index) const {
    if(index < sprites.size()) {
        return sprites[index];
    } else {
        return NULL;
    }
}

void SpriteSet::setTexture(Texture *texture) {
    spriteTexture = texture;
}

Texture *SpriteSet::getTexture() {
    return spriteTexture;
}

SpriteSet::~SpriteSet() {
    
}

void SpriteSet::clearFrames() {
    frames.clear();
    nextFrameIDIndex = 0;
}

void SpriteSet::createGridFrames(Number width, Number height) {
    
    for(Number x = 0.0; x+width <= 1.0; x += width) {
        for(Number y = 0.0; y+height <= 1.0; y += height) {
            SpriteFrame frame;
            frame.coordinates = Polycode::Rectangle(x, y, width, height);
            addSpriteFrame(frame);
        }
    }
}

Polycode::Rectangle createBoxAtCoordinate(Image *image, unsigned int x, unsigned int y) {
    Polycode::Rectangle rect;
    
    rect.x = x;
    rect.y = y;
    
    while(x < image->getWidth()) {
        if(image->getPixel(x, y).a == 0.0) {
            break;
        }
        x++;
    }
    rect.w = x - rect.x;
    
    // look down at first x
    Number y1 = y;
    while(y1 < image->getHeight()) {
        if(image->getPixel(rect.x, y1).a == 0.0) {
            break;
        }
        y1++;
    }
    Number h1 = y1;
    
    // look down at last x
    while(y < image->getHeight()) {
        if(image->getPixel(x, y).a == 0.0) {
            break;
        }
        y++;
    }
    Number h2 = y;

    if(h1 > h2) {
        h2 = h1;
    }
    
    rect.h = h2 - rect.y;
    

    
    return rect;
}

bool rectIntersect(const Polycode::Rectangle &r1, const Polycode::Rectangle &r2, Number minDistance) {
    return !(r2.x - minDistance > r1.x + r1.w ||
             r2.x + r2.w + minDistance < r1.x ||
             r2.y - minDistance > r1.y + r1.h ||
             r2.y + r2.h + minDistance < r1.y);
}

void SpriteSet::createFramesFromIslands(unsigned int minDistance) {
    String imageFileName = getTexture()->getResourcePath();
    
    Image *image = new Image(imageFileName);
    
    
    std::vector<Polycode::Rectangle> rects;
    
    for(int y=0; y < image->getHeight(); y++) {
        for(int x=0; x < image->getWidth(); x++) {
            if(image->getPixel(x, y).a > 0.0) {
                Polycode::Rectangle rect = createBoxAtCoordinate(image,x,y);
                rects.push_back(rect);
                x += rect.w;
            }
        }
    }
    
    while(rects.size() > 1) {

        bool intersected = false;
        for(int i=0; i < rects.size(); i++) {
            for(int i2=0; i2 < rects.size(); i2++) {
                if(i != i2) {
                    if(rectIntersect(rects[i], rects[i2], minDistance)) {

                        Polycode::Rectangle newRect;
                        
                        newRect.x = std::min(rects[i].x, rects[i2].x);
                        newRect.y = std::min(rects[i].y, rects[i2].y);
                        
                        newRect.w = std::max(rects[i].x + rects[i].w, rects[i2].x + rects[i2].w) - newRect.x;
                        newRect.h = std::max(rects[i].y + rects[i].h, rects[i2].y + rects[i2].h) - newRect.y;
                        
                        rects[i] = newRect;
                        rects.erase(rects.begin() + i2);
                        
                        intersected = true;
                        
                        break;
                    }
                }
            }
        }

        if(!intersected) {
            break;
        }
  
    }
    
    
    for(int i=0; i < rects.size(); i++) {
        SpriteFrame frame;
        frame.coordinates = rects[i];
        
        frame.coordinates.x = frame.coordinates.x / ((Number)image->getWidth());
        frame.coordinates.y = frame.coordinates.y / ((Number)image->getHeight());
        frame.coordinates.w = frame.coordinates.w / ((Number)image->getWidth());
        frame.coordinates.h = frame.coordinates.h / ((Number)image->getHeight());
        
        addSpriteFrame(frame);
    }
    
    delete image;
}

SpriteSheetEditor::SpriteSheetEditor(SpriteSet *sprite) : UIElement() {
    
    this->sprite = sprite;
    
    zoomScale = 1.0;
    enableScissor = true;
    
    previewBg = new UIImage("main/grid_dark.png");
    addChild(previewBg);
    previewBg->processInputEvents = true;
    
    panning = false;
    
    previewBg->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
    previewBg->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
    previewBg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    previewBg->addEventListener(this, InputEvent::EVENT_MOUSEUP);
    previewBg->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
    
    previewImage = new UIRect(10, 10);
    previewImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    addChild(previewImage);
    
    frameVisualizerMesh = new SceneMesh(Mesh::LINE_MESH);
    frameVisualizerMesh->setColor(1.0, 1.0, 1.0, 1.0);
    addChild(frameVisualizerMesh);
    frameVisualizerMesh->setAnchorPoint(-1.0, -1.0, 0.0);
    frameVisualizerMesh->loadTexture("main/stipple.png");
    frameVisualizerMesh->lineWidth = 1; //CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX();

    frameVisualizerMeshSelected = new SceneMesh(Mesh::LINE_MESH);
    frameVisualizerMeshSelected->setColor(1.0, 1.0, 0.0, 1.0);
    addChild(frameVisualizerMeshSelected);
    frameVisualizerMeshSelected->setAnchorPoint(-1.0, -1.0, 0.0);
    frameVisualizerMeshSelected->loadTexture("main/stipple.png");
    frameVisualizerMeshSelected->lineWidth = 2;
    
    
    previewImage->setTexture(sprite->getTexture());
    
    bottomMenu = new Entity();
    addChild(bottomMenu);
    
    bottomMenu->processInputEvents = true;
    
    bottomMenuRect = new UIRect(100, 100);
	bottomMenu->addChild(bottomMenuRect);
	bottomMenuRect->setAnchorPoint(-1.0, -1.0, 0.0);
	bottomMenuRect->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
    
    changeImageButton = new UIButton("Change image", 120);
    bottomMenu->addChild(changeImageButton);
    changeImageButton->addEventListener(this, UIEvent::CLICK_EVENT);
    changeImageButton->setPosition(5.0, 3.0);
    
    clearFramesButton = new UIButton("Clear frames", 110);
    bottomMenu->addChild(clearFramesButton);
    clearFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
    clearFramesButton->setPosition(130.0, 3.0);
    
    generateFramesButton = new UIButton("Generate frames", 120);
    bottomMenu->addChild(generateFramesButton);
    generateFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
    generateFramesButton->setPosition(230.0, 3.0);
    
    generateTypeDropdown = new UIComboBox(globalMenu, 120);
    bottomMenu->addChild(generateTypeDropdown);
    generateTypeDropdown->setPosition(360, 3.0);
    
    generateTypeDropdown->addComboItem("Uniform grid");
    generateTypeDropdown->addComboItem("Detect islands");
    
    generateTypeDropdown->setSelectedIndex(0);
    
    uniformGridWidthInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(uniformGridWidthInput);
    uniformGridWidthInput->setPosition(485, 3);
    uniformGridWidthInput->setText("32");
    uniformGridWidthInput->setNumberOnly(true);

    uniformGridHeightInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(uniformGridHeightInput);
    uniformGridHeightInput->setPosition(530, 3);
    uniformGridHeightInput->setText("32");
    uniformGridHeightInput->setNumberOnly(true);
    
    minimumDistanceInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(minimumDistanceInput);
    minimumDistanceInput->setPosition(575, 3);
    minimumDistanceInput->setText("0");
    minimumDistanceInput->setNumberOnly(true);
    
    creatingFrame = false;
    
    Services()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

bool SpriteSheetEditor::hasSelectedID(unsigned int frameID) {
    for(int i=0; i < selectedIDs.size(); i++) {
        if(selectedIDs[i] == frameID) {
            return true;
        }
    }
    return false;
}

void SpriteSheetEditor::Update() {
    Mesh *mesh = frameVisualizerMesh->getMesh();
    Mesh *meshSelected = frameVisualizerMeshSelected->getMesh();
    
    mesh->clearMesh();
    meshSelected->clearMesh();
    
    mesh->indexedMesh = true;
    meshSelected->indexedMesh = true;
    
    unsigned int offsetSelected = 0;
    unsigned int offset = 0;
    
    for(int i=0; i < sprite->getNumFrames(); i++){
        SpriteFrame frame = sprite->getSpriteFrame(i);
        
        mesh->addVertex(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
        mesh->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
        mesh->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
        mesh->addVertex(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
        mesh->addIndexedFace(offset+0,offset+1);
        mesh->addIndexedFace(offset+1,offset+2);
        mesh->addIndexedFace(offset+2,offset+3);
        mesh->addIndexedFace(offset+3,offset+0);
        offset += 4;
        
        if(hasSelectedID(frame.frameID)) {
            meshSelected->addVertex(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
            meshSelected->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
            meshSelected->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
            meshSelected->addVertex(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
            meshSelected->addIndexedFace(offsetSelected+0,offsetSelected+1);
            meshSelected->addIndexedFace(offsetSelected+1,offsetSelected+2);
            meshSelected->addIndexedFace(offsetSelected+2,offsetSelected+3);
            meshSelected->addIndexedFace(offsetSelected+3,offsetSelected+0);
            offsetSelected += 4;
        }
        
    }
    
    if(creatingFrame) {
     
        SpriteFrame frame = frameToAdd;
        
        mesh->addVertex(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
        mesh->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
        mesh->addVertex(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
        mesh->addVertex(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
        mesh->addIndexedFace(offset+0,offset+1);
        mesh->addIndexedFace(offset+1,offset+2);
        mesh->addIndexedFace(offset+2,offset+3);
        mesh->addIndexedFace(offset+3,offset+0);
        offset += 4;

    }
    
    mesh->dirtyArrays();
    meshSelected->dirtyArrays();
}

void SpriteSheetEditor::handleEvent(Event *event) {
    if(event->getDispatcher() == changeImageButton) {
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("png");
        globalFrame->showAssetBrowser(extensions);
    } else if(event->getDispatcher() == generateFramesButton) {
        if(generateTypeDropdown->getSelectedIndex() == 0) {
            Number frameWidth = uniformGridWidthInput->getText().toNumber() / ((Number)sprite->getTexture()->getWidth());
            Number frameHeight = uniformGridHeightInput->getText().toNumber() / ((Number)sprite->getTexture()->getHeight());
            sprite->createGridFrames(frameWidth, frameHeight);
        } else {
            sprite->createFramesFromIslands(minimumDistanceInput->getText().toInteger());
        }
        
        dispatchEvent(new Event(),Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == clearFramesButton) {
        sprite->clearFrames();
        dispatchEvent(new Event(),Event::CHANGE_EVENT);
    } else if(event->getDispatcher() == globalFrame->assetBrowser) {
        String newImagePath = globalFrame->assetBrowser->getSelectedAssetPath();
        
        sprite->loadTexture(globalFrame->assetBrowser->getSelectedAssetPath());
        previewImage->setTexture(sprite->getTexture());
        
        globalFrame->assetBrowser->removeAllHandlersForListener(this);
        globalFrame->hideModal();
        
        Resize(getWidth(), getHeight());
      
    } else if(event->getDispatcher() == Services()->getCore()->getInput()) {
        InputEvent *inputEvent = (InputEvent*) event;
        
        switch(inputEvent->getEventCode()) {
            case InputEvent::EVENT_KEYDOWN:
            {
                switch(inputEvent->getKey()) {
                    case Polycode::KEY_BACKSPACE:
                    case Polycode::KEY_DELETE:
                        if(previewBg->hasFocus) {
                            deleteSelectedFrames();
                        }
                    break;
                }
            }
            break;
        }
        
    } else if(event->getDispatcher() == previewBg) {
        
        switch(event->getEventCode()) {
            case InputEvent::EVENT_MOUSEWHEEL_UP:
                zoomScale *= 1.02;
                Resize(getWidth(), getHeight());
            break;
            case InputEvent::EVENT_MOUSEWHEEL_DOWN:
                zoomScale *= 0.98;
                if(zoomScale < 0.1) {
                    zoomScale = 0.1;
                }
                Resize(getWidth(), getHeight());
            break;
            case InputEvent::EVENT_MOUSEDOWN:
                
                previewBg->focusSelf();
                
                if(Services()->getCore()->getInput()->getKeyState(KEY_LALT)) {
                    panning = true;
                    panMouseBase = Services()->getCore()->getInput()->getMousePosition();
                } else {
                    
                    if(!Services()->getCore()->getInput()->getKeyState(KEY_LSHIFT) &&
                       !Services()->getCore()->getInput()->getKeyState(KEY_LSHIFT)) {
                        clearSelected();
                    }
                    
                    // check hit detection on frames
                    Vector2 mouseCoord = Services()->getCore()->getInput()->getMousePosition();
                    clickBaseCoord = mouseCoord;
                    
                    for(int i=0; i < sprite->getNumFrames(); i++) {
                        SpriteFrame frame = sprite->getSpriteFrame(i);
                        
                        Polycode::Rectangle transforedCoords;
                        
                        Vector2 corner = previewImage->getScreenPositionForMainCamera();
                        
                        transforedCoords.x = corner.x + (frame.coordinates.x * zoomScale * previewImage->getWidth()) ;
                        transforedCoords.y = corner.y + (frame.coordinates.y * zoomScale * previewImage->getHeight());
                        transforedCoords.w = frame.coordinates.w * zoomScale * previewImage->getWidth();
                        transforedCoords.h = frame.coordinates.h * zoomScale  * previewImage->getHeight();

                        if(mouseCoord.x >= transforedCoords.x && mouseCoord.x <= transforedCoords.x + transforedCoords.w && mouseCoord.y >= transforedCoords.y && mouseCoord.y <= transforedCoords.y + transforedCoords.h) {
                            if(!hasSelectedID(frame.frameID)) {
                                selectedIDs.push_back(frame.frameID);
                            }
                            break;
                        }
                    }
                }
            break;
            case InputEvent::EVENT_MOUSEMOVE:
                if(panning) {
                    panOffset += Services()->getCore()->getInput()->getMousePosition() - panMouseBase;
                    panMouseBase = Services()->getCore()->getInput()->getMousePosition();
                    Resize(getWidth(), getHeight());
                } else {
                    CoreInput *input = Services()->getCore()->getInput();
                    
                    if(input->getMouseButtonState(CoreInput::MOUSE_BUTTON1)) {
                        if(clickBaseCoord.distance(input->getMousePosition()) > 2.0) {
                            
                            Vector2 screenCoordinates = previewImage->getScreenPositionForMainCamera();
                            screenCoordinates = clickBaseCoord - screenCoordinates;
                            
                            screenCoordinates.x = screenCoordinates.x / previewImage->getWidth() / zoomScale;
                            screenCoordinates.y = screenCoordinates.y / previewImage->getHeight() / zoomScale;
                            
                            
                            Vector2 screenCoordinates2 = previewImage->getScreenPositionForMainCamera();
                            screenCoordinates2 = input->getMousePosition() - screenCoordinates2;
                            
                            screenCoordinates2.x = screenCoordinates2.x / previewImage->getWidth() / zoomScale;
                            screenCoordinates2.y = screenCoordinates2.y / previewImage->getHeight() / zoomScale;
                            
                            frameToAdd.coordinates.x = screenCoordinates.x;
                            frameToAdd.coordinates.y = screenCoordinates.y;
                            
                            frameToAdd.coordinates.w = screenCoordinates2.x - screenCoordinates.x;
                            frameToAdd.coordinates.h = screenCoordinates2.y - screenCoordinates.y;
                            
                            creatingFrame = true;
                            
                        }
                    }
                }
            break;
            case InputEvent::EVENT_MOUSEUP:
                panning = false;
                if(creatingFrame) {
                    creatingFrame = false;
                    if(fabs(frameToAdd.coordinates.w) > 0.001 & fabs(frameToAdd.coordinates.h) > 0.001) {
                        
                        if(frameToAdd.coordinates.w < 0.0) {
                            frameToAdd.coordinates.x = frameToAdd.coordinates.x + frameToAdd.coordinates.w;
                            frameToAdd.coordinates.w *= -1.0;
                        }

                        if(frameToAdd.coordinates.h < 0.0) {
                            frameToAdd.coordinates.y = frameToAdd.coordinates.y + frameToAdd.coordinates.h;
                            frameToAdd.coordinates.h *= -1.0;
                        }
                        
                        
                        sprite->addSpriteFrame(frameToAdd);
                    }
                }
            break;
        }
    }
}

void SpriteSheetEditor::deleteSelectedFrames() {
 
    for(int i=0; i < selectedIDs.size(); i++) {
        sprite->removeFrameByID(selectedIDs[i]);
    }
    clearSelected();
}

void SpriteSheetEditor::clearSelected() {
    selectedIDs.clear();
}

SpriteSheetEditor::~SpriteSheetEditor() {
    
}

std::vector<unsigned int> SpriteSheetEditor::getSelectedFrameIDs() {
    return selectedIDs;
}

void SpriteSheetEditor::Resize(Number width, Number height) {
    
    previewBg->Resize(width, height-30.0);
    previewBg->setImageCoordinates(0, 0, width, height-30);
    
    Vector2 screenPosition = getScreenPositionForMainCamera();
    scissorBox.setRect(screenPosition.x, screenPosition.y, width, height);
    
    
    Number imageAspectRatio = ((Number)previewImage->getTexture()->getHeight()) / ((Number)previewImage->getTexture()->getWidth());
    
    Number imageWidth = (height-30.0) / imageAspectRatio;
    Number imageHeight = height-30.0;
    
    if(imageWidth > width) {
        imageWidth = width;
        imageHeight = width * imageAspectRatio;
    }
    
    previewImage->Resize(imageWidth, imageHeight);
    previewImage->setScale(zoomScale, zoomScale, 1.0);
    
    previewImage->setPosition((width-(previewImage->getWidth()*zoomScale))/ 2.0, (height-(previewImage->getHeight()*zoomScale)-30.0)/2.0);
    
    previewImage->Translate(panOffset.x, panOffset.y, 0.0);
    
    frameVisualizerMesh->setPosition(previewImage->getPosition());
    frameVisualizerMesh->setScale(previewImage->getWidth() * zoomScale, previewImage->getHeight() * zoomScale, 1.0);

    frameVisualizerMeshSelected->setPosition(previewImage->getPosition());
    frameVisualizerMeshSelected->setScale(previewImage->getWidth() * zoomScale, previewImage->getHeight() * zoomScale, 1.0);
    

    
    bottomMenuRect->Resize(width, 31.0);
    bottomMenu->setPosition(0.0, height-30.0);
    
    UIElement::Resize(width, height);
}

SpriteBrowser::SpriteBrowser(SpriteSet *spriteSet) : UIElement () {
    this->spriteSet = spriteSet;
    
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
    newSpriteButton = new UIButton("Add", 40);
    addChild(newSpriteButton);
    newSpriteButton->setPosition(3.0, 3.0);
    newSpriteButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    spriteTreeView = new UITreeContainer("boxIcon.png", "Sprites", 10, 10);
    spriteTreeView->setPosition(0, 30);
    addChild(spriteTreeView);
    
    spriteTreeView->getRootNode()->toggleCollapsed();
    
    spriteTreeView->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
}

void SpriteBrowser::handleEvent(Event *event) {
    if(event->getDispatcher() == newSpriteButton) {
        Sprite *newEntry = new Sprite("New Sprite");
        spriteSet->addSpriteEntry(newEntry);
        refreshSprites();
    } else if(event->getDispatcher() ==   spriteTreeView->getRootNode()) {
        selectedEntry = (Sprite*) spriteTreeView->getRootNode()->getSelectedNode()->getUserData();
        if(selectedEntry) {
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
        }
    }
}

Sprite *SpriteBrowser::getSelectedSpriteEntry() {
    return selectedEntry;
}

void SpriteBrowser::refreshSprites() {
    spriteTreeView->getRootNode()->clearTree();
    for(int i=0; i < spriteSet->getNumSpriteEntries(); i++) {
        Sprite *spriteEntry = spriteSet->getSpriteEntry(i);
        spriteTreeView->getRootNode()->addTreeChild("file.png", spriteEntry->getName(), (void*)spriteEntry);
    }
}

SpriteBrowser::~SpriteBrowser() {
    
}

void SpriteBrowser::Resize(Number width, Number height) {
    headerBg->Resize(width, 30.0);
    
    spriteTreeView->Resize(width, height-30);
}

SpriteStateEditorDetails::SpriteStateEditorDetails(SpriteSet *spriteSet) : UIElement() {
    
    this->spriteSet = spriteSet;
    
    editBar = new SpriteStateEditBar(spriteSet);
    addChild(editBar);
    editBar->setPosition(10.0, 50.0);
    
    playButton = new UIImageButton("spriteEditor/play_button.png", 1.0, 32, 32);
    addChild(playButton);
    playButton->setPosition(10.0, 5.0);
    playButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    pauseButton = new UIImageButton("spriteEditor/pause_button.png", 1.0, 32, 32);
    addChild(pauseButton);
    pauseButton->setPosition(10.0, 5.0);
    pauseButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    appendFramesButton = new UIButton("Append selected frames", 200.0);
    addChild(appendFramesButton);
    appendFramesButton->setPosition(100.0, 10.0);
    appendFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    fpsInput = new UITextInput(false, 30.0, 12.0);
    addChild(fpsInput);
    fpsInput->setPosition(50.0, 10.0);
    fpsInput->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    visible = false;
    enabled = false;
}

void SpriteStateEditBar::setSceneSprite(SceneSpriteRewrite *sprite) {
    sceneSprite = sprite;
}

SpriteStateEditBar *SpriteStateEditorDetails::getEditBar() {
    return editBar;
}

void SpriteStateEditorDetails::setSceneSprite(SceneSpriteRewrite *sceneSprite) {
    this->sceneSprite = sceneSprite;
    editBar->setSceneSprite(sceneSprite);
}

void SpriteStateEditorDetails::Update() {
    if(sceneSprite) {
        if(sceneSprite->isPaused()) {
            playButton->visible = true;
            playButton->enabled = true;
            pauseButton->visible = false;
            pauseButton->enabled = false;
        } else {
            playButton->visible = false;
            playButton->enabled = false;
            pauseButton->visible = true;
            pauseButton->enabled = true;
        }
    }
}

void SpriteStateEditorDetails::setSpriteState(SpriteState *state) {
    visible = true;
    enabled = true;
    spriteState = state;
    
    fpsInput->setText(String::NumberToString(state->getStateFPS()));
    
    editBar->setSpriteState(state);
}

void SpriteStateEditorDetails::handleEvent(Event *event) {
    if(event->getDispatcher() == fpsInput) {
        spriteState->setStateFPS(fpsInput->getText().toNumber());
    } else if(event->getDispatcher() == playButton) {
        sceneSprite->setPaused(false);
    }  else if(event->getDispatcher() == pauseButton) {
        sceneSprite->setPaused(true);
    }
}

SpriteStateEditorDetails::~SpriteStateEditorDetails() {
    
}

UIButton *SpriteStateEditorDetails::getAppendFramesButton() {
    return appendFramesButton;
}

SpriteState *SpriteStateEditorDetails::getSpriteState() {
    return spriteState;
}

void SpriteStateEditorDetails::refreshState() {
    editBar->refreshBar();
}

void SpriteStateEditorDetails::Resize(Number width, Number height) {
    editBar->Resize(width, height-30.0);
    editBar->Resize(width-20.0, height-60.0);
}

void SpriteStateEditBar::clearBar() {
    
}

void SpriteStateEditBar::setSpriteState(SpriteState *state) {
    spriteState = state;
    state->rebuildStateMeshes();
    refreshBar();
    
}

void SpriteStateEditBar::refreshBar() {
    
    if(!spriteSet || !spriteState || !sceneSprite) {
        return;
    }
    
    barMesh->setTexture(spriteSet->getTexture());
    
    Mesh *mesh = barMesh->getMesh();
    mesh->clearMesh();
    mesh->indexedMesh = true;
    
    Mesh *meshBg = barMeshBg->getMesh();
    meshBg->clearMesh();
    meshBg->indexedMesh = true;
    meshBg->useVertexColors = true;
    
    Mesh *meshTicks = frameTicksMesh->getMesh();
    meshTicks->clearMesh();
    meshTicks->indexedMesh = true;
    meshTicks->useVertexColors = true;
    
    Mesh *meshGrips = frameGripsMesh->getMesh();
    meshGrips->clearMesh();
    meshGrips->indexedMesh = true;
    
    Number frameOffset;
    Number frameSize;
    
    unsigned int offset = 0;
    for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
        unsigned int frameID = spriteState->getFrameIDAtIndex(i);
     
        SpriteFrame frame = spriteSet->getSpriteFrameByID(frameID);
        
        Number gapSize = 1.0;
        
        Number frameTickHeight = 10.0;
        Number frameTickGap = 2.0;
        
        frameSize = defaultFrameWidth * zoomScale;
        Number frameHeight = getHeight()-frameTickHeight-frameTickGap-scroller->getHScrollBar()->getHeight();
        
        if(frameHeight < 32.0) {
            frameHeight = 32.0;
        }
        
        frameOffset = ((Number)i) * frameSize;
        
        // draw frame ticks
        
        Color vertexColor(0.1, 0.1, 0.1, 1.0);
        if(i % 2) {
            vertexColor = Color(0.2, 0.2, 0.2, 1.0);
        }
        
        if(i == sceneSprite->getCurrentFrame()) {
            vertexColor = Color(1.0, 0.8, 0.0, 1.0);
        }
        
        meshTicks->addVertex(frameOffset, 0.0, 0.0, 0.0, 0.0)->vertexColor = vertexColor;
        meshTicks->addVertex(frameOffset, 0.0-frameTickHeight, 0.0, 0.0, 1.0)->vertexColor = vertexColor;
        meshTicks->addVertex(frameOffset+frameSize-gapSize, -frameTickHeight, 0.0, 1.0, 1.0)->vertexColor = vertexColor;
        meshTicks->addVertex(frameOffset+frameSize-gapSize, 0.0, 0.0, 1.0, 0.0)->vertexColor = vertexColor;
        
        
        meshTicks->addIndexedFace(offset+0,offset+1);
        meshTicks->addIndexedFace(offset+1,offset+2);
        meshTicks->addIndexedFace(offset+2,offset+3);
        meshTicks->addIndexedFace(offset+3,offset+0);
        
        // draw icons
        
        Number imageAspectRatio = ((Number)spriteSet->getTexture()->getWidth()) / ((Number)spriteSet->getTexture()->getHeight());
        Number aspectRatio = frame.coordinates.h / frame.coordinates.w / imageAspectRatio;
        
        Number iconFrameWidth = frameSize * 0.5;
        Number iconFrameHeight = iconFrameWidth * aspectRatio;
        
        if(iconFrameHeight > frameHeight * 0.8) {
            iconFrameHeight = frameHeight * 0.8;
            iconFrameWidth = iconFrameHeight / aspectRatio;
        }
        
        Number iconOffset = 2.0;
        
        mesh->addVertex(frameOffset+iconOffset, -frameTickHeight-frameTickGap-iconOffset, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y);
        mesh->addVertex(frameOffset+iconOffset, -frameTickHeight-frameTickGap-iconFrameHeight-iconOffset, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y  - frame.coordinates.h);
        mesh->addVertex(frameOffset+iconFrameWidth+iconOffset, -frameTickHeight-frameTickGap-iconFrameHeight-iconOffset, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0- frame.coordinates.y  - frame.coordinates.h);
        mesh->addVertex(frameOffset+iconFrameWidth+iconOffset, -frameTickHeight-frameTickGap-iconOffset, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0-frame.coordinates.y);
        
        mesh->addIndexedFace(offset+0,offset+1);
        mesh->addIndexedFace(offset+1,offset+2);
        mesh->addIndexedFace(offset+2,offset+3);
        mesh->addIndexedFace(offset+3,offset+0);
        
        // draw frame backgrounds
        
        Color bgFrameColor = Color(1.0, 1.0, 1.0, 1.0);
        
        if(isFrameSelected(i)) {
            bgFrameColor = Color(1.0, 0.5, 0.5, 1.0);
        }
        
        meshBg->addVertex(frameOffset, -frameTickHeight-frameTickGap, 0.0, 0.0, 0.0)->vertexColor = bgFrameColor;
        meshBg->addVertex(frameOffset, -frameTickHeight-frameTickGap-frameHeight, 0.0, 0.0, 1.0)->vertexColor = bgFrameColor;
        meshBg->addVertex(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-frameHeight, 0.0, 1.0, 1.0)->vertexColor = bgFrameColor;
        meshBg->addVertex(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap, 0.0, 1.0, 0.0)->vertexColor = bgFrameColor;

        
        meshBg->addIndexedFace(offset+0,offset+1);
        meshBg->addIndexedFace(offset+1,offset+2);
        meshBg->addIndexedFace(offset+2,offset+3);
        meshBg->addIndexedFace(offset+3,offset+0);
        
        
        Number gripWidth = 8;
        Number gripHeight = 24;
        
        Number gripOffset = (frameHeight-24.0) / 2.0;
        
        meshGrips->addVertex(frameOffset+frameSize-gapSize-gripWidth, -frameTickHeight-frameTickGap-gripOffset, 0.0, 0.0, 0.0);
        meshGrips->addVertex(frameOffset+frameSize-gapSize-gripWidth, -frameTickHeight-frameTickGap-gripHeight-gripOffset, 0.0, 0.0, 1.0);
        meshGrips->addVertex(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-gripHeight-gripOffset, 0.0, 1.0, 1.0);
        meshGrips->addVertex(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-gripOffset, 0.0, 1.0, 0.0);
        
        meshGrips->addIndexedFace(offset+0,offset+1);
        meshGrips->addIndexedFace(offset+1,offset+2);
        meshGrips->addIndexedFace(offset+2,offset+3);
        meshGrips->addIndexedFace(offset+3,offset+0);
        
        offset += 4;
        
    }
    
    mesh->dirtyArrays();
    meshBg->dirtyArrays();
    meshTicks->dirtyArrays();
    
    scroller->setContentSize(frameOffset+frameSize, getHeight());
}

bool SpriteStateEditBar::isFrameSelected(unsigned int frameIndex) {
    for(int i=0; i < selectedFrames.size(); i++) {
        if(selectedFrames[i] == frameIndex) {
            return true;
        }
    }
    return false;
}

void SpriteStateEditBar::Update() {
    refreshBar();
}

void SpriteStateEditBar::Resize(Number width, Number height) {
    UIElement::Resize(width, height);
    scroller->Resize(width, height);
    refreshBar();
}

SpriteStateEditBar::SpriteStateEditBar(SpriteSet *spriteSet) : UIElement() {
    
    this->spriteSet = spriteSet;
    sceneSprite = NULL;
    spriteState = NULL;
    
    barBase = new UIElement();
    
    barMeshBg = new SceneMesh(Mesh::QUAD_MESH);
    barBase->addChild(barMeshBg);
    barMeshBg->loadTexture("spriteEditor/sprite_frame_bg.png");
    barMeshBg->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
    barMesh = new SceneMesh(Mesh::QUAD_MESH);
    barBase->addChild(barMesh);
    barMesh->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
    frameTicksMesh = new SceneMesh(Mesh::QUAD_MESH);
    barBase->addChild(frameTicksMesh);
    
    frameGripsMesh = new SceneMesh(Mesh::QUAD_MESH);
    barBase->addChild(frameGripsMesh);
    frameGripsMesh->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    frameGripsMesh->loadTexture("spriteEditor/frame_grip.png");
    
    this->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
    this->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
    this->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
    
    Services()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    
    zoomScale = 1.0;
    defaultFrameWidth = 50.0;
    
    scroller = new UIScrollContainer(barBase, true, false, 10, 10);
    addChild(scroller);
}

void SpriteStateEditBar::handleEvent(Event *event) {
    if(event->getDispatcher() == this) {
        InputEvent *inputEvent = (InputEvent*) event;
        
        switch(event->getEventCode()) {
            case InputEvent::EVENT_MOUSEWHEEL_UP:
                zoomScale *= 1.02;
            break;
            case InputEvent::EVENT_MOUSEWHEEL_DOWN:
                zoomScale *= 0.98;
                if(zoomScale < 0.25) {
                    zoomScale = 0.25;
                }
            break;
            case InputEvent::EVENT_MOUSEDOWN:
                if(inputEvent->getMousePosition().y < getHeight()-scroller->getHScrollBar()->getHeight()) {
                    unsigned int selectedFrameIndex = (inputEvent->getMousePosition().x - barBase->getPosition().x)/ defaultFrameWidth / zoomScale;
                    if(!Services()->getCore()->getInput()->getKeyState(KEY_LSHIFT) &&
                       !Services()->getCore()->getInput()->getKeyState(KEY_LSHIFT)) {
                        selectedFrames.clear();
                    }
                    selectedFrames.push_back(selectedFrameIndex);
                }
                focusSelf();
            break;
        }
    } else if(event->getDispatcher() == Services()->getCore()->getInput()) {
        InputEvent *inputEvent = (InputEvent*) event;
        
        if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
            switch(inputEvent->getKey()) {
                case Polycode::KEY_DELETE:
                case Polycode::KEY_BACKSPACE:
                    if(hasFocus) {
                        deleteSelectedFrames();
                    }
                break;
            }
        }
    }
}

void SpriteStateEditBar::deleteSelectedFrames() {
    if(!spriteState) {
        return;
    }
    spriteState->removeFrameIndices(selectedFrames);
    selectedFrames.clear();
}

SpriteStateEditBar::~SpriteStateEditBar() {
    
}

SpriteStateEditor::SpriteStateEditor(SpriteSet *spriteSet) : UIElement() {
    this->spriteSet = spriteSet;
    
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
    
    stateSizer = new UIHSizer(10, 10, 200, true);
    addChild(stateSizer);
    stateSizer->setPosition(0, 30.0);
    
    stateTreeView = new UITreeContainer("boxIcon.png", "States", 10, 10);
    stateSizer->addLeftChild(stateTreeView);
    stateTreeView->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
    stateTreeView->getRootNode()->toggleCollapsed();
    
    stateDetails = new SpriteStateEditorDetails(spriteSet);
    stateSizer->addRightChild(stateDetails);
    
    newStateButton = new UIButton("New State", 100.0);
    addChild(newStateButton);
    newStateButton->setPosition(3.0, 3.0);
    newStateButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    selectedState = NULL;
    
    visible = false;
    enabled = false;
}

SpriteState *SpriteStateEditor::getSelectedState() {
    return selectedState;
}

SpriteStateEditorDetails *SpriteStateEditor::getDetailsEditor() {
    return stateDetails;
}

void SpriteStateEditor::setSpriteEntry(Sprite *entry) {
    
    visible = true;
    enabled = true;

    spriteSetEntry = entry;
    refreshStates();
}

void SpriteStateEditor::handleEvent(Event *event) {
    if(event->getDispatcher() == newStateButton) {
        
        String newStateName = "New State";
        if(spriteSetEntry->getNumStates() == 0) {
            newStateName = "default";
        }
        
        SpriteState *newState = new SpriteState(spriteSet, newStateName);
        spriteSetEntry->addSpriteState(newState);
        
        refreshStates();
        
    } else if(event->getDispatcher() == stateTreeView->getRootNode()) {
        selectedState = (SpriteState*) stateTreeView->getRootNode()->getSelectedNode()->getUserData();
        if(selectedState) {
            stateDetails->setSpriteState(selectedState);
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
        }
        
    }
}

void SpriteStateEditor::refreshStates() {
    stateTreeView->getRootNode()->clearTree();
    
    for(int i=0; i < spriteSetEntry->getNumStates(); i++) {
        SpriteState *state = spriteSetEntry->getState(i);
        stateTreeView->getRootNode()->addTreeChild("file.png", state->getName(), (void*) state);
    }
}

SpriteStateEditor::~SpriteStateEditor() {
    
}

void SpriteStateEditor::Resize(Number width, Number height) {
    headerBg->Resize(width, 30.0);
    stateSizer->Resize(width, height-30);
}

SpritePreview::SpritePreview(SpriteSet *spriteSet) : UIElement() {
    sprite = new SceneSpriteRewrite(spriteSet);
    addChild(sprite);
    sprite->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

SceneSpriteRewrite *SpritePreview::getSceneSprite() {
    return sprite;
}

SpritePreview::~SpritePreview() {
    
}

void SpritePreview::Resize(Number width, Number height) {
    sprite->setPosition( (width-sprite->getWidth())/ 2.0, (height-sprite->getHeight())/ 2.0);
}

PolycodeSpriteEditor::PolycodeSpriteEditor() : PolycodeEditor(true){
    mainSizer = new UIVSizer(100, 100, 200, false);
    addChild(mainSizer);
    
    topSizer = new UIHSizer(100, 100, 400, false);
    mainSizer->addTopChild(topSizer);
    
    bottomSizer = new UIHSizer(100, 100, 200, true);
    mainSizer->addBottomChild(bottomSizer);
    
    sprite = new SpriteSet("default.png");
    
    SpriteFrame frame;
    frame.coordinates = Polycode::Rectangle(0.1, 0.4, 0.41, 0.2);
    sprite->addSpriteFrame(frame);
    
    frame.coordinates = Polycode::Rectangle(0.7, 0.6, 0.2, 0.3);
    sprite->addSpriteFrame(frame);
    
    spriteSheetEditor = new SpriteSheetEditor(sprite);
    topSizer->addLeftChild(spriteSheetEditor);
    spriteSheetEditor->addEventListener(this, Event::CHANGE_EVENT);
    
    spriteBrowser = new SpriteBrowser(sprite);
    bottomSizer->addLeftChild(spriteBrowser);
    spriteBrowser->addEventListener(this, Event::CHANGE_EVENT);
    
    stateEditor = new SpriteStateEditor(sprite);
    bottomSizer->addRightChild(stateEditor);
    
    addFramesButton = stateEditor->getDetailsEditor()->getAppendFramesButton();
    addFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    spritePreview = new SpritePreview(sprite);
    topSizer->addRightChild(spritePreview);
    
    stateEditor->getDetailsEditor()->setSceneSprite(spritePreview->getSceneSprite());
    
    stateEditor->addEventListener(this, Event::CHANGE_EVENT);
    
}

void PolycodeSpriteEditor::handleEvent(Event *event) {
    if(event->getDispatcher() == spriteBrowser) {
        stateEditor->setSpriteEntry(spriteBrowser->getSelectedSpriteEntry());
        spritePreview->getSceneSprite()->setSprite(spriteBrowser->getSelectedSpriteEntry());
    } else if(event->getDispatcher() == addFramesButton) {
        SpriteState *spriteState = stateEditor->getDetailsEditor()->getSpriteState();
        spriteState->appendFrames(spriteSheetEditor->getSelectedFrameIDs());
        stateEditor->getDetailsEditor()->refreshState();
    } else if(event->getDispatcher() == stateEditor) {
        spritePreview->getSceneSprite()->setSpriteState(stateEditor->getSelectedState());
    } else if(event->getDispatcher() == spriteSheetEditor) {
        SpriteState *state = spritePreview->getSceneSprite()->getCurrentSpriteState();
        if(state) {
            state->rebuildStateMeshes();
        }
    }
}

PolycodeSpriteEditor::~PolycodeSpriteEditor() {

}

bool PolycodeSpriteEditor::openFile(OSFileEntry filePath) {
	
    PolycodeEditor::openFile(filePath);
    return true;
}

void PolycodeSpriteEditor::saveFile() {

}

void PolycodeSpriteEditor::Resize(int x, int y) {
    mainSizer->Resize(x, y);
	PolycodeEditor::Resize(x,y);
}

