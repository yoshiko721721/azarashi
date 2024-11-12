#pragma once
#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h> // DirextX�̐��w�֘A�̃w�b�_�[�t�@�C��

#include <Xinput.h> //XInput���g�����߂̃w�b�_�[�t�@�C��
#pragma comment (lib, "xinput.lib") //XInput���g�����߂ɕK�v

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

class Input {
private:
	//�L�[���͏���ۑ�����ϐ�
	BYTE keyState[256] = {};
	BYTE keyState_old[256] = {};

	//�R���g���[���[���͏���ۑ�����ϐ�
	XINPUT_STATE controllerState = {};
	XINPUT_STATE controllerState_old = {};

	int VibrationTime; //�U���p�����Ԃ��J�E���g����ϐ�

public:

	Input(); //�R���X�g���N�^
	~Input(); //�f�X�g���N�^
	void Update(); //�X�V

	//�L�[����
	bool GetKeyPress(int key);   //�v���X(�����Ă���Ԃ�����)
	bool GetKeyTrigger(int key); //�g���K�[(�����n�߂���)
	bool GetKeyRelease(int key); //�����[�X(�����I�������)

	//�A�i���O�X�e�B�b�N(�R���g���[���[)
	DirectX::XMFLOAT2 GetLeftAnalogStick(void);
	DirectX::XMFLOAT2 GetRightAnalogStick(void);

	//�g���K�[(�R���g���[���[)
	float GetLeftTrigger(void);
	float GetRightTrigger(void);

	//�{�^������(�R���g���[���[)
	bool GetButtonPress(WORD btn);   //�v���X(�����Ă���Ԃ�����)
	bool GetButtonTrigger(WORD btn); //�g���K�[(�����n�߂���)
	bool GetButtonRelease(WORD btn); //�����[�X(�����I�������)
	
	//�U��(�R���g���[���[)
	//flame�F�U�����p�����鎞��(�P�ʁF�t���[��)
	//powoe�F�U���̋���(0�`1)
	void SetVibration(int frame = 1, float powor = 1);
};

