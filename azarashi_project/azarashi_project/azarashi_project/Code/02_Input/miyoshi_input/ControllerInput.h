#pragma once
#include <d3d11.h>  // DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h> // DirextXの数学関連のヘッダーファイル
//#include "DirectX.h"


//C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include
#include "SDL.h"
#include "SDL_main.h"
                      //書いていて問題なし

#include <Xinput.h> //XInputを使うためのヘッダーファイル
#pragma comment (lib, "xinput.lib") //XInputを使うために必要

#ifndef INPUT_H
#define INPUT_H

//#include "SDL.h"

//ジャイロ入力(コントローラー)
	// SDL_コントローラーを初期化する関数
SDL_GameController* InitializeController();

//	static float SDL_GameControllerGetSensorData(controller,int d,int g);
bool GetGyroData(SDL_GameController* controller, float* gyroData);


// ジャイロセンサーのデータを用いて変数Objectの位置を更新する関数
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
#define XINPUT_LEFT_THUMB     0x0040 //左スティック押し込み
#define XINPUT_RIGHT_THUMB    0x0080 //右スティック押し込み
#define XINPUT_LEFT_SHOULDER  0x0100 //L
#define XINPUT_RIGHT_SHOULDER 0x0200 //R
#define XINPUT_LEFT_TRIGGER   0x0400 //L2
#define XINPUT_RIGHT_TRIGGER  0x0800 //R2

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

enum PUSH_TYPE
{
	PUPS_A = 0,
	PUPS_B = 0,
	PUPS_X = 0,
	PUPS_Y = 0
};

namespace Controller
{
	class Input
	{
	private:
		//キー入力情報を保存する変数
		static BYTE keyState[256];
		static float keySecond[256];
		static BYTE keyState_old[256];


		//コントローラー入力情報を保存する変数
		static XINPUT_STATE controllerState;
		static XINPUT_STATE controllerState_old;

		static int VibrationTime; //振動継続時間をカウントする変数

		////シングルトンからアクセスを許可
		//friend class Singleton<Input>;

		Input(); //コンストラクタ
	public:

		~Input(); //デストラクタ
		static void Update(); //更新
		static void ControllerUpdate(){}
		static SDL_Event e;
		static SDL_GameController* controller;
		static SDL_Joystick* joystick;
		//static SDL_Event e;

		//キー入力
		static bool GetKeyPress(int key, float second = 0.0f);   //プレス(押している間ずっと)
		static bool GetKeyTrigger(int key); //トリガー(押し始めた時)
		static bool GetKeyRelease(int key); //リリース(押し終わった時)

		//アナログスティック(コントローラー)
		static DirectX::XMFLOAT2 GetLeftAnalogStick(void);
		static DirectX::XMFLOAT2 GetRightAnalogStick(void);

		//トリガー(コントローラー)
		static float GetLeftTrigger(void);
		static float GetRightTrigger(void);
		static bool GetLeftTriggerPress(float threshold = 0.1f);
		static bool GetRightTriggerPress(float threshold = 0.1f);

		//ボタン入力(コントローラー)
		static bool GetButtonPress(WORD btn);   //プレス(押している間ずっと)
		static bool GetButtonTrigger(WORD btn); //トリガー(押し始めた時)
		static bool GetButtonRelease(WORD btn); //リリース(押し終わった時)

		static int push;

		static bool push_A; //Aボタンを押したかどうか
		static bool push_B; //Bボタンを押したかどうか
		static bool push_X; //Xボタンを押したかどうか
		static bool push_Y; //Yボタンを押したかどうか

		//振動(コントローラー)
		//flame：振動を継続する時間(単位：フレーム)
		//powoe：振動の強さ(0〜1)
		static void SetVibration(int frame = 1, float powor = 1);
	};
};



