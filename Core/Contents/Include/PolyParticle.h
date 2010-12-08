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
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyScenePrimitive.h"
#include "PolyCoreServices.h"


namespace Polycode {

	class _PolyExport Particle {
		public:
			Particle(int particleType, Material *texture, Mesh *particleMesh);
			~Particle();
			void Reset();
			
			SceneEntity *particleBody;						
			
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