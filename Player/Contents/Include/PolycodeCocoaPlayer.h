/*
 *  CocoaPolycodePlayer.h
 *  PolycodePlayer
 *
 *  Created by Ivan Safrin on 12/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#import "PolySubstanceView.h"

#include "PolycodePlayer.h"
#import <Cocoa/Cocoa.h>
#include "PolyCocoaCore.h"

class CocoaPolycodePlayer : public PolycodePlayer {
	public:
		CocoaPolycodePlayer(SubstanceView *view,String fileName, bool knownArchive);
		virtual ~CocoaPolycodePlayer();
	
		void createCore();	

		NSWindow *playbackWindow;
	
	protected:

		SubstanceView *view;	
};