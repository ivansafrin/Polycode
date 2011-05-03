/*
 *  PolySceneEntity.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package Scene

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolyVector3.h"
#include "PolyMatrix4.h"
#include "PolyQuaternion.h"
#include "PolyEntity.h"
#include "PolyEventHandler.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport SceneEntity : public Entity, public EventHandler {
		public:
			SceneEntity();
			virtual ~SceneEntity();
		
			virtual bool testMouseCollision(Number x, Number y) { return false;}
			
		protected:

	};
}