#include "ControllerGyro.h"
#include <iostream>

//maincpp��
// �R���g���[���[��������
//SDL_GameController* controller = InitializeController();
//if (!controller) {
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return -1;
//}
// 
//  // �W���C���Z���T�[�ŕϐ�Object�̈ʒu���X�V
// UpdateCirclePosition(controller, //Object, SCREEN_WIDTH, SCREEN_HEIGHT);
// 
// //�K�v�ɉ�����SDL_Delay��p���Ēx����������
// //(��)
// SDL_Delay(16); // 60FPS�ɋߎ�
// 
// //�I������
// SDL_GameControllerClose(controller);
// SDL_Quit();
//
// return 0;
//�����

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
//    float gyroData[3] = { 0 }; // x, y, z��
//    if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
//       �����ɏ������L��
//    }
//}
