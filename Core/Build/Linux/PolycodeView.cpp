
#include "PolycodeView.h"
#include <stdio.h>
#include <stdlib.h>

PolycodeView::PolycodeView(const char *title) : PolycodeViewBase() {
	windowTitle = title;
	windowData = &windowTitle;
}

PolycodeView::~PolycodeView() {

}

