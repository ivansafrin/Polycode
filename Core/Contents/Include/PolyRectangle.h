/*
 *  PolyRectangle.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/7/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Math

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"

namespace Polycode {
	class _PolyExport Rectangle {
		public:
			Rectangle(){x=0;y=0;w=0;h=0;}
			Rectangle(Number px, Number py, Number pw, Number ph){x=px;y=py;w=pw;h=ph;}
			void setRect(Number x, Number y, Number w, Number h);
			
			Number x;
			Number y;
			Number w;
			Number h;
	};
}