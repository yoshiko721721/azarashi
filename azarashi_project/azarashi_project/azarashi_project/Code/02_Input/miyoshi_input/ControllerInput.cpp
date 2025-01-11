#include "../miyoshi_input/ControllerInput.h"
#include "../miyoshi_input/gyro動作必要/SDL2-2.30.9/SDL2-2.30.9/include/SDL.h"
#include "../miyoshi_input/gyro動作必要/SDL2-2.30.9/SDL2-2.30.9/include/SDL_main.h"
#include "DirectX.h"

//コントローラー入力情報を保存する変数
XINPUT_STATE Input::controllerState;
XINPUT_STATE Input::controllerState_old;

//キー入力情報を保存する変数
float Input::keySecond[256];
BYTE Input::keyState[256];
BYTE Input::keyState_old[256];

int Input::VibrationTime;

//コンストラクタ
Input::Input()
{
	VibrationTime = 0;
	//Input::GetInstance();
}

//デストラクタ
Input::~Input()
{
	//振動を終了させる
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
}

void Input::Update()
{
	//1フレーム前の入力を記録しておく
	for (int i = 0; i < 256; i++) 
	{
		keyState_old[i] = keyState[i]; 
	}

	controllerState_old = controllerState;

	//キー入力を更新
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




	//コントローラー入力を更新(XInput)
	XInputGetState(0, &controllerState);

	//振動継続時間をカウント
	if (VibrationTime > 0) {
		VibrationTime--;
		if (VibrationTime == 0) { //振動継続時間が経った時に振動を止める
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &vibration);
		}
	}
}

//キー入力
bool Input::GetKeyPress(int key, float second) //プレス
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

bool Input::GetKeyTrigger(int key) //トリガー
{
	return (keyState[key] & 0x80) && !(keyState_old[key] & 0x80);
}
bool Input::GetKeyRelease(int key) //リリース
{
	return !(keyState[key] & 0x80) && (keyState_old[key] & 0x80);
}

//左アナログスティック
DirectX::XMFLOAT2 Input::GetLeftAnalogStick(void)
{
	SHORT Lx = controllerState.Gamepad.sThumbLX; // -32768～32767
	SHORT Ly = controllerState.Gamepad.sThumbLY; // -32768～32767

	DirectX::XMFLOAT2 res;
	res.x = Lx / 32767.0f; //-1～1
	res.y = Ly / 32767.0f; //-1～1
	return res;
}
//右アナログスティック
DirectX::XMFLOAT2 Input::GetRightAnalogStick(void)
{
	SHORT Rx = controllerState.Gamepad.sThumbRX; // -32768～32767
	SHORT Ry = controllerState.Gamepad.sThumbRY; // -32768～32767

	DirectX::XMFLOAT2 res;
	res.x = Rx / 32767.0f; //-1～1
	res.y = Ry / 32767.0f; //-1～1
	return res;
}

//左トリガー
float Input::GetLeftTrigger(void)
{
	BYTE Lt = controllerState.Gamepad.bLeftTrigger; // 0～255
	return Lt / 255.0f;
}
//右トリガー
float Input::GetRightTrigger(void)
{
	BYTE Rt = controllerState.Gamepad.bRightTrigger; // 0～255
	return Rt / 255.0f;
}

//ボタン入力
bool Input::GetButtonPress(WORD btn) //プレス
{
	return (controllerState.Gamepad.wButtons & btn) != 0;
}
bool Input::GetButtonTrigger(WORD btn) //トリガー
{
	return (controllerState.Gamepad.wButtons & btn) != 0 && (controllerState_old.Gamepad.wButtons & btn) == 0;
}
bool Input::GetButtonRelease(WORD btn) //リリース
{
	return (controllerState.Gamepad.wButtons & btn) == 0 && (controllerState_old.Gamepad.wButtons & btn) != 0;
}

//ジャイロ入力


SDL_GameController* InitializeController()//コントローラー初期化
{
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

bool GetGyroData(SDL_GameController* controller, float* gyroData) {
	if (SDL_GameControllerGetSensorData(controller, SDL_SENSOR_GYRO, gyroData, 3) == 0) {
		return true;
	}
	return false;
}



//振動
void Input::SetVibration(int frame, float powor)
{
	// XINPUT_VIBRATION構造体のインスタンスを作成
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// モーターの強度を設定（0～65535）
	vibration.wLeftMotorSpeed = (WORD)(powor * 65535.0f);
	vibration.wRightMotorSpeed = (WORD)(powor * 65535.0f);
	XInputSetState(0, &vibration);

	//振動継続時間を代入
	VibrationTime = frame;
}

