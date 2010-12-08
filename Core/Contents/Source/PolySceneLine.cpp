/*
 *  PolySceneLine.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 10/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySceneLine.h"

using namespace Polycode;

SceneLine::SceneLine(Vector3 p1, Vector3 p2) : SceneEntity() {
	v1.set(p1.x,p1.y,p1.z);
	v2.set(p2.x,p2.y,p2.z);
}

SceneLine::~SceneLine() {

}
			
void SceneLine::Render() {
	/*
	int rmode = CoreServices::getInstance()->getRenderer()->getRenderMode();
	CoreServices::getInstance()->getRenderer()->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);
	CoreServices::getInstance()->getRenderer()->setLineSize(1.0f);
	CoreServices::getInstance()->getRenderer()->beginRenderOperation(Mesh::TRIFAN_MESH);
	CoreServices::getInstance()->getRenderer()->draw3DVertex(&v1, NULL);
	CoreServices::getInstance()->getRenderer()->draw3DVertex(&v2, NULL);
	CoreServices::getInstance()->getRenderer()->endRenderOperation();
	CoreServices::getInstance()->getRenderer()->setRenderMode(rmode);
	 */
}
