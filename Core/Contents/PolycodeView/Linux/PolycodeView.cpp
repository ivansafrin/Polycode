#include "PolycodeView.h"

namespace Polycode {

    PolycodeView::PolycodeView(const char *title, bool resizable) : PolycodeViewBase() {
        windowTitle = title;
        windowData = &windowTitle;
	this->resizable = resizable;
    }

    PolycodeView::~PolycodeView() {

    }

}

