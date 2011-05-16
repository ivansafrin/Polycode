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
			UIHSlider(Font *font, Number start, Number end, Number width);
			~UIHSlider();		
			void handleEvent(Event *event);
			void Update();
			
			void setSliderValue(Number val);
			Number getSliderValue();
			
			ScreenShape *getBgRect();
			
		private:
		
			Number gripPos;
			
			Number labelXPos;
			Number labelYPos;
			ScreenShape *bgRect;
			ScreenShape *gripRect;
			ScreenShape *shadowRect;
			
			Number sliderValue;
			Number startValue;
			Number endValue;
			Number sliderWidth;
			
			ScreenLabel *buttonLabel;
			bool pressedDown;
	};
}