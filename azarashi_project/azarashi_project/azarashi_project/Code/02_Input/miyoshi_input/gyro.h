#pragma once

#ifndef GYRO_H
#define GYRO_H

#include <SDL.h>
#include "circle.h"

// �R���g���[���[������������֐�
SDL_GameController* InitializeController();

// �W���C���Z���T�[�̃f�[�^��p���ĉ~�̈ʒu���X�V����֐�
//void UpdateCirclePosition(SDL_GameController* controller, Circle& circle, int screenWidth, int screenHeight);

#endif // GYRO_H
