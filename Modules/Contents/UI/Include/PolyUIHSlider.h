/*
 *  PolyUIHSlider.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/7/08.
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

namespace Polycode {

	class _PolyExport UIHSlider : public ScreenEntity {
		public:
			UIHSlider(Font *font, float start, float end, float width);
			~UIHSlider();		
			void handleEvent(Event *event);
			void Update();
			
			void setSliderValue(float val);
			float getSliderValue();
			
			ScreenShape *getBgRect();
			
		private:
		
			float gripPos;
			
			float labelXPos;
			float labelYPos;
			ScreenShape *bgRect;
			ScreenShape *gripRect;
			ScreenShape *shadowRect;
			
			float sliderValue;
			float startValue;
			float endValue;
			float sliderWidth;
			
			ScreenLabel *buttonLabel;
			bool pressedDown;
	};
}