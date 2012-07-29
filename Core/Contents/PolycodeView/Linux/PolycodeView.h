#pragma once

#include "PolySDLCore.h"

namespace Polycode {

    class PolycodeView : public PolycodeViewBase {
        public:
            PolycodeView(const char *title);
            ~PolycodeView();

            String windowTitle;
    };

}
