
#include "PolycodeView.h"
#include <stdio.h>
#include <stdlib.h>

namespace Polycode {

    PolycodeView::PolycodeView(const char *title) : PolycodeViewBase() {
        windowTitle = title;
        windowData = &windowTitle;
    }

    PolycodeView::~PolycodeView() {

    }

}

