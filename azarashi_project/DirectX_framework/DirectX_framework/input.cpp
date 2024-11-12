#include "input.h"

//�R���X�g���N�^
Input::Input()
{
	VibrationTime = 0;
}

//�f�X�g���N�^
Input::~Input()
{
	//�U�����I��������
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
}

void Input::Update()
{
	//1�t���[���O�̓��͂��L�^���Ă���
	for (int i = 0; i < 256; i++) { keyState_old[i] = keyState[i]; }
	controllerState_old = controllerState;

	//�L�[���͂��X�V
	BOOL hr = GetKeyboardState(keyState);

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

//�L�[����
bool Input::GetKeyPress(int key) //�v���X
{
	return keyState[key] & 0x80;
}
bool Input::GetKeyTrigger(int key) //�g���K�[
{
	return (keyState[key] & 0x80) && !(keyState_old[key] & 0x80);
}
bool Input::GetKeyRelease(int key) //�����[�X
{
	return !(keyState[key] & 0x80) && (keyState_old[key] & 0x80);
}

//���A�i���O�X�e�B�b�N
DirectX::XMFLOAT2 Input::GetLeftAnalogStick(void)
{
	SHORT x = controllerState.Gamepad.sThumbLX; // -32768�`32767
	SHORT y = controllerState.Gamepad.sThumbLY; // -32768�`32767

	DirectX::XMFLOAT2 res;
	res.x = x / 32767.0f; //-1�`1
	res.y = y / 32767.0f; //-1�`1
	return res;
}
//�E�A�i���O�X�e�B�b�N
DirectX::XMFLOAT2 Input::GetRightAnalogStick(void)
{
	SHORT x = controllerState.Gamepad.sThumbRX; // -32768�`32767
	SHORT y = controllerState.Gamepad.sThumbRY; // -32768�`32767

	DirectX::XMFLOAT2 res;
	res.x = x / 32767.0f; //-1�`1
	res.y = y / 32767.0f; //-1�`1
	return res;
}

//���g���K�[
float Input::GetLeftTrigger(void)
{
	BYTE t = controllerState.Gamepad.bLeftTrigger; // 0�`255
	return t / 255.0f;
}
//�E�g���K�[
float Input::GetRightTrigger(void)
{
	BYTE t = controllerState.Gamepad.bRightTrigger; // 0�`255
	return t / 255.0f;
}

//�{�^������
bool Input::GetButtonPress(WORD btn) //�v���X
{
	return (controllerState.Gamepad.wButtons & btn) != 0;
}
bool Input::GetButtonTrigger(WORD btn) //�g���K�[
{
	return (controllerState.Gamepad.wButtons & btn) != 0 && (controllerState_old.Gamepad.wButtons & btn) == 0;
}
bool Input::GetButtonRelease(WORD btn) //�����[�X
{
	return (controllerState.Gamepad.wButtons & btn) == 0 && (controllerState_old.Gamepad.wButtons & btn) != 0;
}

//�U��
void Input::SetVibration(int frame, float powor)
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

