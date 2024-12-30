#pragma once

#ifndef GYRO_H
#define GYRO_H

#include <SDL.h>
#include "circle.h"

// コントローラーを初期化する関数
SDL_GameController* InitializeController();

// ジャイロセンサーのデータを用いて変数Objectの位置を更新する関数
//void UpdateCirclePosition(SDL_GameController* controller, //Object& //Object, int screenWidth, int screenHeight);

#endif // GYRO_H
