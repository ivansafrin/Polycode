/*
 *  ServerWorld.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/9/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
// @package Network

#pragma once

#include "PolyGlobals.h"
#include "PolyServer.h"

namespace Polycode {

class ServerClient;
	
class _PolyExport ServerWorld {
	public:
		ServerWorld() {}
		~ServerWorld() {};
	
		virtual void updateWorld(float elapsed) = 0;
		virtual void getWorldState(ServerClient *client, char **worldData,unsigned int *worldDataSize) = 0;
};

}