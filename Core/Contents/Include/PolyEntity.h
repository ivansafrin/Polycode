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
#include "PolyQuaternion.h"
#include "PolyColor.h"
#include "PolyRectangle.h"
#include "PolyEventDispatcher.h"
#include <vector>

namespace Polycode {

class Renderer;

class _PolyExport EntityProp {
	public:
		String propName;
		String propValue;
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
		virtual ~Entity();

		/**
		* Main render method. Override this to do your own drawing.
		*/
		virtual void Render(){};
		/**
		* Main update method. Override this to do your updates before the render cycle.
		*/
		virtual void Update(){};

		virtual void transformAndRender();

		void renderChildren();


		/**
		* Clones the entity, return an exact copy. This method must be implemented in an Entity subclass for you to be able to clone it.
		* @param deepClone If true, perform a deep clone, cloning all the children.
		* @param ignoreEditorOnly If true, ignore all child entities where editorOnly is set to true (will still clone the entity you call Clone() on even if its editorOnly flag is set to true.
		* @return The clone of the entity.
		*/
		virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly);

		/**
		* This method must be implemented by all subvlasses implementing Clone.
		*/
		virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly);


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

		Matrix4 getConcatenatedMatrixRelativeTo(Entity *relativeEntity);

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
		* @see addChild()
		*/
		virtual void addEntity(Entity *newChild);

		/**
		* Adds another entity as a child. The children inherit the parent's transforms.
		@param newChild The entity to be added.
		*/
		void addChild(Entity *newChild);

		/**
		* Removes an entity from the entity's children.
		@param entityToRemove Entity to be removed.
		*/
		void removeChild(Entity *entityToRemove);

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
		void setPosition(Number x, Number y, Number z);

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
		void Translate(Number x, Number y, Number z);

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
		void Scale(Number x, Number y, Number z);

		/**
		* Sets the entity's scale.
		@param x X-axis value.
		@param y Y-axis value.
		@param z Z-axis value.
		*/
		void setScale(Number x, Number y, Number z);

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
		* Sets the rotation with quaternion value.
		* @param Current yaw value.
		*/
		void setRotationQuat(Number w, Number x, Number y, Number z);

		/**
		* Returns the current rotation as a quaternion.
		* @return Current rotation value.
		*/
		Quaternion getRotationQuat() const;

		/**
		* Orients the entity towards the specified location with the provided up vector. The up vector determines which side of the entity will be pointing in that direction.
		* @param loc Location to look at.
		* @param upVector The up vector.
		*/
		void lookAt(const Vector3 &loc, const Vector3 &upVector = Vector3(0,1,0));

		/**
		* Orients the entity towards another entity with the provided up vector. The up vector determines which side of the entity will be pointing in that direction.
		* @param loc Location to look at.
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
		// ----------------------------------------------------------------------------------------------------------------

		/** @name Bounding box operations.
		*  These methods modify the bounding box of the entity. The bounding box is used for culling and collision detection.
		*/
		//@{

		/**
		* Recalculates the bounding box of the entity based on its size.
		*/
		void recalculateBBox();

		/**
		* Returns the bounding box radius.
		* @return The bounding box radius.
		*/
		Number getBBoxRadius() const;

		/**
		* Returns the entity's bounding box radius compounded from its children's bounding box radii.
		* @return The compound bounding box radius.
		*/
		Number getCompoundBBoxRadius() const;

		/**
		* Sets the bounding box radius.
		* @param rad New bounding box radius.
		*/
		void setBBoxRadius(Number rad);

		//@}
		// ----------------------------------------------------------------------------------------------------------------

		/** @name Rendering properties
		*  Methods and properties affecting the way the entity is rendered.
		*/
		//@{


		/**
		* You can set a custom string identifier for user purposes.
		*/
		String custEntityType;

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
		* Normally, translucent textures do not affect the depth buffer, but if this flag is set to true, this entity's alpha channel is written to the depth buffer at a preset threshold. This flag is set to false by default.
		*/
		bool alphaTest;

		/**
		* If this flag is set to false, backface culling is disabled when rendering this entity, rendering both sides of each face. Set to true by default.
		*/
		bool backfaceCulled;

		/**
		* If this flag is set to true, the entity will render in wireframe. 
		*/
		bool renderWireframe;

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
		* Entity blending mode. Possible values are Renderer::BLEND_MODE_NORMAL, Renderer::BLEND_MODE_LIGHTEN, Renderer::BLEND_MODE_COLOR, Renderer::BLEND_MODE_PREMULTIPLIED, Renderer::BLEND_MODE_MULTIPLY. See the Renderer class for details on individual blending modes.
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
		void *getUserData();

		/**
		* Sets the entity's blending mode.
		* @param newBlendingMode New blending mode to set. Possible values are Renderer::BLEND_MODE_NORMAL, Renderer::BLEND_MODE_LIGHTEN, Renderer::BLEND_MODE_COLOR, Renderer::BLEND_MODE_PREMULTIPLIED, Renderer::BLEND_MODE_MULTIPLY. See the Renderer class for details on individual blending modes.
		* @see Renderer
		*/
		void setBlendingMode(int newBlendingMode);

		Entity *getEntityById(String id, bool recursive);
		std::vector<Entity*> getEntitiesByTag(String tag, bool recursive);

		Vector3 getChildCenter() const;

		std::vector <EntityProp> entityProps;
		String getEntityProp(const String& propName);
		void setEntityProp(const String& propName, const String& propValue);

		void doUpdates();
		virtual Matrix4 buildPositionMatrix();
		virtual void adjustMatrixForChildren(){}
		void setRenderer(Renderer *renderer);


		Vector3 bBox;
		bool ignoreParentMatrix;

		bool enableScissor;
		Polycode::Rectangle scissorBox;

		Vector3 position;
		Vector3 scale;
		Rotation rotation;


		bool editorOnly;

		/** @name Class and ID strings
		*  These properties can be used to set and retrieve string-based ids and
		* tags
		*/
		//@{

		String id;

		unsigned int getNumTags() const;
		String getTagAtIndex(unsigned int index) const;
		bool hasTag(String tag) const;

		void clearTags();
		void addTag(String tag); 

		//@}

	protected:

		std::vector<String> *tags;

		void checkTransformSetters();

		void *userData;

		std::vector<Entity*> children;

		Vector3 childCenter;
		Number bBoxRadius;

		Vector3 _position;
		Vector3 _scale;
		Rotation _rotation;

		Quaternion rotationQuat;

		bool lockMatrix;
		bool matrixDirty;
		Matrix4 transformMatrix;
		Number matrixAdj;
		Entity *parentEntity;

		Renderer *renderer;
};
}
