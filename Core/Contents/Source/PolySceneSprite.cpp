/*
 Copyright (C) 2013 by Ivan Safrin
 
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

#include "PolySceneSprite.h"
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyLogger.h"

using std::vector;
using namespace Polycode;


SceneSprite::SceneSprite(SpriteSet *spriteSet) : SceneMesh(Mesh::QUAD_MESH) {
    currentSprite = NULL;
    currentSpriteState = NULL;
    this->spriteSet = NULL;
    setSpriteSet(spriteSet);
    defaultMesh = mesh;
    currentFrame = 0;
    core = Services()->getCore();
    spriteTimer = 0.0;
    paused = false;
    playOnce = false;
    spriteTimerVal = 0.1;
    useGeometryHitDetection = false;
    ownsMesh = false;
    startOnRandomFrame = false;
}

bool SceneSprite::getStartOnRandomFrame() {
    return startOnRandomFrame;
}

void SceneSprite::setStartOnRandomFrame(bool val) {
    startOnRandomFrame = val;
    if(val && currentSpriteState) {
        currentFrame = rand() % currentSpriteState->getNumFrameIDs();
    }
}

Entity *SceneSprite::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneSprite *newSprite = new SceneSprite(spriteSet);
    newSprite->setSprite(currentSprite);
    newSprite->setSpriteState(currentSpriteState, currentFrame, playOnce);
    newSprite->setStartOnRandomFrame(startOnRandomFrame);
    applyClone(newSprite, deepClone, ignoreEditorOnly);
    return newSprite;
}

void SceneSprite::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    SceneMesh::applyClone(clone, deepClone, ignoreEditorOnly);
}


SpriteState *SceneSprite::getCurrentSpriteState() {
    return currentSpriteState;
}

SpriteSet *SceneSprite::getSpriteSet() {
    return spriteSet;
}

Sprite *SceneSprite::getCurrentSprite() {
    return currentSprite;
}

void SceneSprite::setPaused(bool val) {
    paused = val;
}

bool SceneSprite::isPaused() {
    return paused;
}

void SceneSprite::setCurrentFrame(unsigned int frameIndex) {
    currentFrame = frameIndex;
}

void SceneSprite::setSpriteByName(String spriteName) {
    Sprite *sprite = spriteSet->getSpriteByName(spriteName);
    if(sprite) {
        setSprite(sprite);
    }
}

void SceneSprite::setSprite(Sprite *spriteEntry) {
    
    if(currentSprite){
        currentSprite->removeAllHandlersForListener(this);
    }
    
    if(spriteEntry) {
        setSpriteSet(spriteEntry->getParentSpriteSet());
    }
    currentSprite = spriteEntry;
    currentSpriteState = NULL;
    
    if(currentSprite) {
        currentSprite->addEventListener(this, Event::CHANGE_EVENT);
    }
}

void SceneSprite::setSpriteSet(SpriteSet *spriteSet) {
    
    if(this->spriteSet) {
        this->spriteSet->removeAllHandlersForListener(this);
    }
    
    this->spriteSet = spriteSet;
    spriteSet->addEventListener(this, Event::CHANGE_EVENT);
    
    setTexture(spriteSet->getTexture());
    
    if(getLocalShaderOptions()) {
        getLocalShaderOptions()->clearTexture("diffuse");
        getLocalShaderOptions()->addTexture("diffuse", getTexture());
    }
    
    currentSprite = NULL;
    currentSpriteState = NULL;
}

Vector3 SceneSprite::getSpriteBoundingBox() const {
    return spriteBoundingBox;
}

void SceneSprite::handleEvent(Event *event) {
    if(event->getDispatcher() == spriteSet) {
        if(event->getEventCode() == Event::CHANGE_EVENT) {
            
            bool hasSprite = false;
            for(int i=0; i < spriteSet->getNumSpriteEntries(); i++) {
                if(currentSprite == spriteSet->getSpriteEntry(i)) {
                    hasSprite = true;
                    break;
                }
            }
            if(!hasSprite) {
                if(spriteSet->getNumSpriteEntries() > 0) {
                    setSprite(spriteSet->getSpriteEntry(0));
                } else {
                    setSprite(NULL);
                }
            }
        }
    } else if(event->getDispatcher() == currentSprite) {
        bool hasState = false;
        for(int i=0; i < currentSprite->getNumStates(); i++) {
            if(currentSprite->getState(i) == currentSpriteState) {
                hasState = true;
                break;
            }
        }
        if(!hasState) {
            if(currentSprite->getNumStates() > 0) {
                setSpriteState(currentSprite->getState(0), 0, playOnce);
            } else {
                setSpriteState(NULL, 0, playOnce);
            }
        }
    }
}

void SceneSprite::setSpriteStateByName(String name, unsigned int startingFrame, bool playOnce) {
    if(!currentSprite) {
        return;
    }
    SpriteState *spriteState = currentSprite->getStateByName(name);
    if(spriteState) {
        setSpriteState(spriteState, startingFrame, playOnce);
    }
}

void SceneSprite::setSpriteState(SpriteState *spriteState, unsigned int startingFrame, bool playOnce) {
    
    if(currentSpriteState != spriteState || playOnce) {
        currentFrame = startingFrame;
    }
    
    currentSpriteState = spriteState;
    
    if(!currentSpriteState) {
        return;
    }
    
    Vector2 bBox = currentSpriteState->getBoundingBox();
    setLocalBoundingBox(bBox.x / currentSpriteState->getPixelsPerUnit(), bBox.y / currentSpriteState->getPixelsPerUnit(), 0.001);
    
    spriteBoundingBox = currentSpriteState->getLargestFrameBoundingBox();
    
    this->playOnce = playOnce;
    
}

void SceneSprite::Update() {
    
    if(!currentSprite || !currentSpriteState) {
        return;
    }
    
    Vector2 bBox = currentSpriteState->getBoundingBox();
    setLocalBoundingBox(bBox.x / currentSpriteState->getPixelsPerUnit(), bBox.y / currentSpriteState->getPixelsPerUnit(), 0.001);
    
    spriteBoundingBox = currentSpriteState->getLargestFrameBoundingBox();
    
    setTexture(spriteSet->getTexture());
    
    if(paused) {
        return;
    }
    
    spriteTimer += core->getElapsed();
    
    if(spriteTimer > 1.0/currentSpriteState->getStateFPS()) {
        spriteTimer = 0.0;
        currentFrame++;
        if(currentFrame >= currentSpriteState->getNumFrameIDs()) {
            if(playOnce) {
                currentFrame = currentSpriteState->getNumFrameIDs()-1;
            } else {
                currentFrame = 0;
            }
        }
    }
}

unsigned int SceneSprite::getCurrentFrame() {
    return currentFrame;
}

void SceneSprite::Render() {
    
    if(!currentSprite || !currentSpriteState) {
        return;
    }
    
    Mesh *stateMesh = currentSpriteState->getMeshForFrameIndex(currentFrame);
    if(stateMesh) {
        this->mesh = stateMesh;
        useVertexBuffer = false;
    } else {
        this->mesh = defaultMesh;
        useVertexBuffer = false;
    }
    
    SceneMesh::Render();
}

SceneSprite::~SceneSprite() {
    
}

SpriteState::SpriteState(SpriteSet *spriteSet, String name) {
    this->spriteSet = spriteSet;
    this->name = name;
    stateFPS = 60.0;
    pixelsPerUnit = 1.0;
}

void SpriteState::setBoundingBox(Vector2 boundingBox) {
    this->boundingBox = boundingBox;
    rebuildStateMeshes();
}

void SpriteState::clearFrames() {
    frameIDs.clear();
    rebuildStateMeshes();
}

Vector2 SpriteState::getBoundingBox() {
    return boundingBox;
}

Vector2 SpriteState::getSpriteOffset() {
    return spriteOffset;
}

void SpriteState::setSpriteOffset(const Vector2 &offset) {
    spriteOffset = offset;
    rebuildStateMeshes();
}


void SpriteState::setPixelsPerUnit(Number ppu) {
    pixelsPerUnit = ppu;
    rebuildStateMeshes();
}

Number SpriteState::getPixelsPerUnit() {
    return pixelsPerUnit;
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

void SpriteState::setNewFrameIDs(std::vector<unsigned int> newIDs) {
    frameIDs = newIDs;
    rebuildStateMeshes();
}

Vector3 SpriteState::getLargestFrameBoundingBox() const {
    return largestFrameBoundingBox;
}

void SpriteState::insertFrame(unsigned int index, unsigned int frameID) {
    if(index < frameIDs.size()) {
        frameIDs.insert(frameIDs.begin()+index, frameID);
    }
    rebuildStateMeshes();
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
    
    largestFrameBoundingBox = Vector3();
    
    for(int i=0; i < frameIDs.size(); i++) {
        Mesh *frameMesh = new Mesh(Mesh::QUAD_MESH);
        SpriteFrame frame = spriteSet->getSpriteFrameByID(frameIDs[i]);
        
        frameMesh->indexedMesh = true;
        
        Number aspectRatio = frame.coordinates.w / frame.coordinates.h;
        Number textureAspectRatio = ((Number)spriteSet->getTexture()->getWidth()) / ((Number)spriteSet->getTexture()->getHeight());
        
        
        Number frameHeight = frame.coordinates.h * ((Number)spriteSet->getTexture()->getHeight()) / pixelsPerUnit;
        
        Number frameWidth = frameHeight * aspectRatio * textureAspectRatio;
        
        
        
        Vector2 meshOffset;
        meshOffset.x = boundingBox.x * spriteOffset.x / pixelsPerUnit;
        meshOffset.y = boundingBox.y * spriteOffset.y / pixelsPerUnit;
        
        meshOffset.x -= frameWidth * frame.anchorPoint.x;
        meshOffset.y += frameHeight * frame.anchorPoint.y;
        
        frameMesh->addVertexWithUVAndNormal(meshOffset.x+-frameWidth*0.5, meshOffset.y+frameHeight*0.5, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y, 0.0, 0.0, 1.0);
        frameMesh->addVertexWithUVAndNormal(meshOffset.x+-frameWidth*0.5, meshOffset.y+frameHeight*0.5-frameHeight, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y  - frame.coordinates.h, 0.0, 0.0, 1.0);
        frameMesh->addVertexWithUVAndNormal(meshOffset.x+-frameWidth*0.5+frameWidth, meshOffset.y+frameHeight*0.5-frameHeight, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0- frame.coordinates.y  - frame.coordinates.h, 0.0, 0.0, 1.0);
        frameMesh->addVertexWithUVAndNormal(meshOffset.x+-frameWidth*0.5+frameWidth, meshOffset.y+frameHeight*0.5, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0-frame.coordinates.y, 0.0, 0.0, 1.0);
        
        
        for(int j=0; j < 4; j++) {

            Vector3 vertex(frameMesh->vertexPositionArray.data[j], frameMesh->vertexPositionArray.data[j+1], frameMesh->vertexPositionArray.data[j+2]);
            
            Number val = fabs(vertex.x);
            if(val > largestFrameBoundingBox.x) {
                largestFrameBoundingBox.x = val;
            }
            val = fabs(vertex.y);
            if(val > largestFrameBoundingBox.y) {
                largestFrameBoundingBox.y = val;
            }
            val = fabs(vertex.z);
            if(val > largestFrameBoundingBox.z) {
                largestFrameBoundingBox.z = val;
            }
        }
        frameMesh->addIndexedFace(0,1);
        frameMesh->addIndexedFace(1,2);
        frameMesh->addIndexedFace(2,3);
        frameMesh->addIndexedFace(3,0);
        
        frameMeshes.push_back(frameMesh);
    }
    
    largestFrameBoundingBox = largestFrameBoundingBox * 2.0;
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

SpriteState *Sprite::getStateByName(const String &name) {
    for(int i=0; i < states.size(); i++) {
        if(states[i]->getName() == name) {
            return states[i];
        }
    }
    return NULL;
}

void Sprite::addSpriteState(SpriteState *state) {
    states.push_back(state);
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

Sprite::Sprite(String name) : Resource(Resource::RESOURCE_SPRITE){
    this->name = name;
    this->setResourceName(name);
}

void Sprite::setParentSpritSet(SpriteSet *spriteSet) {
    parentSpriteSet = spriteSet;
}

SpriteSet *Sprite::getParentSpriteSet() {
    return parentSpriteSet;
}

void Sprite::removeSpriteState(SpriteState *state) {
    for(int i=0; i < states.size(); i++) {
        if(states[i] == state) {
            states.erase(states.begin() + i);
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
            return;
        }
    }
}

Sprite::~Sprite() {
    for(int i=0; i < states.size(); i++) {
        delete states[i];
    }
}

String Sprite::getName() {
    return name;
}

void Sprite::setName(String name) {
    this->name = name;
}


SpriteSet::SpriteSet(const String &fileName, ResourcePool *parentPool) : ResourcePool(fileName, parentPool) {
    nextFrameIDIndex = 0;
    loadSpriteSet(fileName);
}

void SpriteSet::loadSpriteSet(String fileName) {
	Object loadObject;
	if(!loadObject.loadFromBinary(fileName)) {
        if(!loadObject.loadFromXML(fileName)) {
            Logger::log("Error loading sprite sheet: %s.\n", fileName.c_str());
            return;
        }
	}
    
    ObjectEntry *spriteSheetEntry = loadObject.root["sprite_sheet"];
    if(spriteSheetEntry) {
        ObjectEntry *fileNameEntry = (*spriteSheetEntry)["fileName"];
        if(fileNameEntry) {
            loadTexture(fileNameEntry->stringVal);
        }
        
        ObjectEntry *framesEntry = (*spriteSheetEntry)["frames"];
        if(framesEntry) {
            for(int i=0; i < framesEntry->length; i++) {
                ObjectEntry *frameEntry = (*framesEntry)[i];
                
                if(frameEntry) {
                    SpriteFrame frame;
                    
                    ObjectEntry *idEntry = (*frameEntry)["id"];
                    if(idEntry) {
                        frame.frameID = idEntry->intVal;
                    }
                    
                    ObjectEntry *xEntry = (*frameEntry)["x"];
                    if(xEntry) {
                        frame.coordinates.x = xEntry->NumberVal;
                    }
                    ObjectEntry *yEntry = (*frameEntry)["y"];
                    if(yEntry) {
                        frame.coordinates.y = yEntry->NumberVal;
                    }
                    ObjectEntry *wEntry = (*frameEntry)["w"];
                    if(wEntry) {
                        frame.coordinates.w = wEntry->NumberVal;
                    }
                    ObjectEntry *hEntry = (*frameEntry)["h"];
                    if(hEntry) {
                        frame.coordinates.h = hEntry->NumberVal;
                    }
                    ObjectEntry *axEntry = (*frameEntry)["ax"];
                    if(axEntry) {
                        frame.anchorPoint.x = axEntry->NumberVal;
                    }
                    ObjectEntry *ayEntry = (*frameEntry)["ay"];
                    if(ayEntry) {
                        frame.anchorPoint.y = ayEntry->NumberVal;
                    }
                    
                    addSpriteFrame(frame, false);
                }
                
            }
        }
        
    } else {
        return;
    }
    
    ObjectEntry *spritesEntry = loadObject.root["sprites"];
    if(spritesEntry) {
        for(int i=0; i < spritesEntry->length; i++) {
            ObjectEntry *spriteEntry = (*spritesEntry)[i];
            if(spriteEntry) {
                ObjectEntry *nameEntry = (*spriteEntry)["name"];
                String spriteName;
                if(nameEntry) {
                    spriteName = nameEntry->stringVal;
                }
                Sprite *newSprite = new Sprite(spriteName);
                addSpriteEntry(newSprite);
                
                ObjectEntry *statesEntry = (*spriteEntry)["states"];
                
                if(statesEntry) {
                    for(int j=0; j < statesEntry->length; j++) {
                        ObjectEntry *stateEntry = (*statesEntry)[j];
                        if(stateEntry) {
                            SpriteState *newState = new SpriteState(this, "");
                            
                            ObjectEntry *nameEntry = (*stateEntry)["name"];
                            if(nameEntry) {
                                newState->setName(nameEntry->stringVal);
                            }
                            
                            ObjectEntry *fpsEntry = (*stateEntry)["fps"];
                            if(fpsEntry) {
                                newState->setStateFPS(fpsEntry->NumberVal);
                            }
                            
                            ObjectEntry *scaleEntry = (*stateEntry)["scale"];
                            if(scaleEntry) {
                                newState->setPixelsPerUnit(scaleEntry->NumberVal);
                            }
                            
                            ObjectEntry *widthEntry = (*stateEntry)["width"];
                            ObjectEntry *heightEntry = (*stateEntry)["height"];
                            if(widthEntry && heightEntry) {
                                newState->setBoundingBox(Vector2(widthEntry->NumberVal, heightEntry->NumberVal));
                            }
                            
                            ObjectEntry *xOffsetEntry = (*stateEntry)["offset_x"];
                            ObjectEntry *yOffsetEntry = (*stateEntry)["offset_y"];
                            if(xOffsetEntry && yOffsetEntry) {
                                newState->setSpriteOffset(Vector2(xOffsetEntry->NumberVal, yOffsetEntry->NumberVal));
                            }
                            
                            ObjectEntry *frameIDsEntry = (*stateEntry)["frame_ids"];
                            
                            if(frameIDsEntry) {
                                std::vector<String> frameIDs = frameIDsEntry->stringVal.split(",");
                                
                                std::vector<unsigned int> frameIDInts;
                                for(int f=0; f < frameIDs.size(); f++) {
                                    frameIDInts.push_back(frameIDs[f].toInteger());
                                }
                                
                                newState->appendFrames(frameIDInts);
                            }
                            
                            newSprite->addSpriteState(newState);
                        }
                    }
                }
            }
        }
    }
}

void SpriteSet::removeFrameByID(unsigned int frameID) {
    for(int i=0; i < frames.size(); i++) {
        if(frames[i].frameID == frameID) {
            frames.erase(frames.begin() + i);
            return;
        }
    }
}

void SpriteSet::removeSprite(Sprite *sprite) {
    for(int i=0; i < sprites.size(); i++) {
        if(sprites[i] == sprite) {
            removeResource(sprites[i]);
            sprites.erase(sprites.begin()+i);
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
            return;
        }
    }
}

Sprite *SpriteSet::getSpriteByName(String spriteName) {
    for(int i=0; i < sprites.size(); i++) {
        if(sprites[i]->getName() == spriteName) {
            return sprites[i];
        }
    }
    return NULL;
}

Texture *SpriteSet::loadTexture(String imageFileName) {
    Texture *spriteTexture = Services()->getMaterialManager()->createTextureFromFile(imageFileName, true, Services()->getMaterialManager()->mipmapsDefault);
    setTexture(spriteTexture);
    return spriteTexture;
}

void SpriteSet::addSpriteFrame(const SpriteFrame &frame, bool assignID) {
    
    // do not add existing frames
    for(int i=0; i < frames.size(); i++) {
        SpriteFrame existingFrame = frames[i];
        
        if(existingFrame.coordinates == frame.coordinates) {
            return;
        }
        
    }
    
    frames.push_back(frame);
    if(assignID) {
        frames[frames.size()-1].frameID = nextFrameIDIndex;
        nextFrameIDIndex++;
    } else {
        nextFrameIDIndex = frame.frameID + 1;
    }
    
}

void SpriteSet::setSpriteFrame(const SpriteFrame &frame) {
    for(int i=0 ;i < frames.size(); i++) {
        if(frames[i].frameID == frame.frameID) {
            frames[i].coordinates = frame.coordinates;
            frames[i].anchorPoint = frame.anchorPoint;
            return;
        }
    }
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
    addResource(newEntry);
    newEntry->setParentSpritSet(this);
    sprites.push_back(newEntry);
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
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

void SpriteSet::createGridFrames(unsigned int xCount, unsigned int yCount, const Vector2 &defaultAnchor) {
    
    Number frameWidth = 1.0/(Number)xCount;
    Number frameHeight = 1.0/(Number)yCount;
    
    for(int y = 0; y < yCount; y++) {
        for(Number x = 0; x < xCount; x++) {
            SpriteFrame frame;
            frame.coordinates = Polycode::Rectangle(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
            frame.anchorPoint = defaultAnchor;
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

void SpriteSet::createFramesFromIslands(unsigned int minDistance, const Vector2 &defaultAnchor) {
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
        
        frame.anchorPoint = defaultAnchor;
        
        addSpriteFrame(frame);
    }
    
    delete image;
}
