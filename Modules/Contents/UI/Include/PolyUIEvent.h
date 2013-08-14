/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once
#include "PolyGlobals.h"
#include "PolyEvent.h"

namespace Polycode {

	class _PolyExport UIEvent : public Event {
		public:
			UIEvent();
			virtual ~UIEvent();
		
			static const int EVENTBASE_UIEVENT = 0xA00;
			static const int CLICK_EVENT = EVENTBASE_UIEVENT+0;
			static const int CLOSE_EVENT = EVENTBASE_UIEVENT+1;
			static const int OK_EVENT = EVENTBASE_UIEVENT+2;
			static const int CANCEL_EVENT = EVENTBASE_UIEVENT+3;
			static const int CHANGE_EVENT = EVENTBASE_UIEVENT+4;
			static const int YES_EVENT = EVENTBASE_UIEVENT+5;
			static const int NO_EVENT = EVENTBASE_UIEVENT+6;									
		protected:
		
			
	};
}