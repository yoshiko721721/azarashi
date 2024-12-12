#include "gyro.h"
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

//void UpdateCirclePosition(SDL_GameController* controller, Circle& circle, int screenWidth, int screenHeight) {
//    float gyroData[3] = { 0 }; // x, y, z��
//    if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
//        // �W���C���f�[�^���~�̈ʒu�ɔ��f
//        circle.x += gyroData[0] * 0.1f; // �X�P�[�����O�W���𒲐�
//        circle.y += gyroData[1] * 0.1f;
//
//        // ��ʒ[�Ńo�E���h
//        if (circle.x < 0) circle.x = 0;
//        if (circle.x > screenWidth) circle.x = screenWidth;
//        if (circle.y < 0) circle.y = 0;
//        if (circle.y > screenHeight) circle.y = screenHeight;
//    }
//}
