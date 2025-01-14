#include "ControllerGyro.h"
#include <iostream>

//maincppで
// コントローラーを初期化
//SDL_GameController* controller = InitializeController();
//if (!controller) {
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return -1;
//}
// 
//  // ジャイロセンサーで変数Objectの位置を更新
// UpdateCirclePosition(controller, //Object, SCREEN_WIDTH, SCREEN_HEIGHT);
// 
// //必要に応じてSDL_Delayを用いて遅延をかける
// //(例)
// SDL_Delay(16); // 60FPSに近似
// 
// //終了処理
// SDL_GameControllerClose(controller);
// SDL_Quit();
//
// return 0;
//を入力

SDL_GameController* InitializeController() {
    SDL_GameController* controller = nullptr;
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            controller = SDL_GameControllerOpen(i);
            if (controller) {
                std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
                SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_GYRO, SDL_TRUE);
                break;
            }
        }
    }
    if (!controller) {
        std::cerr << "No GameController found!" << std::endl;
    }
    return controller;
}

//void UpdateObjectPosition(SDL_GameController* controller, Object& object, int screenWidth, int screenHeight) {
//    float gyroData[3] = { 0 }; // x, y, z軸
//    if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
//       ここに処理を記入
//    }
//}
