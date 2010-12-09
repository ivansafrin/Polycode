/*
 *  PolyUICheckBox.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenImage.h"
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"

namespace Polycode {

	class _PolyExport UICheckBox : public ScreenEntity {
		public:
			UICheckBox(Font *font, String checkImage, String caption, bool checked);
			~UICheckBox();
		
			void changeCheck();
			bool isChecked();
			void handleEvent(Event *event);
				
		private:
			bool checked;
			ScreenLabel *captionLabel;
			ScreenShape *buttonRect;
			ScreenShape *shadowRect;
			ScreenImage *buttonImage;
			bool pressedDown;
	};
}