/*
 *  PolySceneLight.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/21/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyString.h"
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
			SceneLight(int type, Number intensity, Number distance, Scene *parentScene);
			virtual ~SceneLight();
		
			Number getIntensity();
			Number getDistance();
			int getType();
			
			void renderDepthMap(Scene *scene);
			
			void Render();

			Matrix4 getLightViewMatrix();
			
			static const int AREA_LIGHT = 0;
			static const int SPOT_LIGHT = 1;
			
			Texture *getZBufferTexture();
			Color lightColor;
		
			void setLightColor(Number r, Number g, Number b) { lightColor.r = r; lightColor.g = g; lightColor.b = b; }
			void enableShadows(bool val, Number resolution=256);
			void setShadowMapFOV(Number fov);
		
			bool areShadowsEnabled();
		
			int getLightType() { return type; }
		
		private:
		
			int type;
			Number intensity;
			
			Camera *spotCamera;
			Texture *zBufferTexture;
		
			Scene *parentScene;
			
			Matrix4 lightViewMatrix;
		
			Number shadowMapRes;
			Number shadowMapFOV;	
			bool shadowsEnabled;
		
			Number distance;
			Mesh *lightMesh;
	};
}