/*
Copyright (C) 2011 by Ivan Safrin

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
#include "PolyVector2.h"
#include "PolyEventDispatcher.h"
#include <vector>

namespace Polycode {

	class InputEvent;
	class Renderer;
	class Material;
	class Texture;
	class ScreenEntity;
	class ShaderBinding;

	/**
	* 2D rendering base. The Screen is the container for all 2D rendering in Polycode. Screens are automatically rendered and need only be instantiated to immediately add themselves to the rendering pipeline. Each screen has a root entity.
	*/	
	class _PolyExport Screen : public EventDispatcher {
	public:
		
		/**
		* Default constructor.
		*/
		Screen();
		virtual ~Screen();
		
		/**
		* Adds a ScreenEntity to the 2d rendering pipeline.
		* @param newEntity Entity to add.
		* @return Returns the same entity for convenience.
		*/		
		ScreenEntity* addChild(ScreenEntity *newEntity);

		/**
		* Adds a ScreenEntity to the 2d rendering pipeline.
		* @param newEntity Entity to add.
		* @return Returns the same entity for convenience.
		*/		
		ScreenEntity* addEntity(ScreenEntity *newEntity);
		
		/**
		* Removes a ScreenEntity from the screen's render list.
		* @param entityToRemove Entity to remove.
		* @return Returns the same entity for convenience.
		*/				
		virtual ScreenEntity* removeChild(ScreenEntity *entityToRemove);
		
		/**
		* Sets the screen's offset. You can also translate the root entity to do the same thing.
		* @param x New x offset.
		* @param y New y offset.		
		*/						
		void setScreenOffset(Number x, Number y);
		
		/** 
		* Returns the screen's offset.
		* @return The screen's offset as 2d vector.
		*/		
		Vector2 getScreenOffset() const;
				
		virtual void Shutdown();
		virtual void Update();
		
		/**
		* Returns the entity at specified point. This is a deprecated method which does not take rotation or scale into account. Please use the 2d physics and collision module for proper collision detection.
		*/
		ScreenEntity *getEntityAt(Number x, Number y);

		void Render();
		void setRenderer(Renderer *renderer);

		/**
		* Changes the screen's coordinate system. By default, screens' dimensions are in pixels. To accommodate changing resolutions without changing the dimensions of a screen's content, you can call this method to make it use normalized coordinates.
		* @param newVal If true, the screen will use normalized coordinates, if false, it will use pixel coordinates.
		* @param yCoordinateSize The normalized size of the screen vertically. The horizontal size will be calculated based on the resolution.
		*/		
		void setNormalizedCoordinates(bool newVal, Number yCoordinateSize = 1.0f);
		
		/**
		* Sets the shader material to use for post processing on this screen.
		* @param shaderName Name of the shader material to use.
		*/				
		void setScreenShader(const String& shaderName);
		
		/**
		* Removes the current screen shader for this screen.
		*/
		void clearScreenShader();
		
		void handleEvent(Event *event);
		int getHighestZIndex() const;
		
		/**
		* Sorts the screen's children based on their z index.
		*/ 
		void sortChildren();
		
		static bool cmpZindex(const ScreenEntity *left, const ScreenEntity *right);
		
		void handleInputEvent(InputEvent *inputEvent);
		
		/**
		* Returns true if the screen has a shader applied to it.
		*/				
		bool hasFilterShader() const;
		void drawFilter();
		
		bool usesNormalizedCoordinates() const { return useNormalizedCoordinates; }
		Number getYCoordinateSize() const { return yCoordinateSize; }
		
		/**
		* Returns the root entity. The root entity can be used to transform the entire screen and change its color.
		* @return The root entity.
		*/		
		ScreenEntity *getRootEntity() { return rootEntity; }
		
		int getNumChildren() { return children.size(); }
		ScreenEntity *getChild(int index) { return children[index]; }
		
		/**
		* If set to false, the screen will not be rendered or updated.
		*/
		bool enabled;
		
		/**
		* Returns the local shader options for the camera post processing material.
		*/				
		const std::vector<ShaderBinding*>& getLocalShaderOptions() const { return localShaderOptions; }
		
		/**
		* Returns the shader material applied to the camera.
		*/					
		Material *getScreenShaderMaterial() const { return filterShaderMaterial; }
		
		/**
		* If set to true, will process touch events as mouse clicks. Defaults to false.
		*/		
		bool processTouchEventsAsMouse;
		
		/**
		* If ownsChildren is set to true, the scene will delete its children upon destruction (defaults to false).
		*/
		bool ownsChildren;		
		
		/**
		* If true, children snap to pixels by default. You can still change it per entity. Defaults to false.
		*/		
		bool snapToPixelsByDefault;
		
	protected:
		
		bool useNormalizedCoordinates;
		Number yCoordinateSize;		
		
		ScreenEntity *rootEntity;
		
		Vector2 offset;
		Renderer *renderer;
		ScreenEntity *focusChild;
		std::vector <ScreenEntity*> children;
		
		Material *filterShaderMaterial;			
		Texture *originalSceneTexture;				
		std::vector<ShaderBinding*> localShaderOptions;
		bool _hasFilterShader;
	};
}
