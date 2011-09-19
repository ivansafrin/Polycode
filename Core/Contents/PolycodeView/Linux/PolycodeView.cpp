#include "PolycodeView.h"

namespace Polycode {

    PolycodeView::PolycodeView(const char *title) : PolycodeViewBase() {
        windowTitle = title;
        windowData = &windowTitle;
    }

    PolycodeView::~PolycodeView() {

    }

}

