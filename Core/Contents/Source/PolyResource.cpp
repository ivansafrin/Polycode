/*
 *  PolyResource.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/19/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyResource.h"

using namespace Polycode;

Resource::Resource(int type) {
	this->type = type;
}

Resource::~Resource() {

}

string Resource::getResourceName() {
	return name;
}

int Resource::getResourceType() {
	return type;
}

void Resource::setResourceName(string newName) {
	name = newName;
}

void Resource::setResourcePath(string path) {
	resourcePath = path;
}

string Resource::getResourcePath() {
	return resourcePath;
}
