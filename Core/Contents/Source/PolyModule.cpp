/*
 *  PolyModule.cpp
 *  PolyCore
 *
 *  Created by Ivan Safrin on 12/1/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */


#include "PolyModule.h"

using namespace Polycode;

PolycodeModule::PolycodeModule() {
	type = TYPE_GENERIC;
}

PolycodeModule::~PolycodeModule() {
	
}

PolycodeShaderModule::PolycodeShaderModule() : PolycodeModule() {
	type = TYPE_SHADER;
}

PolycodeShaderModule::~PolycodeShaderModule() {

}
