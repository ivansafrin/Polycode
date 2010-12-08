/*
 *  PolyUIWindow.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package UI

#pragma once

#include "PolyGlobals.h"
#include "PolyScreenShape.h"
#include "PolyScreenLabel.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIImageButton.h"
#include "PolyFont.h"
#include "PolyScreenEvent.h"
#include "PolyUIBox.h"

namespace Polycode {

	class _PolyExport UIWindow : public ScreenEntity {
		public:
			UIWindow(wstring windowName, float width, float height);
			~UIWindow();
			
			void showWindow();
			void hideWindow();
			void onKeyDown(TAUKey key, wchar_t charCode);
			virtual void onClose(){}
			void onLoseFocus();
			
			void setWindowSize(float w, float h);
			
			void onMouseDown(float x, float y);
					
			virtual void handleEvent(Event *event);
		
			float padding;
			float topPadding;
		
			bool closeOnEscape;
		
		protected:				

		
			Font *font;
			Tween *windowTween;
			UIImageButton *closeBtn;
			UIBox *windowRect;
			ScreenShape *titlebarRect;
	};
}