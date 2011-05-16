/*
 *  PolyUIButton.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"

namespace Polycode {

	class _PolyExport UIButton : public ScreenEntity {
		public:
			UIButton(String text, Number width, Number height = 26);
			~UIButton();		
			void handleEvent(Event *event);
			
			void Update();
				
		private:
			
			Number labelXPos;
			Number labelYPos;
			UIBox *buttonRect;
			UIBox *buttonFocusedRect;		
			ScreenLabel *buttonLabel;
			bool pressedDown;
	};
}