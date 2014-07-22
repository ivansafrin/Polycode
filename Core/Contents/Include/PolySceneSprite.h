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

#pragma once
#include "PolyGlobals.h"
#include "PolyScenePrimitive.h"
#include "PolyCore.h"
#include "PolyResourceManager.h"
#include <vector>

namespace Polycode {

    
    class SpriteFrame {
    public:
        Polycode::Rectangle coordinates;
        Vector2 anchorPoint;
        unsigned int frameID;
    };
    
    class SpriteSet;
    
    class SpriteState {
    public:
        SpriteState(SpriteSet *spriteSet, String name);
        
        void setName(String name);
        String getName() const;
        
        void POLYIGNORE appendFrames(std::vector<unsigned int> newFrameIDs);
        
        unsigned int getNumFrameIDs();
        unsigned int getFrameIDAtIndex(unsigned int index);
        
        Mesh *getMeshForFrameIndex(unsigned int index);
        
        void insertFrame(unsigned int index, unsigned int frameID);
        
        void POLYIGNORE setNewFrameIDs(std::vector<unsigned int> newIDs);
        
        void removeFrameByIndex(unsigned int frameIndex);
        void POLYIGNORE removeFrameIndices(std::vector<unsigned int> indices);
        void clearFrames();
        
        void setPixelsPerUnit(Number ppu);
        Number getPixelsPerUnit();
        
        void rebuildStateMeshes();
        
        void setStateFPS(Number fps);
        Number getStateFPS();
        
        Vector3 getLargestFrameBoundingBox() const;
        
        void setBoundingBox(Vector2 boundingBox);
        Vector2 getBoundingBox();
        
        Vector2 getSpriteOffset();
        void setSpriteOffset(const Vector2 &offset);
        
    protected:
        
        Vector3 largestFrameBoundingBox;
        Vector2 boundingBox;
        Vector2 spriteOffset;
        Number pixelsPerUnit;
        Number stateFPS;
        SpriteSet *spriteSet;
        String name;
        std::vector<unsigned int> frameIDs;
        std::vector<Mesh*> frameMeshes;
    };
    
    class SpriteSet;
    
    class Sprite : public Resource {
    public:
        Sprite(String name);
        ~Sprite();
        
        String getName();
        void setName(String name);
        
        void addSpriteState(SpriteState *state);
        void removeSpriteState(SpriteState *state);
        
        unsigned int getNumStates();
        SpriteState *getState(unsigned int index);
        SpriteState *getStateByName(const String &name);
        
        void setParentSpritSet(SpriteSet *spriteSet);
        SpriteSet *getParentSpriteSet();
        
        
    protected:
        String name;
        SpriteSet *parentSpriteSet;
        std::vector<SpriteState*> states;
    };
    
    class SpriteSet : public ResourcePool {
    public:
        SpriteSet(String imageFileName, ResourcePool *parentPool);
        ~SpriteSet();
        
        void setTexture(Texture *texture);
        Texture *getTexture();
        Texture *loadTexture(String imageFileName);
        
        void addSpriteEntry(Sprite *newEntry);
        unsigned int getNumSpriteEntries() const;
        Sprite *getSpriteEntry(unsigned int index) const;
        void removeSprite(Sprite *sprite);
        
        void loadSpriteSet(String fileName);
        
        // frame manipulation
        void addSpriteFrame(const SpriteFrame &frame, bool assignID = true);
        unsigned int getNumFrames() const;
        SpriteFrame getSpriteFrame(unsigned int index) const;
        
        SpriteFrame getSpriteFrameByID(unsigned int frameID) const;
        void removeFrameByID(unsigned int frameID);
        
        void setSpriteFrame(const SpriteFrame &frame);
        
        void clearFrames();
        
        // automatic frame generation
        void createGridFrames(Number width, Number height, const Vector2 &defaultAnchor);
        void createFramesFromIslands(unsigned int minDistance, const Vector2 &defaultAnchor);
        
        Sprite *getSpriteByName(String spriteName);
        
    protected:
        
        unsigned int nextFrameIDIndex;
        Texture *spriteTexture;
        std::vector<SpriteFrame> frames;
        std::vector<Sprite*> sprites;
    };
    
    class SceneSprite : public SceneMesh {
    public:
        SceneSprite(SpriteSet *spriteSet);
        ~SceneSprite();
        
        Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
        void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
        
        SpriteSet *getSpriteSet();
        Sprite *getCurrentSprite();
        
        void handleEvent(Event *event);
        
        void setSpriteSet(SpriteSet *spriteSet);
        void setSpriteByName(String spriteName);
        
        void setCurrentFrame(unsigned int frameIndex);
        unsigned int getCurrentFrame();
        void Update();
        void Render();
        
        Vector3 getSpriteBoundingBox() const;
        
        void setPaused(bool val);
        bool isPaused();
        
        void setSprite(Sprite *spriteEntry);
        
        void setSpriteState(SpriteState *spriteState, unsigned int startingFrame, bool playOnce);
        
        void setSpriteStateByName(String name, unsigned int startingFrame, bool playOnce);
        
        SpriteState *getCurrentSpriteState();
        

        bool getStartOnRandomFrame();
        void setStartOnRandomFrame(bool val);
        
    protected:
        
        Vector3 spriteBoundingBox;
        bool startOnRandomFrame;
        bool playOnce;
        bool paused;
        Core *core;
        unsigned int currentFrame;
        Mesh *defaultMesh;
        Sprite *currentSprite;
        SpriteState *currentSpriteState;
        SpriteSet *spriteSet;
        Number spriteTimer;
        Number spriteTimerVal;
        
    };
}
