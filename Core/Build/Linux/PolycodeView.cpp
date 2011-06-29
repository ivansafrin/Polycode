
#include "PolycodeView.h"
#include <stdio.h>
#include <stdlib.h>

long getThreadID() {
        return (long)pthread_self();
}

PolycodeView::PolycodeView(const char *title) : PolycodeViewBase() {
	windowTitle = title;
	windowData = &windowTitle;
}

PolycodeView::~PolycodeView() {

}

