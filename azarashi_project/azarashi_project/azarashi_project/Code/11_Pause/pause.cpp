#include "pause.h"

void Pause::apply() {
	if (Input::GetButtonTrigger(XINPUT_START) || Input::GetKeyTrigger(VK_P)) {
		paused = true;
	}

}

void Pause::maladaptive()
{
		paused = false;
}

bool Pause::isPaused() const {
    return paused;
}
