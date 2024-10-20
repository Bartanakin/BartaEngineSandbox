//
// Created by barta on 01/03/2024.
//

#include "Sandbox.h"
#include "Dynamics/Timers/FrameLimitTimerProxy.h"
#include "Dynamics/Timers/SFML_Timer.h"

int main() {
	auto app = new Sandbox();
	app->run();
	delete app;

    return 0;
}