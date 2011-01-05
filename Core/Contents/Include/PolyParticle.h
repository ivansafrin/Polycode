/*
 *  PolyParticle.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Scene

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyScreenShape.h"
#include "PolyScenePrimitive.h"
#include "PolyCoreServices.h"


namespace Polycode {

	class _PolyExport Particle {
		public:
			Particle(int particleType, bool isScreenParticle, Material *material, Texture *texture, Mesh *particleMesh);
			~Particle();
			void Reset();
			
			void createSceneParticle(int particleType, Material *material, Mesh *particleMesh);
			void createScreenParticle(int particleType, Texture *texture, Mesh *particleMesh);
		
			Entity *particleBody;						
			
			Vector3 velVector;
			Vector3 dirVector;	
			Vector3 deviation;		
			float life;
			float lifespan;
			float brightnessDeviation;
			float perlinPosX;
			float perlinPosY;
			float perlinPosZ;
			
			static const int BILLBOARD_PARTICLE = 0;
			static const int MESH_PARTICLE = 1;
	};
}