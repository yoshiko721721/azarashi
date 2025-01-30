#include "pause.h"

void Pause::apply() {
	if (Input::GetKeyTrigger(VK_P)) {
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
