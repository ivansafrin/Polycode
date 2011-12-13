#pragma once

#include "PolyCoreInput.h"

extern "C" {
#include "gamepad/Gamepad.h"

#define POLL_ITERATION_INTERVAL 30

class StemGamepadController {
	public: 
		StemGamepadController(Polycode::CoreInput *coreInput);
		~StemGamepadController();
		
		void Update();
		
		unsigned int iterationsToNextPoll;
		Polycode::CoreInput *coreInput;
};
}