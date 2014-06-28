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


SceneSpriteRewrite::SceneSpriteRewrite(String imageFileName) : SceneMesh(Mesh::QUAD_MESH) {
    Texture *spriteTexture = Services()->getMaterialManager()->createTextureFromFile(imageFileName, true, Services()->getMaterialManager()->mipmapsDefault);
    setTexture(spriteTexture);
}

void SceneSpriteRewrite::addSpriteFrame(const SpriteFrame &frame) {
    frames.push_back(frame);
}

unsigned int SceneSpriteRewrite::getNumFrames() const {
    return frames.size();
}

SpriteFrame SceneSpriteRewrite::getSpriteFrame(unsigned int index) const {
    if(index < frames.size()) {
        return frames[index];
    } else {
        return SpriteFrame();
    }
}

SceneSpriteRewrite::~SceneSpriteRewrite() {
    
}

void SceneSpriteRewrite::clearFrames() {
    frames.clear();
}

void SceneSpriteRewrite::createGridFrames(Number width, Number height) {
    
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

void SceneSpriteRewrite::createFramesFromIslands(unsigned int minDistance) {
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

SpriteSheetEditor::SpriteSheetEditor(SceneSpriteRewrite *sprite) : UIElement() {
    
    this->sprite = sprite;
    
    enableScissor = true;
    
    previewBg = new UIImage("main/grid_dark.png");
    addChild(previewBg);
    
    previewImage = new UIRect(10, 10);
    previewImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    addChild(previewImage);
    
    frameVisualizerMesh = new SceneMesh(Mesh::LINE_MESH);
    frameVisualizerMesh->setColor(1.0, 1.0, 1.0, 1.0);
    addChild(frameVisualizerMesh);
    frameVisualizerMesh->setAnchorPoint(-1.0, -1.0, 0.0);
    
    frameVisualizerMesh->loadTexture("main/stipple.png");
    
    frameVisualizerMesh->lineWidth = 1; //CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX();
    
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
    
    generateFramesButton = new UIButton("Generate frames", 120);
    bottomMenu->addChild(generateFramesButton);
    generateFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
    generateFramesButton->setPosition(130.0, 3.0);
    
    generateTypeDropdown = new UIComboBox(globalMenu, 120);
    bottomMenu->addChild(generateTypeDropdown);
    generateTypeDropdown->setPosition(260, 3.0);
    
    generateTypeDropdown->addComboItem("Uniform grid");
    generateTypeDropdown->addComboItem("Detect islands");
    
    generateTypeDropdown->setSelectedIndex(0);
    
    uniformGridWidthInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(uniformGridWidthInput);
    uniformGridWidthInput->setPosition(385, 3);
    uniformGridWidthInput->setText("32");
    uniformGridWidthInput->setNumberOnly(true);

    uniformGridHeightInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(uniformGridHeightInput);
    uniformGridHeightInput->setPosition(430, 3);
    uniformGridHeightInput->setText("32");
    uniformGridHeightInput->setNumberOnly(true);
    
    minimumDistanceInput = new UITextInput(false, 30, 12);
    bottomMenu->addChild(minimumDistanceInput);
    minimumDistanceInput->setPosition(475, 3);
    minimumDistanceInput->setText("0");
    minimumDistanceInput->setNumberOnly(true);
}

void SpriteSheetEditor::Update() {
    Mesh *mesh = frameVisualizerMesh->getMesh();

    mesh->clearMesh();
    mesh->indexedMesh = true;
    
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
    }
    
    mesh->dirtyArrays();
}

void SpriteSheetEditor::handleEvent(Event *event) {
    if(event->getDispatcher() == changeImageButton) {
        globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
        std::vector<String> extensions;
        extensions.push_back("png");
        globalFrame->showAssetBrowser(extensions);
    } else if(event->getDispatcher() == generateFramesButton) {
        sprite->clearFrames();
        
        if(generateTypeDropdown->getSelectedIndex() == 0) {
            Number frameWidth = uniformGridWidthInput->getText().toNumber() / ((Number)sprite->getTexture()->getWidth());
            Number frameHeight = uniformGridHeightInput->getText().toNumber() / ((Number)sprite->getTexture()->getHeight());
            sprite->createGridFrames(frameWidth, frameHeight);
        } else {
            sprite->createFramesFromIslands(minimumDistanceInput->getText().toInteger());
        }
    } else if(event->getDispatcher() == globalFrame->assetBrowser) {
        String newImagePath = globalFrame->assetBrowser->getSelectedAssetPath();
        
        sprite->loadTexture(globalFrame->assetBrowser->getSelectedAssetPath());
        previewImage->setTexture(sprite->getTexture());
        
        globalFrame->assetBrowser->removeAllHandlersForListener(this);
        globalFrame->hideModal();
        
        Resize(getWidth(), getHeight());
        
    }
}

SpriteSheetEditor::~SpriteSheetEditor() {
    
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

    
    previewImage->setPosition((width-previewImage->getWidth())/ 2.0, (height-previewImage->getHeight()-30.0)/2.0);
    
    frameVisualizerMesh->setPosition(previewImage->getPosition());
    frameVisualizerMesh->setScale(previewImage->getWidth(), previewImage->getHeight(), 1.0);
    
    bottomMenuRect->Resize(width, 30.0);
    bottomMenu->setPosition(0.0, height-30.0);
    
    UIElement::Resize(width, height);
}

PolycodeSpriteEditor::PolycodeSpriteEditor() : PolycodeEditor(true){
    mainSizer = new UIVSizer(100, 100, 200, false);
    addChild(mainSizer);
    
    topSizer = new UIHSizer(100, 100, 400, false);
    mainSizer->addTopChild(topSizer);
    
    sprite = new SceneSpriteRewrite("default.png");
    
    SpriteFrame frame;
    frame.coordinates = Polycode::Rectangle(0.1, 0.4, 0.41, 0.2);
    sprite->addSpriteFrame(frame);
    
    frame.coordinates = Polycode::Rectangle(0.7, 0.6, 0.2, 0.3);
    sprite->addSpriteFrame(frame);
    
    spriteSheetEditor = new SpriteSheetEditor(sprite);
    topSizer->addLeftChild(spriteSheetEditor);
}

void PolycodeSpriteEditor::handleEvent(Event *event) {

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

