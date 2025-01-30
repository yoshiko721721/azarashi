#include "pause.h"

void Pause::apply() {
	if (Input::GetKeyTrigger(VK_P)) {
		paused = true;
	}

}

void Pause::maladaptive() {
	if (Input::GetKeyTrigger(VK_K)) {
		paused = false;
	}
}

bool Pause::isPaused() const {
    return paused;
}
