#pragma once

#include <Polycode.h>
#include "PolySDLCore.h"

class PolycodeView : public PolycodeViewBase {
	public:
		PolycodeView(const char *title);
		~PolycodeView();

		String windowTitle;
};
