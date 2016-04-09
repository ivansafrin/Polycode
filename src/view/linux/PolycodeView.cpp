#include "polycode/view/linux/PolycodeView.h"

#include <X11/Xlib.h>

namespace Polycode {

    PolycodeView::PolycodeView(const char *title, bool resizable) : PolycodeViewBase() {
        XInitThreads();
        windowTitle = title;
        windowData = &windowTitle;
	this->resizable = resizable;
    }

    PolycodeView::~PolycodeView() {

    }

}