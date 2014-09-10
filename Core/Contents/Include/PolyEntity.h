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
#include "PolyString.h"
#include "PolyMatrix4.h"
#include "PolyVector2.h"
#include "PolyQuaternion.h"
#include "PolyColor.h"
#include "PolyRectangle.h"
#include "PolyRay.h"
#include "PolyEventDispatcher.h"
#include <vector>

namespace Polycode {

	class Renderer;

	class _PolyExport MouseEventResult {
		public:
			bool hit;
			bool blocked;
	};

	class _PolyExport EntityProp {
	public:
		String propName;
		String propValue;		
	};
    
    class _PolyExport AABB {
        public:
            Vector3 min;
            Vector3 max;
    };

	class _PolyExport Rotation {
		public:
			Rotation();
						
			Number pitch;
			Number yaw;			
			Number roll;		
			
			inline bool operator == ( const Rotation& r2)  {
				return (r2.pitch == pitch && r2.roll == roll && r2.yaw == yaw);
			}		

			inline bool operator != ( const Rotation& r2)  {
				return (r2.pitch != pitch || r2.yaw != yaw || r2.roll != roll);
			}				
			
	};

	/**
	* Base class for both 2D and 3D objects in Polycode. It provides position and color transformations as well as hierarchy for all Polycode objects.
	*/
	class _PolyExport Entity : public EventDispatcher {
		public:
			Entity();
			
			Entity(Number width, Number height, Number depth = 0.01);	
			
			virtual ~Entity();


			void initEntity();
			/**
			* Main render method. Override this to do your own drawing.
			*/
			virtual void Render(){};
			/**
			* Main update method. Override this to do your updates before the render cycle.
			*/			
			virtual void Update(){};			
			virtual void fixedUpdate(){};
        
			void transformAndRender();		

			void renderChildren();					
		
			
			/**
 			* Clones the entity, return an exact copy. This method must be implemented in an Entity subclass for you to be able to clone it.
 			* @param deepClone If true, perform a deep clone, cloning all the children.
 			* @param ignoreEditorOnly If true, ignore all child entities where editorOnly is set to true (will still clone the entity you call Clone() on even if its editorOnly flag is set to true.
 			* @return The clone of the entity.
 			*/
			virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;

			/**
 			* This method must be implemented by all subclasses implementing Clone.
 			*/
			virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
		
		
			// ----------------------------------------------------------------------------------------------------------------
			/** @name Matrix operations.
			*  These methods operate directly on the entity's matrix.
			*/
			//@{
									
			/** 
			* Sets the state of the dirty matrix flag. The dirty matrix flag gets set automatically when a transformation is applied to the entity and the transfrom matrix needs to be rebuilt. This method is provided to manually override that flag.
			@param val New value of the dirty matrix flag.
			*/
			void dirtyMatrix(bool val);
			
			/**
			* Forces the transformation matrix to be rebuilt.
			*/
			void rebuildTransformMatrix();

			/**
			* Forces the matrix to be rebuilt if the matrix flag is dirty. This is also called on all of the entity's children.
			*/
			void updateEntityMatrix();
			
			/**
			* Returns the entity's transform matrix.
			@return Transform matrix.
			*/
			const Matrix4& getTransformMatrix() const;
			
			/** 
			* Returns the entity's matrix multiplied by its parent's concatenated matrix. This, in effect, returns the entity's actual world transformation.
			@return Entity's concatenated matrix.
			*/
			Matrix4 getConcatenatedMatrix();
			
            /**
             * Returns the concatenated matrix up to the specified parent entity.
             * @param relativeEntity Parent entity, relative to which to return the transform matrix.
             */
			Matrix4 getConcatenatedMatrixRelativeTo(Entity *relativeEntity);
			
            /**
             * Returns the concatenated matrix, multiplied by the entity's anchor adjustment.
             * @see setAnchorPoint
             */
			Matrix4 getAnchorAdjustedMatrix();
			
			/** 
			* Returns Same as getConcatenatedMatrix(), but contains only roll information for rotation. Used internally for billboards.
			@return Entity's concatenated roll matrix.
			@see getConcatenatedMatrix()
			*/			
			Matrix4 getConcatenatedRollMatrix() const;
						
			/**
			* Sets the transform matrix directly, without setting all of the individual transfrom properties of the entity.
			@param matrix 4x4 transform matrix to apply.
			*/						
			void setTransformByMatrixPure(const Matrix4& matrix);
			
			/** Returns the matrix for the entity looking at a location based on a location and an up vector.
			* @param loc Location to look at.
			* @param upVector Up vector.
			* @return The resulting lookAt matrix.
			*/
			Matrix4 getLookAtMatrix(const Vector3 &loc, const Vector3 &upVector = Vector3(0,1,0));

			
			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
			/** @name Hierarchy operations.
			*  These methods add and remove entities to and from each other.
			*/
			//@{

			/**
			* Adds another entity as a child. The children inherit the parent's transforms.
			@param newChild The entity to be added.
			*/					
			virtual void addChild(Entity *newChild);
			
			/**
			* Removes an entity from the entity's children.
			@param entityToRemove Entity to be removed.
			*/
			virtual void removeChild(Entity *entityToRemove);

            /**
             * Moves the specified child one position up the render list.
             */
			void moveChildUp(Entity *child);
        
            /**
             * Moves the specified child one position down the render list.
             */
			void moveChildDown(Entity *child);
        
            /**
             * Moves the specified child up to the top of the render list.
             */
			void moveChildTop(Entity *child);
        
            /**
             * Moves the specified child up to the bottom of the render list.
             */
			void moveChildBottom(Entity *child);

			/**
			* Manually sets the entity's parent. This method does not add the entity to the parent and should not be called manually.
			@param entity Parent entity.
			*/		
			void setParentEntity(Entity *entity);
			
			/** 
			* Returns the parent entity of the entity.
			@return Parent entity of this entity.
			*/
			Entity *getParentEntity() const;
			
			/**
			* Returns the number of child entities belonging to this entity.
			* @return Number of child entities.
			*/
			unsigned int getNumChildren();
			
			/**
			* Returns the child entity at specified index.
			* @param index Index to return entity at.
			* @return Child entity at specified index or NULL of index out of range.
			*/			
			Entity *getChildAtIndex(unsigned int index);
			
			/**
			* If set to true, will automatically delete children upon destruction. (defaults to false).
			*/ 
			bool ownsChildren;										
			
			/**
             * Sets the ownsChildren flag for this entity and recursively for all its child entities.
             * @see ownsChildren
             */
			void setOwnsChildrenRecursive(bool val);
			//@}
			// ----------------------------------------------------------------------------------------------------------------
				

			/** @name Transform operations.
			*  These methods apply various transformations to the entity.
			*/
			//@{			

			/**
			* Returns the entity's position.
			@return Entity's position as a vector.
			*/			
			Vector3 getPosition() const;
			
            /**
             * Returns the entity's position as a Vector2
             */
			Vector2 getPosition2D() const;
			
			/**
			* Returns the entity's position added to the combined position of its parent. This method is here only for convenience of calculating certain properties and should not be used to get an entity's actual position in the world. To get the actual world position of the entity, use the entity's concatendated matrix.
			@see getConcatenatedMatrix()
			@return Entity's position as a vector.
			*/			
			Vector3 getCombinedPosition() const;

			/**
			* Sets the entity's position.
			@param x X-axis value.
			@param y Y-axis value.
			@param z Z-axis value.						
			*/						
			void setPosition(Number x, Number y, Number z=0.0);
			
			/**
			* Sets the entity's position with a vector.
			@param posVec New position as a vector.
			*/								
			void setPosition(const Vector3 &posVec);
			
			/**
			* Returns the entity's position on the X axis.
			@param x X-axis value.
			*/									
			void setPositionX(Number x);

			/**
			* Returns the entity's position on the Y axis.
			@param y Y-axis value.
			*/												
			void setPositionY(Number y);
				
			/**
			* Translates the entity relative to its current position.
			@param x X-axis value.
			@param y Y-axis value.
			@param z Z-axis value.						
			*/						
			void Translate(Number x, Number y, Number z=0.0);
			
			/**
			* Translates the entity relative to its current position with a vector.
			@param tVec New position as a vector.
			*/											
			void Translate(const Vector3 &tVec);

			/**
			* Returns the entity's position on the Z axis.
			@param z Z-axis value.
			*/															
			void setPositionZ(Number z);

			/**
			* Returns the entity's scale on the X axis.
			@param x X-axis scale value.
			*/												
			void setScaleX(Number x);
			
			/**
			* Returns the entity's scale on the Y axis.
			@param y Y-axis scale value.
			*/															
			void setScaleY(Number y);
			
			/**
			* Returns the entity's scale on the Z axis.
			@param z Z-axis scale value.
			*/																		
			void setScaleZ(Number z);

			
			/**
			* Scales the entity relative to its current scale.
			@param x X-axis value.
			@param y Y-axis value.
			@param z Z-axis value.						
			*/									
			void Scale(Number x, Number y, Number z=0.0);
			

			/**
			* Scales the entity relative to its current scale.
			@param scale Scale vector.				
			*/									
			void Scale(const Vector3 &scale);			

			/**
			* Sets the entity's scale.
			@param x X-axis value.
			@param y Y-axis value.
			@param z Z-axis value.						
			*/									
			void setScale(Number x, Number y, Number z=1.0);
			
			/**
			* Sets the entity's scale.
			@param v New scale vector.
			*/												
			void setScale(const Vector3 &v);
			
			/**
			* Returns the entity's scale multiplied by its parent's compound scale.
			* @return Compound scale as vector.
			*/			
			Vector3 getCompoundScale() const;
			
			/**
			* Returns the entity's scale.
			@return Entity's scale as a vector.
			*/						
			Vector3 getScale() const;
        
            /**
             * Returns the entity's rotation as euler angles
             @return Entity's rotation as euler angles
             */
            Vector3 getRotationEuler() const;
		
			/**
			* Returns the entity's pitch combined with the combined pitch of its parent.
			@return Entity's combined pitch.
			*/									
			Number getCombinedPitch() const;
			
			/**
			* Returns the entity's yaw combined with the combined yaw of its parent.
			@return Entity's combined yaw.
			*/									
			Number getCombinedYaw() const;
			
			/**
			* Returns the entity's roll combined with the combined roll of its parent.
			@return Entity's combined roll.
			*/												
			Number getCombinedRoll() const;
			
			/**
			* Forces the rotation quaternion to be rebuilt.
			*/
			void rebuildRotation();					
			
            /**
             * Sets rotation from euler angles
             * @param rotation New rotation values
             */
            void setRotationEuler(const Vector3 &rotation);
        
			/**
			* Sets the pitch rotation of the entity.
			* @param pitch New pitch value in degrees.
			*/								
			void setPitch(Number pitch);
			
			/**
			* Sets the yaw rotation of the entity.
			* @param yaw New yaw value in degrees.
			*/											
			void setYaw(Number yaw);
			
			/**
			* Sets the roll rotation of the entity.
			* @param roll New roll value in degrees.
			*/														
			void setRoll(Number roll);
			
			/**
			* Rolls the entity relative to its current roll.
			* @param roll Roll value in degrees.
			*/																	
			void Roll(Number roll);
			
			/**
			* Yaws the entity relative to its current yaw.
			* @param yaw Yaw value in degrees.
			*/																				
			void Yaw(Number yaw);
			
			/**
			* Pitches the entity relative to its current pitch.
			* @param pitch Pitch value in degrees.
			*/																				
			void Pitch(Number pitch);
			
			/**
			* Returns the current pitch of the entity.
			* @return Current pitch value.
			*/																				
			Number getPitch() const;
			
			/**
			* Returns the current yaw of the entity.
			* @return Current yaw value.
			*/																							
			Number getYaw() const;
			
			/**
			* Returns the current roll of the entity.
			* @return Current roll value.
			*/																										
			Number getRoll() const;
			     
            /**
             * Returns the bounding box X value.
             */
			Number getWidth() const;

            /**
             * Returns the bounding box Y value.
             */
			Number getHeight() const;

            /**
             * Returns the bounding box Z value.
             */
			Number getDepth() const;
			
            /**
             * Sets the bounding box X value.
             */
			void setWidth(Number width);
        
            /**
             * Sets the bounding box Y value.
             */
			void setHeight(Number height);
        
            /**
             * Sets the bounding box Z value.
             */
			void setDepth(Number depth);
			
			/**
			* Sets the rotation with quaternion value.
			*/
			void setRotationQuat(Number w, Number x, Number y, Number z);

            /*
            * Sets the rotation with quaternion value.
            */
			void setRotationByQuaternion(const Quaternion &quaternion);
			
			/**
			* Returns the current rotation as a quaternion.
			* @return Current rotation value.
			*/
			Quaternion getRotationQuat() const;
			
        
            Quaternion getConcatenatedQuat() const;
        
			/**
			* Orients the entity towards the specified location with the provided up vector. The up vector determines which side of the entity will be pointing in that direction.
			* @param loc Location to look at.
			* @param upVector The up vector.
			*/																															
			void lookAt(const Vector3 &loc, const Vector3 &upVector = Vector3(0,1,0));
			
			/**
			* Orients the entity towards another entity with the provided up vector. The up vector determines which side of the entity will be pointing in that direction.
			* @param entity Entity to look at.
			* @param upVector The up vector.
			* @see lookAt()
			*/																																		
			void lookAtEntity(Entity *entity, const Vector3 &upVector = Vector3(0,1,0));		
			
			/**
			* Returns the entity's color multiplied by its parent entity's combined color.
			* @return Entity's combined color.
			*/
			Color getCombinedColor() const;
			
			/**
			* Sets the color of the entity as normalized floating point values.
			* @param r Red value as a 0-1 floating point number.
			* @param g Green value as a 0-1 floating point number.
			* @param b Blue value as a 0-1 floating point number.
			* @param a Alpha value as a 0-1 floating point number.									
			*/			
			void setColor(Number r, Number g, Number b, Number a);
			
			/**
			* Sets the color of the entity as 0-255 integers.
			* @param r Red value as a 0-255 integer.
			* @param g Green value as a 0-255 integer.
			* @param b Blue value as a 0-255 integer.
			* @param a Alpha value as a 0-255 integer.
			*/						
			void setColorInt(int r, int g, int b, int a);	
			
			/**
			* Sets the color of the entity.
			* @param color Color to set the entity color to.
			*/									
			void setColor(Color color);

			//@}

			
            /**
             * Sets the anchor (center) point of the entity as normalized half bounding box coordinates. (i.e. -1.0 or 1.0 will offset the entity by half on a particular axis).
             * @param anchorPoint Anchor point as a 3D Vector.
             */
			void setAnchorPoint(const Vector3 &anchorPoint);
        
            /**
             * Sets the anchor (center) point of the entity as normalized half bounding box coordinates. (i.e. -1.0 or 1.0 will offset the entity by half on a particular axis).
             * @param x X Offset
             * @param y Y Offset
             * @param z Z Offset
             */
			void setAnchorPoint(Number x, Number y, Number z);
        
            /**
             * Returns the current anchor (center) point of the entity.
             */
			Vector3 getAnchorPoint() const;
			
			virtual MouseEventResult onMouseDown(const Ray &ray, int mouseButton, int timestamp);
			virtual MouseEventResult onMouseUp(const Ray &ray, int mouseButton, int timestamp);
			virtual MouseEventResult onMouseMove(const Ray &ray, int timestamp);
			virtual MouseEventResult onMouseWheelUp(const Ray &ray, int timestamp);
			virtual MouseEventResult onMouseWheelDown(const Ray &ray, int timestamp);

		
			/** @name Rendering properties
			*  Methods and properties affecting the way the entity is rendered.
			*/
			//@{
								
			/**
			* If this flag is true, the entity will always face the camera. False by default.
			*/						
			bool billboardMode;			
			
			/**
			* Normally, if billboardMode is on, no rotation is allowed at all. If this flag is also true, you can rotate the entity around the axis pointing to the camera.
			*/									
			bool billboardRoll;
			
			/**
			* If set to true, the entity will not be scaled by the modelview
			* matrix when billboardMode is enabled
			*/
			bool billboardIgnoreScale;

			/**
			* The entity's color.
			*/					
			Color color;
			
			/**
			* If this flag is set to false, this entity will not be rendered or updated.
			*/			
			bool enabled;
			
			/**
			* If this flag is set to false, this entity will not be rendered.
			*/
			bool visible;
		
			/** 
			* If this flag is set to false, this entity will not write to the depth buffer when it's rendered.
			*/
			bool depthWrite;		
			
			/** 
			* If this flag is set to false, this entity will not check the depth buffer when it's rendering.
			*/			
			bool depthTest;
			
			/**
			* Entity blending mode. Possible values are Renderer::BLEND_MODE_NONE, Renderer::BLEND_MODE_NORMAL, Renderer::BLEND_MODE_LIGHTEN, Renderer::BLEND_MODE_COLOR, Renderer::BLEND_MODE_PREMULTIPLIED, Renderer::BLEND_MODE_MULTIPLY. See the Renderer class for details on individual blending modes.
                This blending mode is overridden by the material.
			*/
			int blendingMode;	
			
			/**
			* If set to false, the children of this entity will not multiply by this entity's color. Set to true by default.
			*/ 
			bool colorAffectsChildren;	

			/**
			* If set to false, the children will be rendered even if the entity is invisible.
			*/ 
			bool visibilityAffectsChildren;	
			
			/**
			* If this flag is set to true, this entity will render only into the depth buffer. This, effectively, means that it will be invisible, but still obscuring other entities.
			*/
			bool depthOnly;		
			
			/**
			* If this flag is set to true, this entity's transformations will not take into account its parent, making its transforms always relative to 0.
			*/
			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
			/**
			* Sets user data pointer.
			* @param userData User data pointer
			*/
			void setUserData(void *userData);			

			/**
			* Returns the user data pointer.
			* @return User data pointer
			*/			
			void *getUserData() const;
				
			/**
			* Sets the entity's blending mode.
			* @param newBlendingMode New blending mode to set. Possible values are Renderer::BLEND_MODE_NORMAL, Renderer::BLEND_MODE_LIGHTEN, Renderer::BLEND_MODE_COLOR, Renderer::BLEND_MODE_PREMULTIPLIED, Renderer::BLEND_MODE_MULTIPLY. See the Renderer class for details on individual blending modes.
			* @see Renderer			
			*/
			void setBlendingMode(int newBlendingMode);
			
            /**
             * Returns the first child entity that has the specified string id.
             * @param id Specified id to search for.
             * @param recursive If set to true, will search all child entities recursively.
             * @return Entity with specified string id or NULL if not found.
             */
			Entity *getEntityById(String id, bool recursive) const;
        
            /**
             * Returns all child entities which have the specified tag.
             * @param tag Tag to search for.
             * @param recursive If set to true, will search all child entities recursively.
             * @return List of child entities that contain the specified tag.
             */
			std::vector<Entity*> getEntitiesByTag(String tag, bool recursive) const;

            /**
             * Returns all child entities that have the specified layer ID. Layer IDs are used by the entity instances to separate entities into groups.
             * @param Layer ID to search for.
             * @param recursive If set to true, will search all child entities recursively.
             * @return List of child entities that contain the specified layer ID.
             */
            std::vector<Entity*> getEntitiesByLayerID(unsigned char layerID, bool recursive) const;
        
            /** 
             * Returns custom string dictionary property of the entity based on the property name.
             * @param Property name to look up.
             * @return String property for specified property name or "null" if this property doesn't exist.
             */
			String getEntityProp(const String& propName);
        
            /**
             * Sets the entity property for a specified property name in the entity's custom property dictionary.
             * @param propName Property name to set.
             * @param propValue Value to set for the specified property name.
             */
			void setEntityProp(const String& propName, const String& propValue);
			
            /**
             * If set to true, the y position of the entity matrix will be multiplied by -1.0, inverting its Y-axis coordinate system.
             */
			void setInverseY(bool val);
        
            /**
             * Returns true if the entity is set to use an inverse Y-coordinate system.
             */
			bool getInverseY();
			
			void doUpdates();
			void doFixedUpdates();
			virtual Matrix4 buildPositionMatrix();
			void setRenderer(Renderer *renderer);
			
            /**
             * Implement this method to do custom ray hit detection beyond a bounding box check. Always returns true by default.
             */
			virtual bool customHitDetection(const Ray &ray) { return true; }			
			/**
             * If set to true, the entity's transformations will not be affected by its parents. Defaults to false.
             */
			bool ignoreParentMatrix;
						
            /**
             * If set to true, will constrain the rendering of this entity into the viewport coordinates defined by scissorBox.
             * @see scissorBox
             */
			bool enableScissor;
        
            /**
             * Defines the viewport coordinates to clip rendering to if enableScissor is defined.
             * @see enableScissor
             */
			Polycode::Rectangle scissorBox;			
			
            /**
             * Flags an editor only entity. If set to true, this entity will not be saved to file by entity instances or show up in the IDE entity editor.
             */
			bool editorOnly;

            /**
             * String ID of the entity. Can be used to retrieve specific entities by their ID.
             */
			String id;

            /**
             * Returns the number of tags this entity has.
             */
			unsigned int getNumTags() const;
        
            /**
             * Returns the tag at specified index or an empty string if index is invalid.
             */
			String getTagAtIndex(unsigned int index) const;
        
            /**
             * Returns true if this entity contains the specified tag.
             * @param tag Tag to look up.
             * @return True if this entity contains the specified tag, false if it doesn't.
             */
			bool hasTag(String tag) const;
			
            /**
             * Removes all tags from this entity.
             */
			void clearTags();
        
            /**
             * Adds a string tag to the entity.
             * @param tag Tag to add.
             */
			void addTag(String tag);
			
            /**
             * Entity collision type for physics module. This is set per physics module documentaiton.
             */
			unsigned char collisionShapeType;
        
            /**
             * If set to true, will automatically process mouse events and dispatch its own input events if mouse events intersect with the entity's bounding box. Defaults to false.
                 Attention: All of the entity's parents' processInputEvents flags must be set to true for this to function including the parent Scene's rootEntity!
             */
			bool processInputEvents;
        
            /**
             * If set to true, will block input events for entities below itself in the parent's entiy list.
             */
			bool blockMouseInput;
						
		
            /** 
             * Returns the screen pixel position of the entity using a specified projection matrix, camera matrix and viewport.
             * @param projectionMatrix Projection matrix to use.
             * @param cameraMatrix Camera matrix to use.
             * @param viewport Viewport rectangle.
             * @return Pixel position of the entity on the screen.
             */
            Vector2 getScreenPosition(const Matrix4 &projectionMatrix, const Matrix4 &cameraMatrix, const Polycode::Rectangle &viewport);
        
            /**
             * Returns the screen pixel position of the entity using the last projection matrix, camera matrix and viewport that were set in the renderer.
             * @return Pixel position of the entity on the screen.
             */
			Vector2 getScreenPositionForMainCamera();


            /**
             * If set to true, will round the position of this entity to integral values. Use this if you need pixel-perfect positioning in 2D.
             */
			bool snapToPixels;
        
			bool mouseOver;
        
            /**
             * Sets the default blending mode for all created entities.
             */
            static int defaultBlendingMode;
        
            void recalculateAABBAllChildren();
            void recalculateAABB();
        
            /**
             Return axis-aligned bounding box in world space.
             */
            AABB getWorldAABB();
        
            /**
             * Returns the bounding box of the entity. This is used for hit-testing as well as visibility calculation.
             */
            Vector3 getLocalBoundingBox();
        
            /**
             * Sets the bounding box of the entity as a 3D Vector. This is used for hit-testing as well as visibility calculation.
             */
            void setLocalBoundingBox(const Vector3 box);
        
            /**
             * Sets the bounding box of the entity. This is used for hit-testing as well as visibility calculation.
             */
            void setLocalBoundingBox(Number x, Number y, Number z);
        
            /**
             * Sets the bounding box X-axis value of the entity.
             */
            void setLocalBoundingBoxX(Number x);
        
            /**
             * Sets the bounding box Y-axis value of the entity.
             */
            void setLocalBoundingBoxY(Number y);

            /**
             * Sets the bounding box Z-axis value of the entity.
             */
            void setLocalBoundingBoxZ(Number z);
        
            bool rendererVis;
        
            /**
            * Layer ID. Used by entity instances to separate entities into groups.
            */
            unsigned char layerID;

            std::vector <EntityProp> entityProps;
        
		protected:
        
		
            AABB aabb;
            Vector3 bBox;
        
			int lastClickTicks;
			Number yAdjust;
			std::vector<String> *tags;
		
			void *userData;
		
			std::vector<Entity*> children;

			Vector3 anchorPoint;
		
			Vector3 position;
			Vector3 scale;		
			Vector3 rotation;
	
			Quaternion rotationQuat;
			
			bool lockMatrix;
			bool matrixDirty;
        
			Matrix4 transformMatrix;
			Entity *parentEntity;
		
			Renderer *renderer;
	};
	
	typedef Entity SceneEntity;
	typedef Entity ScreenEntity;
			
}
