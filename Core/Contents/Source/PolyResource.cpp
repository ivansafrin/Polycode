/*
 *  PolyResource.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/19/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyResource.h"

using namespace Polycode;

Resource::Resource(int type) {
	this->type = type;
}

Resource::~Resource() {

}

String Resource::getResourceName() {
	return name;
}

int Resource::getResourceType() {
	return type;
}

void Resource::setResourceName(String newName) {
	name = newName;
}

void Resource::setResourcePath(String path) {
	resourcePath = path;
}

String Resource::getResourcePath() {
	return resourcePath;
}
