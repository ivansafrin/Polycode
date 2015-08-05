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
#include "PolyEntity.h"
#include "PolyObject.h"
#include "PolyParticleEmitter.h"
#include "PolyScenePrimitive.h"
#include "PolyResource.h"
#include "PolySceneSprite.h"
#include "PolyBezierCurve.h"
#include "PolySceneLine.h"
#include "PolyScene.h"
#include "PolySound.h"

namespace Polycode {

class SceneEntityInstanceResourceEntry;
    class SceneEntityInstanceLayer;
    
class SceneEntityInstance : public Entity {
	public:
    
        SceneEntityInstance(Scene *parentScene, const String& fileName);
		explicit SceneEntityInstance(Scene *parentScene);
		
		static SceneEntityInstance *BlankSceneEntityInstance(Scene *parentScene);

		virtual ~SceneEntityInstance();
	
		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
		
		void reloadEntityInstance();

		void clearInstance();

		void parseObjectIntoCurve(ObjectEntry *entry, BezierCurve *curve);
		Entity *loadObjectEntryIntoEntity(ObjectEntry *entry, Entity *targetEntity = NULL, int entityFileVersion = 1);
		bool loadFromFile(const String& fileName);
        void applySceneMesh(ObjectEntry *entry, SceneMesh *sceneMesh);
		
        void linkResourcePool(ResourcePool *pool);
        unsigned int getNumLinkedResourePools();
        ResourcePool *getLinkedResourcePoolAtIndex(unsigned int index);
    
        void unlinkResourcePool(ResourcePool *pool);
    
		SceneEntityInstanceResourceEntry *getResourceEntry();
    
        ResourcePool *getTopLevelResourcePool();

        bool hasLayerID(unsigned char layerID) const;
        unsigned int getNumLayers() const;
        SceneEntityInstanceLayer *getLayerAtIndex(unsigned int index) const;
        void removeLayer(SceneEntityInstanceLayer *layer);
    
    
        SceneEntityInstanceLayer *createNewLayer(String name);
		
		String getFileName() const;
		bool cloneUsingReload;

		String fileName;
		
	protected:
		
        std::vector<SceneEntityInstanceLayer*> layers;
    
        void rebuildResourceLinks();
    
        ResourcePool *topLevelResourcePool;
        std::vector<ResourcePool*> resourcePools;
        Scene *parentScene;
		SceneEntityInstanceResourceEntry *resourceEntry;
		
};
    
class SceneEntityInstanceLayer {
    public:
        SceneEntityInstanceLayer(SceneEntityInstance *instance,String name);
    
        void setLayerVisibility(bool val);
    
        String name;
        unsigned char layerID;
        bool visible;
        SceneEntityInstance *instance;
};


class SceneEntityInstanceResourceEntry : public Resource {
	public:
		SceneEntityInstanceResourceEntry(SceneEntityInstance *instance);
		virtual ~SceneEntityInstanceResourceEntry();
		
		SceneEntityInstance *getInstance();
		void reloadResource();
		
	protected:
		SceneEntityInstance* instance;
};


}