/*
 *  PolyUIImageButton.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenImage.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"

namespace Polycode {

	class _PolyExport UIImageButton : public ScreenEntity {
		public:
			UIImageButton(string imageName);
			~UIImageButton();
		
			void handleEvent(Event *event);
				
		private:
			ScreenShape *buttonRect;
			ScreenImage *buttonImage;
			bool pressedDown;
	};
}