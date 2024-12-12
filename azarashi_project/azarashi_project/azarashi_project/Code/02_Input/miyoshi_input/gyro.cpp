#include "gyro.h"
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

//void UpdateCirclePosition(SDL_GameController* controller, Circle& circle, int screenWidth, int screenHeight) {
//    float gyroData[3] = { 0 }; // x, y, z軸
//    if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
//        // ジャイロデータを円の位置に反映
//        circle.x += gyroData[0] * 0.1f; // スケーリング係数を調整
//        circle.y += gyroData[1] * 0.1f;
//
//        // 画面端でバウンド
//        if (circle.x < 0) circle.x = 0;
//        if (circle.x > screenWidth) circle.x = screenWidth;
//        if (circle.y < 0) circle.y = 0;
//        if (circle.y > screenHeight) circle.y = screenHeight;
//    }
//}
