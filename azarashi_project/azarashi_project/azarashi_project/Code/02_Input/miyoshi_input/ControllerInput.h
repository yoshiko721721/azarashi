#pragma once
#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h> // DirextX�̐��w�֘A�̃w�b�_�[�t�@�C��
//#include "DirectX.h"


//C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include
#include "SDL.h"
#include "SDL_main.h"
                      //�����Ă��Ė��Ȃ�

#include <Xinput.h> //XInput���g�����߂̃w�b�_�[�t�@�C��
#pragma comment (lib, "xinput.lib") //XInput���g�����߂ɕK�v

#ifndef INPUT_H
#define INPUT_H

//#include "SDL.h"

//�W���C������(�R���g���[���[)
	// SDL_�R���g���[���[������������֐�
SDL_GameController* InitializeController();

//	static float SDL_GameControllerGetSensorData(controller,int d,int g);
bool GetGyroData(SDL_GameController* controller, float* gyroData);


// �W���C���Z���T�[�̃f�[�^��p���ĕϐ�Object�̈ʒu���X�V����֐�
//void UpdateCirclePosition(SDL_GameController* controller, //Object& //Object,
//                              int screenWidth, int screenHeight);
#endif // !INPUT_H

#define XINPUT_A              0x1000
#define XINPUT_B              0x2000
#define XINPUT_X              0x4000
#define XINPUT_Y              0x8000
#define XINPUT_UP             0x0001
#define XINPUT_DOWN           0x0002
#define XINPUT_LEFT           0x0004
#define XINPUT_RIGHT          0x0008
#define XINPUT_START          0x0010
#define XINPUT_BACK           0x0020
#define XINPUT_LEFT_THUMB     0x0040 //���X�e�B�b�N��������
#define XINPUT_RIGHT_THUMB    0x0080 //�E�X�e�B�b�N��������
#define XINPUT_LEFT_SHOULDER  0x0100 //L
#define XINPUT_RIGHT_SHOULDER 0x0200 //R

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x45
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


namespace Controller
{
	class Input
	{
	private:
		//�L�[���͏���ۑ�����ϐ�
		static BYTE keyState[256];
		static float keySecond[256];
		static BYTE keyState_old[256];


		//�R���g���[���[���͏���ۑ�����ϐ�
		static XINPUT_STATE controllerState;
		static XINPUT_STATE controllerState_old;

		static int VibrationTime; //�U���p�����Ԃ��J�E���g����ϐ�

		////�V���O���g������A�N�Z�X������
		//friend class Singleton<Input>;

		Input(); //�R���X�g���N�^
	public:

		~Input(); //�f�X�g���N�^
		static void Update(); //�X�V
		static SDL_Event e;
		static SDL_GameController* controller;
		//static SDL_Event e;

		//�L�[����
		static bool GetKeyPress(int key, float second = 0.0f);   //�v���X(�����Ă���Ԃ�����)
		static bool GetKeyTrigger(int key); //�g���K�[(�����n�߂���)
		static bool GetKeyRelease(int key); //�����[�X(�����I�������)

		//�A�i���O�X�e�B�b�N(�R���g���[���[)
		static DirectX::XMFLOAT2 GetLeftAnalogStick(void);
		static DirectX::XMFLOAT2 GetRightAnalogStick(void);

		//�g���K�[(�R���g���[���[)
		static float GetLeftTrigger(void);
		static float GetRightTrigger(void);

		//�{�^������(�R���g���[���[)
		static bool GetButtonPress(WORD btn);   //�v���X(�����Ă���Ԃ�����)
		static bool GetButtonTrigger(WORD btn); //�g���K�[(�����n�߂���)
		static bool GetButtonRelease(WORD btn); //�����[�X(�����I�������)





		//�U��(�R���g���[���[)
		//flame�F�U�����p�����鎞��(�P�ʁF�t���[��)
		//powoe�F�U���̋���(0�`1)
		static void SetVibration(int frame = 1, float powor = 1);
	};
};



