/*
 *  PolySceneLight.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/21/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyCoreServices.h"
#include "PolyScene.h"
#include "PolyCamera.h"
#include "PolyMesh.h"

namespace Polycode {

	class Scene;
	class Camera;
	class _PolyExport SceneLight : public SceneEntity {
		public:
			SceneLight(int type, float intensity, float distance, Scene *parentScene);
			virtual ~SceneLight();
		
			float getIntensity();
			float getDistance();
			int getType();
			
			void renderDepthMap(Scene *scene);
			
			void Render();

			Matrix4 getLightViewMatrix();
			
			static const int AREA_LIGHT = 0;
			static const int SPOT_LIGHT = 1;
			
			Texture *getZBufferTexture();
			Color lightColor;
		
			void setLightColor(float r, float g, float b) { lightColor.r = r; lightColor.g = g; lightColor.b = b; }
			void enableShadows(bool val, float resolution=256);
			void setShadowMapFOV(float fov);
		
			bool areShadowsEnabled();
		
			int getLightType() { return type; }
		
		private:
		
			int type;
			float intensity;
			
			Camera *spotCamera;
			Texture *zBufferTexture;
		
			Scene *parentScene;
			
			Matrix4 lightViewMatrix;
		
			float shadowMapRes;
			float shadowMapFOV;	
			bool shadowsEnabled;
		
			float distance;
			Mesh *lightMesh;
	};
}