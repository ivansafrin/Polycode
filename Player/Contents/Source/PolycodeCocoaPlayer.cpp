/*
 *  CocoaPolycodePlayer.cpp
 *  PolycodePlayer
 *
 *  Created by Ivan Safrin on 12/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolycodeCocoaPlayer.h"


CocoaPolycodePlayer::CocoaPolycodePlayer(SubstanceView *view, String fileName, bool knownArchive) : PolycodePlayer(fileName, knownArchive) {
	this->view = view;
}

CocoaPolycodePlayer::~CocoaPolycodePlayer() {
	
}

void CocoaPolycodePlayer::createCore() {
	core =  new CocoaCore(view, xRes, yRes,  fullScreen, aaLevel, frameRate);	
}