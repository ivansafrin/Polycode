/*
 *  PolyEntity.h
 *  Poly
 *
 *  Created by Ivan Safrin on 1/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyMatrix4.h"
#include "PolyQuaternion.h"
#include "PolyColor.h"
#include "PolyRenderer.h"
#include <vector>

using std::vector;

namespace Polycode {
	
	
	class _PolyExport EntityProp {
	public:
		String propName;
		String propValue;		
	};	

	class _PolyExport Entity {
		public:
			Entity();
			~Entity();

			virtual void Render(){};
			virtual void Update(){};
			virtual void transformAndRender();		
		
			void setMatrix(Matrix4 matrix);
			void rebuildTransformMatrix();
		
			void addEntity(Entity *newChild);
			void addChild(Entity *newChild);
			void removeChild(Entity *entityToRemove);
		
			void updateEntityMatrix();
			void renderChildren();		

			Vector3 *getPosition();
			void setPosition(float x, float y, float z);
			
			void setPositionX(float x);
			void setPositionY(float y);
			void setPositionZ(float z);

			void setScaleX(float x);
			void setScaleY(float y);
			void setScaleZ(float z);
		
		
			void setPosition(Vector3 posVec);
		
			void Translate(float x, float y, float z);
			void Translate(Vector3 tVec);
			void Scale(float x, float y, float z);
			void setScale(float x, float y, float z);
			Vector3 getScale();		
		
			Vector3 getCombinedPosition();
			float getCombinedPitch();
			float getCombinedYaw();
			float getCombinedRoll();
			void setParentEntity(Entity *entity);
			Entity *getParentEntity();
			void rebuildRotation();
			void dirtyMatrix(bool val);
		
			void setPitch(float pitch);
			void setYaw(float yaw);
			void setRoll(float roll);
			void Roll(float roll);
			void Yaw(float roll);
			void Pitch(float roll);
			float getPitch();
			float getYaw();
			float getRoll();
		
			void setRotationQuat(float w, float x, float y, float z);
			Quaternion getRotationQuat();
		
			Matrix4 getTransformMatrix();
			Matrix4 getConcatenatedMatrix();		
			Matrix4 getConcatenatedRollMatrix();		
		
			void setTransformByMatrix(Matrix4 matrix);	
		
			void setRenderer(Renderer *renderer);
			
			Color getCombinedColor();
			void setColor(float r, float g, float b, float a);
			void setColorInt(int r, int g, int b, int a);	
			void setColor(Color color);
		
			void recalculateBBox();
			float getBBoxRadius();
			float getCompoundBBoxRadius();
			void setBBoxRadius(float rad);			
			void setBlendingMode(int newBlendingMode);		
			Vector3 getChildCenter();
		
			void setDepthWrite(bool val);
		
			void doUpdates();
		
			void lookAt(const Vector3 &loc, const Vector3 &upVector = Vector3(0,1,0));
			void lookAtEntity(Entity *entity, const Vector3 &upVector = Vector3(0,1,0));		
			Matrix4 getLookAtMatrix(const Vector3 &loc, const Vector3 &upVector = Vector3(0,1,0));
		
			virtual Matrix4 buildPositionMatrix();
			virtual void adjustMatrixForChildren(){}
			
			void setMask(Entity *mask);
			void clearMask();
		
			Vector3 getCompoundScale();
		
			String custEntityType;
			vector <EntityProp> entityProps;				
		
			String getEntityProp(String propName);
		
			Vector3 bBox;
			bool billboardMode;			
			bool billboardRoll;
			bool alphaTest;
			bool backfaceCulled;	
		
			bool renderWireframe;
		
			Color color;
			bool enabled;
			bool visible;
		
			bool colorAffectsChildren;		
			bool depthOnly;
		
			// deprecated, remove!
			bool maskByZbuffer;
		
			bool isMask;
		
		protected:
			vector<Entity*> children;

			int blendingMode;
			Vector3 childCenter;
			float bBoxRadius;		
		
			Vector3 position;
			Vector3 scale;		
		
			bool hasMask;
		
			bool lockMatrix;
			bool matrixDirty;
			Matrix4 transformMatrix;
		
			float matrixAdj;
			float pitch;
			float yaw;			
			float roll;
		
			Entity *parentEntity;
		
			Quaternion qYaw;
			Quaternion qPitch;
			Quaternion qRoll;			
			Quaternion rotationQuat;	
		
			Entity *maskEntity;
		
			bool depthWrite;		
		
			Renderer *renderer;
	};
}