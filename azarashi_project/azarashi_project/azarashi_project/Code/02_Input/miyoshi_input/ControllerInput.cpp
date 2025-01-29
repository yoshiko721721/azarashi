#include "../miyoshi_input/ControllerInput.h"
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_gamecontroller.h"
#include "SDL_joystick.h"
#include <iostream>
//#include <DirectX.h>

SDL_Event Controller::Input::e;
SDL_GameController* Controller::Input::controller = nullptr;
SDL_Joystick* Controller::Input::joystick = nullptr;

//�R���g���[���[���͏���ۑ�����ϐ�
XINPUT_STATE Controller::Input::controllerState;
XINPUT_STATE Controller::Input::controllerState_old;

//�L�[���͏���ۑ�����ϐ�
float Controller::Input::keySecond[256];
BYTE Controller::Input::keyState[256];
BYTE Controller::Input::keyState_old[256];

int Controller::Input::VibrationTime;

//�R���X�g���N�^
Controller::Input::Input()
{
	VibrationTime = 0;
	//Input::GetInstance();
}

//�f�X�g���N�^
Controller::Input::~Input()
{
	//�U�����I��������
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
}

void Controller::Input::Update()
{
	//1�t���[���O�̓��͂��L�^���Ă���
	for (int i = 0; i < 256; i++) 
	{
		keyState_old[i] = keyState[i]; 
	}

	controllerState_old = controllerState;

	//�L�[���͂��X�V
	BOOL hr = GetKeyboardState(keyState);

	for (int i = 0; i < 256; i++)
	{
		if ((keyState[i] & 0x80) == false)
		{
			keySecond[i] = 0;
		}
		else
		{
			keySecond[i] += 1;
		}
	}

	//�R���g���[���[���͂��X�V(XInput)
	XInputGetState(0, &controllerState);

	//�U���p�����Ԃ��J�E���g
	if (VibrationTime > 0) {
		VibrationTime--;
		if (VibrationTime == 0) { //�U���p�����Ԃ��o�������ɐU�����~�߂�
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &vibration);
		}
	}
}

/*void Controller::Input::ControllerUpdate()
{
	if (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				push_A = true;
			}
			else
			{
				push_A = false;
			}

			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				push_B = true;
			}
			else
			{
				push_B = false;
			}

			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_X)
			{
				push_X = true;
			}
			else
			{
				push_X = false;
			}

			if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				push_Y = true;
			}
			else
			{
				push_Y = false;
			}
		}
	}
}*/

//�L�[����
bool Controller::Input::GetKeyPress(int key, float second) //�v���X
{
	if (keyState[key] & 0x80)
	{
		if (second == 0.0f || (keySecond[key] / 60) > second)
		{
			return true;
		}
	}

	return false;
}

bool Controller::Input::GetKeyTrigger(int key) //�g���K�[
{
	return (keyState[key] & 0x80) && !(keyState_old[key] & 0x80);
}
bool Controller::Input::GetKeyRelease(int key) //�����[�X
{
	return !(keyState[key] & 0x80) && (keyState_old[key] & 0x80);
}

//���A�i���O�X�e�B�b�N
DirectX::XMFLOAT2 Controller::Input::GetLeftAnalogStick(void)
{
	SHORT Lx = controllerState.Gamepad.sThumbLX; // -32768�`32767
	SHORT Ly = controllerState.Gamepad.sThumbLY; // -32768�`32767

	DirectX::XMFLOAT2 res;
	res.x = Lx / 32767.0f; //-1�`1
	res.y = Ly / 32767.0f; //-1�`1
	return res;
}
//�E�A�i���O�X�e�B�b�N
DirectX::XMFLOAT2 Controller::Input::GetRightAnalogStick(void)
{
	SHORT Rx = controllerState.Gamepad.sThumbRX; // -32768�`32767
	SHORT Ry = controllerState.Gamepad.sThumbRY; // -32768�`32767

	DirectX::XMFLOAT2 res;
	res.x = Rx / 32767.0f; //-1�`1
	res.y = Ry / 32767.0f; //-1�`1
	return res;
}

//���g���K�[
float Controller::Input::GetLeftTrigger(void)
{
	BYTE Lt = controllerState.Gamepad.bLeftTrigger; // 0�`255
	return Lt / 255.0f;
}
//�E�g���K�[
float Controller::Input::GetRightTrigger(void)
{
	BYTE Rt = controllerState.Gamepad.bRightTrigger; // 0�`255
	return Rt / 255.0f;
}

//�{�^������
bool Controller::Input::GetButtonPress(WORD btn) //�v���X
{
	return (controllerState.Gamepad.wButtons & btn) != 0;
}
bool Controller::Input::GetButtonTrigger(WORD btn) //�g���K�[
{
	return (controllerState.Gamepad.wButtons & btn) != 0 && (controllerState_old.Gamepad.wButtons & btn) == 0;
}
bool Controller::Input::GetButtonRelease(WORD btn) //�����[�X
{
	return (controllerState.Gamepad.wButtons & btn) == 0 && (controllerState_old.Gamepad.wButtons & btn) != 0;
}

//�W���C������


SDL_GameController* InitializeController()//�R���g���[���[������
{
	Controller::Input::controller = nullptr;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			Controller::Input::controller = SDL_GameControllerOpen(i);
			if (Controller::Input::controller) {
				std::cout << "Controller connected: " << SDL_GameControllerName(Controller::Input::controller) << std::endl;
				break;
			}
		}
	} 
	if (!Controller::Input::controller) {
		//std::cerr << "No GameController found!" << std::endl;
	}
	//return controller;
	return Controller::Input::controller;
}

bool GetGyroData(SDL_GameController* controller, float* gyroData) {
	if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
		return true;
	}
	return false;
}

//�U��
void Controller::Input::SetVibration(int frame, float powor)
{
	// XINPUT_VIBRATION�\���̂̃C���X�^���X���쐬
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// ���[�^�[�̋��x��ݒ�i0�`65535�j
	vibration.wLeftMotorSpeed = (WORD)(powor * 65535.0f);
	vibration.wRightMotorSpeed = (WORD)(powor * 65535.0f);
	XInputSetState(0, &vibration);

	//�U���p�����Ԃ���
	VibrationTime = frame;
}

